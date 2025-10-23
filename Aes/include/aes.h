/* aes.h - AES 블록 암호 핵심 API */
#ifndef CRYPTO_AES_H
#define CRYPTO_AES_H

#include "crypto_common.h"

/* =============================================================================
 * 데이터 구조체 정의
 * ============================================================================= */

/**
 * @brief AES 확장 키 구조체
 * 
 * AES 키 스케줄링을 통해 생성된 모든 라운드 키를 저장합니다.
 * 이 구조체는 암호화/복호화에 필요한 모든 라운드 키를 포함합니다.
 */
typedef struct {
    uint32_t rk[AES_MAX_ROUND_KEYS];  /**< 라운드 키 배열 (최대 60개) */
    uint32_t nr;                      /**< 라운드 수 (10/12/14) */
} aes_key_t;

/* =============================================================================
 * 키 관리 함수들
 * ============================================================================= */

/**
 * @brief AES 암호화용 키 확장
 * 
 * 원본 키를 확장하여 모든 라운드에 필요한 라운드 키들을 생성합니다.
 * 키 스케줄링 알고리즘을 사용하여 키를 확장합니다.
 * 
 * @param ek 확장된 암호화 키 구조체 (출력)
 * @param key 원본 키 (입력)
 * @param klen 키 길이 (AES_128, AES_192, AES_256)
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 * 
 * @note 사용 후 aes_key_clear()로 키를 정리해야 합니다.
 */
AES_API aes_err_t aes_set_encrypt_key(aes_key_t *ek,
                                      const uint8_t *key, 
                                      aes_keylen_t klen);

/**
 * @brief AES 복호화용 키 확장
 * 
 * 복호화는 암호화와 동일한 라운드 키를 사용하므로,
 * 암호화 키를 생성한 후 동일한 순서로 복사합니다.
 * 
 * @param dk 확장된 복호화 키 구조체 (출력)
 * @param key 원본 키 (입력)
 * @param klen 키 길이 (AES_128, AES_192, AES_256)
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 * 
 * @note 사용 후 aes_key_clear()로 키를 정리해야 합니다.
 */
AES_API aes_err_t aes_set_decrypt_key(aes_key_t *dk,
                                      const uint8_t *key, 
                                      aes_keylen_t klen);

/**
 * @brief 확장된 키 메모리 정리
 * 
 * 보안을 위해 확장된 키의 메모리를 0으로 덮어쓰기합니다.
 * 키 사용 후 반드시 호출해야 합니다.
 * 
 * @param k 정리할 키 구조체
 * 
 * @warning 이 함수는 민감한 키 데이터를 메모리에서 완전히 제거합니다.
 */
AES_API void aes_key_clear(aes_key_t *k);

/* =============================================================================
 * 블록 암호화/복호화 함수들
 * ============================================================================= */

/**
 * @brief AES 블록 암호화 (128비트)
 * 
 * 표준 AES 암호화 알고리즘을 구현합니다.
 * - 초기 AddRoundKey
 * - Nr-1번의 일반 라운드 (SubBytes, ShiftRows, MixColumns, AddRoundKey)
 * - 마지막 라운드 (SubBytes, ShiftRows, AddRoundKey)
 * 
 * @param ek 확장된 암호화 키
 * @param in 입력 평문 (16바이트)
 * @param out 출력 암호문 (16바이트)
 * 
 * @note 입력과 출력 버퍼는 겹치지 않아야 합니다.
 * @note ek는 aes_set_encrypt_key()로 미리 설정되어야 합니다.
 */
AES_API aes_err_t aes_encrypt_block(const aes_key_t *ek,
                                   const uint8_t in[AES_BLOCK_SIZE],
                                   uint8_t out[AES_BLOCK_SIZE]);

/**
 * @brief AES 블록 복호화 (128비트)
 * 
 * 표준 AES 복호화 알고리즘을 구현합니다.
 * - 초기 AddRoundKey (마지막 라운드키)
 * - Nr-1번의 일반 라운드 (InvShiftRows, InvSubBytes, AddRoundKey, InvMixColumns)
 * - 마지막 라운드 (InvShiftRows, InvSubBytes, AddRoundKey)
 * 
 * @param dk 확장된 복호화 키
 * @param in 입력 암호문 (16바이트)
 * @param out 출력 평문 (16바이트)
 * 
 * @note 입력과 출력 버퍼는 겹치지 않아야 합니다.
 * @note dk는 aes_set_decrypt_key()로 미리 설정되어야 합니다.
 */
AES_API aes_err_t aes_decrypt_block(const aes_key_t *dk,
                                   const uint8_t in[AES_BLOCK_SIZE],
                                   uint8_t out[AES_BLOCK_SIZE]);

/* =============================================================================
 * 유틸리티 함수들
 * ============================================================================= */

/**
 * @brief 키 길이 유효성 검사
 * 
 * 주어진 키 길이가 유효한 AES 키 길이인지 확인합니다.
 * 
 * @param klen 확인할 키 길이
 * @return 유효하면 1, 아니면 0
 */
AES_API int aes_is_valid_key_length(aes_keylen_t klen);

/**
 * @brief 키 길이에 따른 라운드 수 반환
 * 
 * 키 길이에 따라 필요한 라운드 수를 반환합니다.
 * 
 * @param klen 키 길이
 * @return 라운드 수 (오류 시 -1)
 */
AES_API int aes_get_rounds(aes_keylen_t klen);

/**
 * @brief 라이브러리 버전 정보 반환
 * 
 * 라이브러리의 버전 정보를 문자열로 반환합니다.
 * 
 * @return 버전 문자열
 */
AES_API const char* aes_get_version(void);

#endif /* CRYPTO_AES_H */