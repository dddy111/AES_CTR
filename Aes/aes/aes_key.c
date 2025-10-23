/* aes_key.c - AES 키 스케줄링 구현 */
#include <stdint.h>
#include "../include/aes.h"
#include "../include/aes_internal.h"
#include "../include/crypto_common.h"

/* =============================================================================
 * 상수 정의
 * ============================================================================= */

#define MAX_ROUND_KEYS 60  /* 최대 라운드 키 개수 (AES-256용) */

/* =============================================================================
 * 내부 헬퍼 함수들
 * ============================================================================= */

/**
 * @brief 4바이트 워드를 왼쪽으로 1바이트 회전 (RotWord)
 * @param word 4바이트 워드
 * @return 회전된 워드
 */
static uint32_t rot_word(uint32_t word)
{
    return (word << 8) | (word >> 24);
}

/**
 * @brief 4바이트 워드의 각 바이트에 S-Box 적용 (SubWord)
 * @param word 4바이트 워드
 * @return S-Box가 적용된 워드
 */
static uint32_t sub_word(uint32_t word)
{
    uint32_t result = 0;
    
    // 각 바이트에 S-Box 적용
    result |= ((uint32_t)aes_sub_byte((word >> 24) & 0xff)) << 24;  // MSB
    result |= ((uint32_t)aes_sub_byte((word >> 16) & 0xff)) << 16;
    result |= ((uint32_t)aes_sub_byte((word >> 8) & 0xff)) << 8;
    result |= ((uint32_t)aes_sub_byte(word & 0xff));                // LSB
    
    return result;
}

/**
 * @brief 키 길이에 따른 라운드 수 반환
 * @param key_len 키 길이 (AES_128, AES_192, AES_256)
 * @return 라운드 수 (오류 시 -1)
 */
static int get_rounds(aes_keylen_t key_len)
{
    switch (key_len) {
        case AES_128: return 10;  /* AES-128: 10라운드 */
        case AES_192: return 12;  /* AES-192: 12라운드 */
        case AES_256: return 14;  /* AES-256: 14라운드 */
        default: return -1;       /* 잘못된 키 길이 */
    }
}

/**
 * @brief 바이트 배열을 32비트 워드로 변환
 * @param bytes 바이트 배열
 * @param index 시작 인덱스
 * @return 32비트 워드 (빅엔디안)
 */
static uint32_t bytes_to_word(const uint8_t *bytes, int index)
{
    return ((uint32_t)bytes[4*index + 0] << 24) |
           ((uint32_t)bytes[4*index + 1] << 16) |
           ((uint32_t)bytes[4*index + 2] << 8)  |
           ((uint32_t)bytes[4*index + 3]);
}

/**
 * @brief 원본 키를 첫 번째 라운드 키로 설정
 * @param ek 확장 키 구조체
 * @param key 원본 키
 * @param key_len 키 길이 (바이트)
 */
static void set_initial_round_keys(aes_key_t *ek, const uint8_t *key, aes_keylen_t key_len)
{
    int key_word_count = (int)key_len / 4;
    
    for (int i = 0; i < key_word_count; i++) {
        ek->rk[i] = bytes_to_word(key, i);
    }
}

/**
 * @brief 라운드 키 생성 (키 스케줄링)
 * @param ek 확장 키 구조체
 * @param key_len 키 길이
 * @param rounds 라운드 수
 */
static void generate_round_keys(aes_key_t *ek, aes_keylen_t key_len, int rounds)
{
    int key_word_count = (int)key_len / 4;
    int total_keys = 4 * (rounds + 1);
    
    for (int i = key_word_count; i < total_keys; i++) {
        uint32_t temp = ek->rk[i - 1];
        
        // 키 길이에 따른 특별한 처리
        if (i % key_word_count == 0) {
            // RotWord, SubWord, Rcon 적용
            temp = sub_word(rot_word(temp)) ^ ((uint32_t)aes_rcon[i / key_word_count] << 24);
        } else if (key_len == AES_256 && i % key_word_count == 4) {
            // AES-256의 경우 4번째 워드마다 SubWord 적용
            temp = sub_word(temp);
        }
        
        // 이전 라운드 키와 XOR
        ek->rk[i] = ek->rk[i - key_word_count] ^ temp;
    }
}

