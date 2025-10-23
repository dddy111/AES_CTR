/* ctr_mode.c - 범용 CTR 모드 구현 */
#include "ctr_mode.h"
#include "crypto_common.h"
#include <string.h>

/* CTR 초기화 */
aes_err_t ctr_init(ctr_ctx_t *ctx,
                   void *key,
                   block_cipher_encrypt_t encrypt_fn,
                   const uint8_t iv[16])
{
    if (!ctx || !key || !encrypt_fn || !iv) {
        return AES_ERR_BAD_PARAM;
    }
    
    ctx->key = key;
    ctx->encrypt_fn = encrypt_fn;
    memcpy(ctx->counter, iv, 16);
    
    return AES_OK;
}

/* 카운터 재설정 */
aes_err_t ctr_set_counter(ctr_ctx_t *ctx, const uint8_t counter[16])
{
    if (!ctx || !counter) {
        return AES_ERR_BAD_PARAM;
    }
    
    memcpy(ctx->counter, counter, 16);
    
    return AES_OK;
}

/* 현재 카운터 값 조회 */
void ctr_get_counter(const ctr_ctx_t *ctx, uint8_t counter[16])
{
    if (ctx && counter) {
        memcpy(counter, ctx->counter, 16);
    }
}

/* 카운터 증가 (빅엔디안 16바이트) */
static void increment_counter(uint8_t counter[16])
{
    for (int i = 15; i >= 0; i--) {
        if (++counter[i] != 0) {
            break; /* 오버플로우 없음 */
        }
    }
}

/* 패딩 적용 (PKCS#7 패딩) - 16바이트 미만만 처리 */
static void apply_padding(const uint8_t *in, size_t len, uint8_t out[16])
{
    if (len >= 16) {
        // 16바이트 이상은 패딩 불필요
        memcpy(out, in, 16);
        return;
    }
    
    // 입력 데이터 복사
    memcpy(out, in, len);
    
    // 패딩 바이트 계산
    uint8_t padding = 16 - len;
    
    // 패딩 적용
    for (size_t i = len; i < 16; i++) {
        out[i] = padding;
    }
}

/* 패딩 제거 */
static size_t remove_padding(const uint8_t in[16])
{
    uint8_t padding = in[15];
    
    // 패딩 유효성 검사
    if (padding == 0 || padding > 16) {
        return 16; // 잘못된 패딩, 전체 16바이트 반환
    }
    
    // 패딩 바이트들이 모두 같은지 확인
    for (int i = 16 - padding; i < 16; i++) {
        if (in[i] != padding) {
            return 16; // 잘못된 패딩, 전체 16바이트 반환
        }
    }
    
    return 16 - padding; // 실제 데이터 길이
}

/* CTR 암/복호화 (16바이트 단위) */
aes_err_t ctr_crypt(ctr_ctx_t *ctx,
                    const uint8_t *in, uint8_t *out, size_t len)
{
    if (!ctx || !in || !out || len == 0) {
        return AES_ERR_BAD_PARAM;
    }
    
    // 16바이트 단위로 처리
    if (len != 16) {
        return AES_ERR_BAD_PARAM; // 패딩이 적용되어야 함
    }
    
    // 카운터로 키스트림 생성
    uint8_t keystream[16];
    ctx->encrypt_fn(ctx->key, ctx->counter, keystream);
    
    // XOR 연산으로 암/복호화
    for (int i = 0; i < 16; i++) {
        out[i] = in[i] ^ keystream[i];
    }
    
    // 카운터 증가
    increment_counter(ctx->counter);
    
    return AES_OK;
}

/* 컨텍스트 내부 민감 정보 삭제 */
void ctr_clear(ctr_ctx_t *ctx)
{
    if (ctx) {
        /* 카운터를 0으로 덮어쓰기 */
        memset(ctx->counter, 0, sizeof(ctx->counter));
        ctx->key = NULL;
        ctx->encrypt_fn = NULL;
    }
}

