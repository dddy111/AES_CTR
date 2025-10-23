/* aes_core.c - AES 핵심 암호화/복호화 구현 */
#include <stdint.h>
#include "../include/crypto_common.h"
#include "../include/aes_internal.h"
#include "../include/aes.h"

/* =============================================================================
 * 내부 헬퍼 함수들
 * ============================================================================= */

/**
 * @brief 16바이트 배열 복사
 * @param src 소스 배열 (16바이트)
 * @param dst 대상 배열 (16바이트)
 */
static void copy_16_bytes(const uint8_t src[16], uint8_t dst[16])
{
    for (int i = 0; i < 16; i++) {
        dst[i] = src[i];
    }
}

/*
 * 주의: aes_encrypt_round의 에러 스택 지원 버전만 사용합니다.
 * static 버전은 제거되었습니다.
 */

/**
 * @brief AES 암호화 라운드 실행 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 상태 배열
 * @param round_key 라운드 키
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_encrypt_round(aes_error_stack_t* error_stack, uint8_t state[16], const uint32_t *round_key)
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    // SubBytes
    aes_err_t result = aes_sub_bytes(error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(error_stack, result, "SubBytes failed in encrypt round");
        return aes_error_get_top(error_stack);
    }
    
    // ShiftRows
    result = aes_shift_rows(error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(error_stack, result, "ShiftRows failed in encrypt round");
        return aes_error_get_top(error_stack);
    }
    
    // MixColumns
    result = aes_mix_columns(error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(error_stack, result, "MixColumns failed in encrypt round");
        return aes_error_get_top(error_stack);
    }
    
    // AddRoundKey
    aes_add_round_key(state, round_key);
    
    return AES_OK;
}

/*
 * 주의: aes_decrypt_round의 에러 스택 지원 버전만 사용합니다.
 * static 버전은 제거되었습니다.
 */

/**
 * @brief AES 복호화 라운드 실행 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 상태 배열
 * @param round_key 라운드 키
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_decrypt_round(aes_error_stack_t* error_stack, uint8_t state[16], const uint32_t *round_key)
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    // InvShiftRows
    aes_err_t result = aes_inv_shift_rows(error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(error_stack, result, "InvShiftRows failed in decrypt round");
        return aes_error_get_top(error_stack);
    }
    
    // InvSubBytes
    result = aes_inv_sub_bytes(error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(error_stack, result, "InvSubBytes failed in decrypt round");
        return aes_error_get_top(error_stack);
    }
    
    // AddRoundKey
    aes_add_round_key(state, round_key);
    
    // InvMixColumns
    result = aes_inv_mix_columns(error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(error_stack, result, "InvMixColumns failed in decrypt round");
        return aes_error_get_top(error_stack);
    }
    
    return AES_OK;
}

/* =============================================================================
 * 공개 API 함수들
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
 */
aes_err_t aes_encrypt_block(const aes_key_t *ek, 
                           const uint8_t in[AES_BLOCK_SIZE], 
                           uint8_t out[AES_BLOCK_SIZE])
{
    aes_error_stack_t error_stack;
    AES_ERROR_INIT(&error_stack);
    
    // 매개변수 유효성 검사
    if (!ek || !in || !out) {
        AES_ERROR_PUSH(&error_stack, AES_ERR_BAD_PARAM, "NULL parameter detected");
        return aes_error_get_top(&error_stack);
    }
    
    if (ek->nr == 0) {
        AES_ERROR_PUSH(&error_stack, AES_ERR_NOT_INIT, "Key not initialized");
        return aes_error_get_top(&error_stack);
    }
    
    uint8_t state[16];
    
    // 1. 입력을 상태 배열로 복사
    copy_16_bytes(in, state);
    
    // 2. 초기 AddRoundKey (라운드 0)
    aes_add_round_key(state, &ek->rk[0]);
    
    // 3. 라운드 1 ~ Nr-1 (일반 라운드)
    for (int round = 1; round < (int)ek->nr; round++) {
        aes_err_t result = aes_encrypt_round(&error_stack, state, &ek->rk[4 * round]);
        if (result != AES_OK) {
            AES_ERROR_PUSH(&error_stack, result, "Encrypt round failed");
            return aes_error_get_top(&error_stack);
        }
    }
    
    // 4. 마지막 라운드 (MixColumns 제외)
    aes_err_t result = aes_sub_bytes(&error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(&error_stack, result, "SubBytes failed in final round");
        return aes_error_get_top(&error_stack);
    }
    
    result = aes_shift_rows(&error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(&error_stack, result, "ShiftRows failed in final round");
        return aes_error_get_top(&error_stack);
    }
    
    aes_add_round_key(state, &ek->rk[4 * ek->nr]);
    
    // 5. 결과를 출력에 복사
    copy_16_bytes(state, out);
    
    return AES_OK;
}

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
 */
aes_err_t aes_decrypt_block(const aes_key_t *dk, 
                           const uint8_t in[AES_BLOCK_SIZE], 
                           uint8_t out[AES_BLOCK_SIZE])
{
    aes_error_stack_t error_stack;
    AES_ERROR_INIT(&error_stack);
    
    // 매개변수 유효성 검사
    if (!dk || !in || !out) {
        AES_ERROR_PUSH(&error_stack, AES_ERR_BAD_PARAM, "NULL parameter detected");
        return aes_error_get_top(&error_stack);
    }
    
    if (dk->nr == 0) {
        AES_ERROR_PUSH(&error_stack, AES_ERR_NOT_INIT, "Key not initialized");
        return aes_error_get_top(&error_stack);
    }
    
    uint8_t state[16];
    
    // 1. 입력을 상태 배열로 복사
    copy_16_bytes(in, state);
    
    // 2. 초기 AddRoundKey (마지막 라운드키)
    aes_add_round_key(state, &dk->rk[4 * dk->nr]);
    
    // 3. 라운드 Nr-1 ~ 1 (일반 라운드)
    for (int round = dk->nr - 1; round > 0; round--) {
        aes_err_t result = aes_decrypt_round(&error_stack, state, &dk->rk[4 * round]);
        if (result != AES_OK) {
            AES_ERROR_PUSH(&error_stack, result, "Decrypt round failed");
            return aes_error_get_top(&error_stack);
        }
    }
    
    // 4. 마지막 라운드 (InvMixColumns 제외)
    aes_err_t result = aes_inv_shift_rows(&error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(&error_stack, result, "InvShiftRows failed in final round");
        return aes_error_get_top(&error_stack);
    }
    
    result = aes_inv_sub_bytes(&error_stack, state);
    if (result != AES_OK) {
        AES_ERROR_PUSH(&error_stack, result, "InvSubBytes failed in final round");
        return aes_error_get_top(&error_stack);
    }
    
    aes_add_round_key(state, &dk->rk[0]);
    
    // 5. 결과를 출력에 복사
    copy_16_bytes(state, out);
    
    return AES_OK;
}