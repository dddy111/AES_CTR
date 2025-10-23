/* aes_internal.h - AES 내부 헤더 (구현 세부사항) */
#ifndef AES_INTERNAL_H
#define AES_INTERNAL_H

#include "crypto_common.h"

/* =============================================================================
 * 내부 상수 정의
 * ============================================================================= */

/** @brief S-Box 크기 */
#define AES_SBOX_SIZE 256

/** @brief Rcon 상수 개수 */
#define AES_RCON_SIZE 11

/** @brief AES 상태 배열 크기 */
#define AES_STATE_SIZE 16

/* =============================================================================
 * S-Box 및 Rcon 상수
 * ============================================================================= */

/**
 * @brief AES S-Box 테이블
 * 
 * 8비트 입력을 8비트 출력으로 변환하는 비선형 치환 테이블입니다.
 * 이는 AES의 비선형성을 제공하는 핵심 요소입니다.
 */
extern const uint8_t aes_sbox[AES_SBOX_SIZE];

/**
 * @brief AES 역 S-Box 테이블
 * 
 * S-Box의 역변환으로, 복호화 시 사용됩니다.
 * S-Box와 역 S-Box는 서로 역함수 관계입니다.
 */
extern const uint8_t aes_inv_sbox[AES_SBOX_SIZE];

/**
 * @brief Rcon 상수 테이블
 * 
 * 키 스케줄링에서 사용되는 라운드 상수들입니다.
 * 각 라운드마다 다른 상수를 사용하여 키의 확산성을 높입니다.
 */
extern const uint8_t aes_rcon[AES_RCON_SIZE];

/* =============================================================================
 * S-Box 변환 함수들
 * ============================================================================= */

/**
 * @brief S-Box를 사용한 바이트 치환
 * @param byte 입력 바이트 (0-255)
 * @return S-Box 치환 결과
 */
uint8_t aes_sub_byte(uint8_t byte);

/**
 * @brief 역 S-Box를 사용한 바이트 치환
 * @param byte 입력 바이트 (0-255)
 * @return 역 S-Box 치환 결과
 */
uint8_t aes_inv_sub_byte(uint8_t byte);

/**
 * @brief SubBytes 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_sub_bytes(aes_error_stack_t* error_stack, uint8_t state[AES_STATE_SIZE]);

/**
 * @brief InvSubBytes 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_inv_sub_bytes(aes_error_stack_t* error_stack, uint8_t state[AES_STATE_SIZE]);

/* =============================================================================
 * MixColumns 및 ShiftRows 변환 함수들
 * ============================================================================= */

/**
 * @brief MixColumns 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_mix_columns(aes_error_stack_t* error_stack, uint8_t state[AES_STATE_SIZE]);

/**
 * @brief InvMixColumns 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_inv_mix_columns(aes_error_stack_t* error_stack, uint8_t state[AES_STATE_SIZE]);

/**
 * @brief ShiftRows 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_shift_rows(aes_error_stack_t* error_stack, uint8_t state[AES_STATE_SIZE]);

/**
 * @brief InvShiftRows 변환 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 16바이트 상태 배열
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_inv_shift_rows(aes_error_stack_t* error_stack, uint8_t state[AES_STATE_SIZE]);

/**
 * @brief AddRoundKey 변환
 * 
 * 현재 상태와 라운드 키를 XOR 연산합니다.
 * 이는 AES의 유일한 비선형 변환이 아닌 연산입니다.
 * 
 * @param state 16바이트 상태 배열
 * @param round_key 4개의 32비트 워드로 구성된 라운드 키
 */
void aes_add_round_key(uint8_t state[AES_STATE_SIZE], const uint32_t *round_key);

/**
 * @brief AES 암호화 라운드 실행 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 상태 배열
 * @param round_key 라운드 키
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_encrypt_round(aes_error_stack_t* error_stack, uint8_t state[16], const uint32_t *round_key);

/**
 * @brief AES 복호화 라운드 실행 (에러 스택 지원)
 * @param error_stack 에러 스택
 * @param state 상태 배열
 * @param round_key 라운드 키
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_decrypt_round(aes_error_stack_t* error_stack, uint8_t state[16], const uint32_t *round_key);

/* =============================================================================
 * GF(2^8) 유한체 연산 함수들
 * ============================================================================= */

/**
 * @brief GF(2^8)에서 x 곱하기 (0x02 곱하기)
 * @param a 곱할 값
 * @return a * x in GF(2^8)
 */
uint8_t gf256_mul2(uint8_t a);

/**
 * @brief GF(2^8)에서 3 곱하기 (0x03 곱하기)
 * @param a 곱할 값
 * @return a * 3 in GF(2^8)
 */
uint8_t gf256_mul3(uint8_t a);

/**
 * @brief GF(2^8)에서 x^2 곱하기 (0x04 곱하기)
 * @param a 곱할 값
 * @return a * x^2 in GF(2^8)
 */
uint8_t gf256_mul4(uint8_t a);

/**
 * @brief GF(2^8)에서 x^3 곱하기 (0x08 곱하기)
 * @param a 곱할 값
 * @return a * x^3 in GF(2^8)
 */
uint8_t gf256_mul8(uint8_t a);

/**
 * @brief GF(2^8)에서 일반적인 곱셈
 * @param a 첫 번째 피연산자
 * @param b 두 번째 피연산자
 * @return a * b in GF(2^8)
 */
uint8_t gf256_mul(uint8_t a, uint8_t b);

/**
 * @brief GF(2^8)에서 역원 계산
 * @param a 역원을 구할 값
 * @return a^(-1) in GF(2^8), a가 0이면 0
 */
uint8_t gf256_inv(uint8_t a);

/**
 * @brief GF(2^8)에서 제곱
 * @param a 제곱할 값
 * @return a^2 in GF(2^8)
 */
uint8_t gf256_square(uint8_t a);

/**
 * @brief GF(2^8)에서 제곱근
 * @param a 제곱근을 구할 값
 * @return sqrt(a) in GF(2^8)
 */
uint8_t gf256_sqrt(uint8_t a);

#endif /* AES_INTERNAL_H */