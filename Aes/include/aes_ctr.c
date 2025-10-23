/* aes_ctr.c - AES-CTR 모드 래퍼 구현 */
#include "aes_ctr.h"
#include "aes.h"
#include "ctr_mode.h"
#include "crypto_common.h"
#include <string.h>

/* AES 블록 암호화 함수 (범용 CTR 모드용) */
static void aes_encrypt_wrapper(const void *key, 
                                const uint8_t in[16], 
                                uint8_t out[16])
{
    const aes_key_t *aes_key = (const aes_key_t *)key;
    aes_encrypt_block(aes_key, in, out);
}

/* AES-CTR 초기화 */
aes_err_t aes_ctr_init(aes_ctr_ctx_t *ctx,
                       const uint8_t *key, aes_keylen_t klen,
                       const uint8_t iv[AES_BLOCK_SIZE])
{
    if (!ctx || !key || !iv) {
        return AES_ERR_BAD_PARAM;
    }
    
    /* AES 키 설정 */
    aes_err_t err = aes_set_encrypt_key(&ctx->ek, key, klen);
    if (err != AES_OK) {
        return err;
    }
    
    /* 범용 CTR 모드 초기화 */
    err = ctr_init(&ctx->ctr, &ctx->ek, aes_encrypt_wrapper, iv);
    if (err != AES_OK) {
        aes_key_clear(&ctx->ek);
        return err;
    }
    
    return AES_OK;
}

/* 카운터 재설정 */
aes_err_t aes_ctr_set_counter(aes_ctr_ctx_t *ctx,
                              const uint8_t counter[AES_BLOCK_SIZE])
{
    if (!ctx || !counter) {
        return AES_ERR_BAD_PARAM;
    }
    
    return ctr_set_counter(&ctx->ctr, counter);
}

/* 현재 카운터 값 조회 */
void aes_ctr_get_counter(const aes_ctr_ctx_t *ctx,
                         uint8_t counter[AES_BLOCK_SIZE])
{
    if (ctx && counter) {
        ctr_get_counter(&ctx->ctr, counter);
    }
}

/* AES-CTR 암/복호화 (패딩 적용) */
aes_err_t aes_ctr_crypt(aes_ctr_ctx_t *ctx,
                        const uint8_t *in, uint8_t *out, size_t len)
{
    if (!ctx || !in || !out || len == 0) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (len > 16) {
        return AES_ERR_BAD_PARAM; // 16바이트 초과는 지원하지 않음
    }
    
    // 패딩 적용하여 16바이트로 만들기
    uint8_t padded_input[16];
    
    if (len < 16) {
        // 16바이트 미만: 패딩 적용
        memcpy(padded_input, in, len);
        uint8_t padding = 16 - len;
        for (size_t i = len; i < 16; i++) {
            padded_input[i] = padding;
        }
    } else {
        // 정확히 16바이트: 패딩 없음
        memcpy(padded_input, in, 16);
    }
    
    // 16바이트 단위로 암호화
    return ctr_crypt(&ctx->ctr, padded_input, out, 16);
}

/* 컨텍스트 내부 민감 정보 삭제 */
void aes_ctr_clear(aes_ctr_ctx_t *ctx)
{
    if (ctx) {
        ctr_clear(&ctx->ctr);
        aes_key_clear(&ctx->ek);
    }
}

