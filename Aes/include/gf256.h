/* gf256.h - GF(2^8) 유한체 연산 헤더 */
#ifndef GF256_H
#define GF256_H

#include <stdint.h>

/* =============================================================================
 * GF(2^8) 유한체 연산 함수들
 * ============================================================================= */

/**
 * @brief GF(2^8)에서 x 곱하기 (0x02 곱하기)
 * 
 * 이는 AES MixColumns에서 자주 사용되는 연산입니다.
 * x 곱하기는 왼쪽 시프트 후 기약다항식으로 모듈로 감소하는 것입니다.
 * 
 * @param a 곱할 값
 * @return a * x in GF(2^8)
 */
uint8_t gf256_mul2(uint8_t a);

/**
 * @brief GF(2^8)에서 3 곱하기 (0x03 곱하기)
 * 
 * 3 = 2 + 1이므로, x 곱하기와 원래 값을 XOR합니다.
 * 이는 AES MixColumns에서 자주 사용됩니다.
 * 
 * @param a 곱할 값
 * @return a * 3 in GF(2^8)
 */
uint8_t gf256_mul3(uint8_t a);

/**
 * @brief GF(2^8)에서 x^2 곱하기 (0x04 곱하기)
 * 
 * x^2 곱하기는 x 곱하기를 두 번 적용하는 것입니다.
 * 
 * @param a 곱할 값
 * @return a * x^2 in GF(2^8)
 */
uint8_t gf256_mul4(uint8_t a);

/**
 * @brief GF(2^8)에서 x^3 곱하기 (0x08 곱하기)
 * 
 * x^3 곱하기는 x^2 곱하기 후 x 곱하기를 적용하는 것입니다.
 * 
 * @param a 곱할 값
 * @return a * x^3 in GF(2^8)
 */
uint8_t gf256_mul8(uint8_t a);

/**
 * @brief GF(2^8)에서 일반적인 곱셈
 * 
 * 이진 곱셈 알고리즘을 사용하여 두 값을 곱합니다.
 * 이는 모든 GF(2^8) 곱셈의 기본이 되는 함수입니다.
 * 
 * @param a 첫 번째 피연산자
 * @param b 두 번째 피연산자
 * @return a * b in GF(2^8)
 */
uint8_t gf256_mul(uint8_t a, uint8_t b);

/**
 * @brief GF(2^8)에서 역원 계산
 * 
 * 테이블 룩업을 사용하여 빠르게 역원을 계산합니다.
 * 0의 역원은 정의되지 않으므로 0을 반환합니다.
 * 
 * @param a 역원을 구할 값
 * @return a^(-1) in GF(2^8), a가 0이면 0
 */
uint8_t gf256_inv(uint8_t a);

/**
 * @brief GF(2^8)에서 제곱
 * 
 * 제곱은 곱셈의 특별한 경우로, 같은 값을 곱하는 것입니다.
 * 
 * @param a 제곱할 값
 * @return a^2 in GF(2^8)
 */
uint8_t gf256_square(uint8_t a);

/**
 * @brief GF(2^8)에서 제곱근
 * 
 * GF(2^8)에서 제곱근은 a^(128)과 같습니다.
 * 이는 7번의 제곱 연산으로 계산할 수 있습니다.
 * 
 * @param a 제곱근을 구할 값
 * @return sqrt(a) in GF(2^8)
 */
uint8_t gf256_sqrt(uint8_t a);

#endif /* GF256_H */