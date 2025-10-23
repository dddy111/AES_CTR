/* aes_round.c - AES MixColumns 및 InvMixColumns 구현 */
#include <stdint.h>
#include "../include/crypto_common.h"
#include "../include/aes_internal.h"
#include "../include/gf256.h"

/* =============================================================================
 * 상수 정의
 * ============================================================================= */

#define STATE_SIZE 16  /* AES 상태 배열 크기 */
#define ROW_SIZE 4     /* 행 크기 */
#define COL_SIZE 4     /* 열 크기 */

/* =============================================================================
 * 내부 헬퍼 함수들
 * ============================================================================= */

/**
 * @brief 상태 배열의 특정 위치에 접근 (행, 열 인덱스)
 * @param state 상태 배열
 * @param row 행 인덱스 (0-3)
 * @param col 열 인덱스 (0-3)
 * @return 해당 위치의 바이트
 */
static uint8_t get_state_byte(const uint8_t state[STATE_SIZE], int row, int col)
{
    return state[row + col * ROW_SIZE];
}

/**
 * @brief 상태 배열의 특정 위치에 값 설정 (행, 열 인덱스)
 * @param state 상태 배열
 * @param row 행 인덱스 (0-3)
 * @param col 열 인덱스 (0-3)
 * @param value 설정할 값
 */
static void set_state_byte(uint8_t state[STATE_SIZE], int row, int col, uint8_t value)
{
    state[row + col * ROW_SIZE] = value;
}

/**
 * @brief MixColumns 변환을 한 열에 적용
 * @param state 상태 배열
 * @param col 열 인덱스 (0-3)
 * @param result 결과를 저장할 배열
 */
static void mix_column(const uint8_t state[STATE_SIZE], int col, uint8_t result[ROW_SIZE])
{
    // MixColumns 행렬 곱셈:
    // [02 03 01 01]   [s0]
    // [01 02 03 01] * [s1]
    // [01 01 02 03]   [s2]
    // [03 01 01 02]   [s3]
    
    uint8_t s0 = get_state_byte(state, 0, col);
    uint8_t s1 = get_state_byte(state, 1, col);
    uint8_t s2 = get_state_byte(state, 2, col);
    uint8_t s3 = get_state_byte(state, 3, col);
    
    result[0] = gf256_mul2(s0) ^ gf256_mul3(s1) ^ s2 ^ s3;
    result[1] = s0 ^ gf256_mul2(s1) ^ gf256_mul3(s2) ^ s3;
    result[2] = s0 ^ s1 ^ gf256_mul2(s2) ^ gf256_mul3(s3);
    result[3] = gf256_mul3(s0) ^ s1 ^ s2 ^ gf256_mul2(s3);
}

/**
 * @brief InvMixColumns 변환을 한 열에 적용
 * @param state 상태 배열
 * @param col 열 인덱스 (0-3)
 * @param result 결과를 저장할 배열
 */
static void inv_mix_column(const uint8_t state[STATE_SIZE], int col, uint8_t result[ROW_SIZE])
{
    // InvMixColumns 행렬 곱셈:
    // [0e 0b 0d 09]   [s0]
    // [09 0e 0b 0d] * [s1]
    // [0d 09 0e 0b]   [s2]
    // [0b 0d 09 0e]   [s3]
    
    uint8_t s0 = get_state_byte(state, 0, col);
    uint8_t s1 = get_state_byte(state, 1, col);
    uint8_t s2 = get_state_byte(state, 2, col);
    uint8_t s3 = get_state_byte(state, 3, col);
    
    result[0] = gf256_mul(s0, 0x0e) ^ gf256_mul(s1, 0x0b) ^ gf256_mul(s2, 0x0d) ^ gf256_mul(s3, 0x09);
    result[1] = gf256_mul(s0, 0x09) ^ gf256_mul(s1, 0x0e) ^ gf256_mul(s2, 0x0b) ^ gf256_mul(s3, 0x0d);
    result[2] = gf256_mul(s0, 0x0d) ^ gf256_mul(s1, 0x09) ^ gf256_mul(s2, 0x0e) ^ gf256_mul(s3, 0x0b);
    result[3] = gf256_mul(s0, 0x0b) ^ gf256_mul(s1, 0x0d) ^ gf256_mul(s2, 0x09) ^ gf256_mul(s3, 0x0e);
}

/**
 * @brief 한 행을 왼쪽으로 시프트 (AES ShiftRows)
 * @param state 상태 배열
 * @param row 행 인덱스 (0-3)
 * @param shift_amount 시프트 양 (1-3)
 */
static void aes_shift_row(uint8_t state[STATE_SIZE], int row, int shift_amount)
{
    uint8_t temp[ROW_SIZE];
    
    // 현재 행의 값을 임시 배열에 복사
    for (int col = 0; col < ROW_SIZE; col++) {
        temp[col] = get_state_byte(state, row, col);
    }
    
    // 왼쪽으로 시프트
    for (int col = 0; col < ROW_SIZE; col++) {
        int new_col = (col + shift_amount) % ROW_SIZE;
        set_state_byte(state, row, new_col, temp[col]);
    }
}

/**
 * @brief 한 행을 오른쪽으로 시프트 (AES InvShiftRows)
 * @param state 상태 배열
 * @param row 행 인덱스 (0-3)
 * @param shift_amount 시프트 양 (1-3)
 */
