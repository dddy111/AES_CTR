/* ctr_mode.h - 범용 CTR 모드 헤더 */
#ifndef CTR_MODE_H
#define CTR_MODE_H

#include "crypto_common.h"

/* 블록 암호화 함수 타입 */
typedef void (*block_cipher_encrypt_t)(const void *key, 
                                       const uint8_t in[16], 
                                       uint8_t out[16]);

/* CTR 모드 컨텍스트 */
typedef struct {
    void *key;                          /* 블록 암호 키 */
    block_cipher_encrypt_t encrypt_fn;  /* 블록 암호화 함수 */
    uint8_t counter[16];                /* 현재 카운터 */
} ctr_ctx_t;

/* CTR 모드 함수들 */
AES_API aes_err_t ctr_init(ctr_ctx_t *ctx,
                           void *key,
                           block_cipher_encrypt_t encrypt_fn,
                           const uint8_t iv[16]);

AES_API aes_err_t ctr_set_counter(ctr_ctx_t *ctx, const uint8_t counter[16]);

AES_API void ctr_get_counter(const ctr_ctx_t *ctx, uint8_t counter[16]);

AES_API aes_err_t ctr_crypt(ctr_ctx_t *ctx,
                            const uint8_t *in, uint8_t *out, size_t len);

AES_API void ctr_clear(ctr_ctx_t *ctx);

#endif /* CTR_MODE_H */