/**
 * @brief 암호화 키를 복호화 키로 복사
 * @param dk 복호화 키 구조체
 * @param ek 암호화 키 구조체
 */
static void copy_encrypt_to_decrypt_key(aes_key_t *dk, const aes_key_t *ek)
{
    dk->nr = ek->nr;
    
    // 모든 라운드 키를 동일한 순서로 복사
    for (int i = 0; i <= (int)ek->nr; i++) {
        dk->rk[4 * i + 0] = ek->rk[4 * i + 0];
        dk->rk[4 * i + 1] = ek->rk[4 * i + 1];
        dk->rk[4 * i + 2] = ek->rk[4 * i + 2];
        dk->rk[4 * i + 3] = ek->rk[4 * i + 3];
    }
}

/* =============================================================================
 * 공개 API 함수들
 * ============================================================================= */

/**
 * @brief AES 암호화용 키 확장
 * 
 * 원본 키를 확장하여 모든 라운드에 필요한 라운드 키들을 생성합니다.
 * 키 스케줄링 알고리즘을 사용하여 키를 확장합니다.
 * 
 * @param ek 확장된 암호화 키 구조체
 * @param key 원본 키 (16, 24, 또는 32바이트)
 * @param klen 키 길이 (AES_128, AES_192, AES_256)
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_set_encrypt_key(aes_key_t *ek, const uint8_t *key, aes_keylen_t klen)
{
    // 매개변수 유효성 검사
    if (!ek || !key) {
        return AES_ERR_BAD_PARAM;
    }
    
    // 키 길이에 따른 라운드 수 확인
    int rounds = get_rounds(klen);
    if (rounds < 0) {
        return AES_ERR_BAD_KEY_LEN;
    }
    
    // 라운드 수 설정
    ek->nr = rounds;
    
    // 1. 원본 키를 첫 번째 라운드 키로 설정
    set_initial_round_keys(ek, key, klen);
    
    // 2. 나머지 라운드 키들 생성
    generate_round_keys(ek, klen, rounds);
    
    return AES_OK;
}

/**
 * @brief AES 복호화용 키 확장
 * 
 * 복호화는 암호화와 동일한 라운드 키를 사용하므로,
 * 암호화 키를 생성한 후 동일한 순서로 복사합니다.
 * 
 * @param dk 확장된 복호화 키 구조체
 * @param key 원본 키 (16, 24, 또는 32바이트)
 * @param klen 키 길이 (AES_128, AES_192, AES_256)
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_set_decrypt_key(aes_key_t *dk, const uint8_t *key, aes_keylen_t klen)
{
    // 매개변수 유효성 검사
    if (!dk || !key) {
        return AES_ERR_BAD_PARAM;
    }
    
    // 1. 먼저 암호화 키 생성
    aes_key_t ek;
    aes_err_t err = aes_set_encrypt_key(&ek, key, klen);
    if (err != AES_OK) {
        return err;
    }
    
    // 2. 암호화 키를 복호화 키로 복사
    copy_encrypt_to_decrypt_key(dk, &ek);
    
    // 3. 임시 암호화 키 정리
    aes_key_clear(&ek);
    
    return AES_OK;
}

/**
 * @brief 확장된 키 메모리 정리
 * 
 * 보안을 위해 확장된 키의 메모리를 0으로 덮어쓰기합니다.
 * 키 사용 후 반드시 호출해야 합니다.
 * 
 * @param k 정리할 키 구조체
 */
void aes_key_clear(aes_key_t *k)
{
    if (k) {
        // 모든 라운드 키를 0으로 덮어쓰기
        for (int i = 0; i < MAX_ROUND_KEYS; i++) {
            k->rk[i] = 0;
        }
        k->nr = 0;
    }
}