static void aes_inv_shift_row(uint8_t state[STATE_SIZE], int row, int shift_amount)
{
    uint8_t temp[ROW_SIZE];
    
    // 현재 행의 값을 임시 배열에 복사
    for (int col = 0; col < ROW_SIZE; col++) {
        temp[col] = get_state_byte(state, row, col);
    }
    
    // 오른쪽으로 시프트
    for (int col = 0; col < ROW_SIZE; col++) {
        int new_col = (col - shift_amount + ROW_SIZE) % ROW_SIZE;
        set_state_byte(state, row, new_col, temp[col]);
    }
}

/* =============================================================================
 * 공개 API 함수들
 * ============================================================================= */





/**
 * @brief AddRoundKey 변환
 * 
 * 현재 상태와 라운드 키를 XOR 연산합니다.
 * 이는 AES의 유일한 비선형 변환이 아닌 연산입니다.
 * 
 * @param state 16바이트 상태 배열
 * @param round_key 4개의 32비트 워드로 구성된 라운드 키
 */
void aes_add_round_key(uint8_t state[STATE_SIZE], const uint32_t *round_key)
{
    for (int i = 0; i < ROW_SIZE; i++) {
        uint32_t key_word = round_key[i];
        
        // 32비트 워드를 4바이트로 분해하여 XOR
        state[4*i + 0] ^= (key_word >> 24) & 0xff;  // MSB
        state[4*i + 1] ^= (key_word >> 16) & 0xff;
        state[4*i + 2] ^= (key_word >> 8) & 0xff;
        state[4*i + 3] ^= key_word & 0xff;          // LSB
    }
}

/* =============================================================================
 * 에러 스택 지원 함수들
 * ============================================================================= */

/**
 * @brief SubBytes 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_sub_bytes(aes_error_stack_t* error_stack, uint8_t state[STATE_SIZE])
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (!state) {
        AES_ERROR_PUSH(error_stack, AES_ERR_BAD_PARAM, "NULL state array");
        return aes_error_get_top(error_stack);
    }
    
    for (int i = 0; i < STATE_SIZE; i++) {
        state[i] = aes_sub_byte(state[i]);
    }
    
    return AES_OK;
}

/**
 * @brief ShiftRows 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_shift_rows(aes_error_stack_t* error_stack, uint8_t state[STATE_SIZE])
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (!state) {
        AES_ERROR_PUSH(error_stack, AES_ERR_BAD_PARAM, "NULL state array");
        return aes_error_get_top(error_stack);
    }
    
    // 1행: 1바이트 왼쪽 시프트
    aes_shift_row(state, 1, 1);
    
    // 2행: 2바이트 왼쪽 시프트
    aes_shift_row(state, 2, 2);
    
    // 3행: 3바이트 왼쪽 시프트
    aes_shift_row(state, 3, 3);
    
    return AES_OK;
}

/**
 * @brief MixColumns 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_mix_columns(aes_error_stack_t* error_stack, uint8_t state[STATE_SIZE])
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (!state) {
        AES_ERROR_PUSH(error_stack, AES_ERR_BAD_PARAM, "NULL state array");
        return aes_error_get_top(error_stack);
    }
    
    for (int col = 0; col < COL_SIZE; col++) {
        uint8_t result[ROW_SIZE];
        mix_column(state, col, result);
        
        // 결과를 상태 배열에 복사
        for (int row = 0; row < ROW_SIZE; row++) {
            set_state_byte(state, row, col, result[row]);
        }
    }
    
    return AES_OK;
}

/**
 * @brief InvSubBytes 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_inv_sub_bytes(aes_error_stack_t* error_stack, uint8_t state[STATE_SIZE])
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (!state) {
        AES_ERROR_PUSH(error_stack, AES_ERR_BAD_PARAM, "NULL state array");
        return aes_error_get_top(error_stack);
    }
    
    for (int i = 0; i < STATE_SIZE; i++) {
        state[i] = aes_inv_sub_byte(state[i]);
    }
    
    return AES_OK;
}

/**
 * @brief InvShiftRows 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_inv_shift_rows(aes_error_stack_t* error_stack, uint8_t state[STATE_SIZE])
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (!state) {
        AES_ERROR_PUSH(error_stack, AES_ERR_BAD_PARAM, "NULL state array");
        return aes_error_get_top(error_stack);
    }
    
    // 1행: 1바이트 오른쪽 시프트
    aes_inv_shift_row(state, 1, 1);
    
    // 2행: 2바이트 오른쪽 시프트
    aes_inv_shift_row(state, 2, 2);
    
    // 3행: 3바이트 오른쪽 시프트
    aes_inv_shift_row(state, 3, 3);
    
    return AES_OK;
}

/**
 * @brief InvMixColumns 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_inv_mix_columns(aes_error_stack_t* error_stack, uint8_t state[STATE_SIZE])
{
    if (!error_stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (!state) {
        AES_ERROR_PUSH(error_stack, AES_ERR_BAD_PARAM, "NULL state array");
        return aes_error_get_top(error_stack);
    }
    
    for (int col = 0; col < COL_SIZE; col++) {
        uint8_t result[ROW_SIZE];
        inv_mix_column(state, col, result);
        
        // 결과를 상태 배열에 복사
        for (int row = 0; row < ROW_SIZE; row++) {
            set_state_byte(state, row, col, result[row]);
        }
    }
    
    return AES_OK;
}