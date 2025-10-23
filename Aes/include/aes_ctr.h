/* aes_ctr.h - AES-CTR 모드 헤더 */
#ifndef AES_CTR_H
#define AES_CTR_H

#include "aes.h"
#include "ctr_mode.h"
#include "crypto_common.h"

/* CTR 모드 컨텍스트 */
typedef struct {
    aes_key_t ek;           /* AES 암호화 키 */
    ctr_ctx_t ctr;          /* 범용 CTR 컨텍스트 */
} aes_ctr_ctx_t;

/* CTR 모드 함수들 */
AES_API aes_err_t aes_ctr_init(aes_ctr_ctx_t *ctx,
                               const uint8_t *key, aes_keylen_t klen,
                               const uint8_t iv[AES_BLOCK_SIZE]);

AES_API aes_err_t aes_ctr_set_counter(aes_ctr_ctx_t *ctx,
                                      const uint8_t counter[AES_BLOCK_SIZE]);

AES_API void aes_ctr_get_counter(const aes_ctr_ctx_t *ctx,
                                 uint8_t counter[AES_BLOCK_SIZE]);

AES_API aes_err_t aes_ctr_crypt(aes_ctr_ctx_t *ctx,
                                const uint8_t *in, uint8_t *out, size_t len);

AES_API void aes_ctr_clear(aes_ctr_ctx_t *ctx);

#endif /* AES_CTR_H */
