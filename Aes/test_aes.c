#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "include/aes.h"
#include "include/aes_ctr.h"
#include "include/crypto_common.h"

void print_hex(const char* label, const uint8_t* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void print_string(const char* label, const uint8_t* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        if (data[i] >= 32 && data[i] <= 126) {
            printf("%c", data[i]);
        } else {
            printf("\\x%02x", data[i]);
        }
    }
    printf("\n");
}

int test_aes_ctr_padding() {
    printf("\n=== AES-CTR 패딩 테스트 ===\n");
    
    uint8_t key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                       0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    uint8_t iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    
    // 다양한 길이의 테스트 데이터
    struct {
        const char* name;
        const uint8_t* data;
        size_t len;
    } test_cases[] = {
        {"5바이트", (const uint8_t*)"Hello", 5},
        {"10바이트", (const uint8_t*)"HelloWorld", 10},
        {"15바이트", (const uint8_t*)"HelloWorld12345", 15},
        {"16바이트", (const uint8_t*)"HelloWorld123456", 16}
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int success = 1;
    
    printf("키 길이: 16 바이트\n");
    print_hex("키", key, 16);
    print_hex("IV", iv, 16);
    
    for (int i = 0; i < num_tests; i++) {
        printf("\n--- 테스트 %d: %s ---\n", i + 1, test_cases[i].name);
        
        const uint8_t* plaintext = test_cases[i].data;
        size_t plaintext_len = test_cases[i].len;
        
        print_string("평문", plaintext, plaintext_len);
        printf("평문 길이: %zu 바이트\n", plaintext_len);
        
        // 암호화
        aes_ctr_ctx_t enc_ctx;
        aes_err_t err = aes_ctr_init(&enc_ctx, key, AES_128, iv);
        if (err != AES_OK) {
            printf("❌ CTR 초기화 실패: %d\n", err);
            success = 0;
            continue;
        }
        
        uint8_t ciphertext[16];
        err = aes_ctr_crypt(&enc_ctx, plaintext, ciphertext, plaintext_len);
        if (err != AES_OK) {
            printf("❌ 암호화 실패: %d\n", err);
            aes_ctr_clear(&enc_ctx);
            success = 0;
            continue;
        }
        
        print_hex("암호문 (16바이트)", ciphertext, 16);
        
        // 복호화
        aes_ctr_ctx_t dec_ctx;
        err = aes_ctr_init(&dec_ctx, key, AES_128, iv);
        if (err != AES_OK) {
            printf("❌ 복호화용 CTR 초기화 실패: %d\n", err);
            aes_ctr_clear(&enc_ctx);
            success = 0;
            continue;
        }
        
        uint8_t decrypted[16];
        err = aes_ctr_crypt(&dec_ctx, ciphertext, decrypted, 16);
        if (err != AES_OK) {
            printf("❌ 복호화 실패: %d\n", err);
            aes_ctr_clear(&enc_ctx);
            aes_ctr_clear(&dec_ctx);
            success = 0;
            continue;
        }
        
        print_hex("복호문 (16바이트)", decrypted, 16);
        
        // 원본과 비교 (패딩 제거)
        int match = 1;
        if (plaintext_len < 16) {
            // 패딩이 있는 경우: 원본 길이만큼만 비교
            for (size_t j = 0; j < plaintext_len; j++) {
                if (plaintext[j] != decrypted[j]) {
                    match = 0;
                    break;
                }
            }
            
            // 패딩 부분 확인
            uint8_t expected_padding = 16 - plaintext_len;
            for (size_t j = plaintext_len; j < 16; j++) {
                if (decrypted[j] != expected_padding) {
                    match = 0;
                    break;
                }
            }
        } else {
            // 16바이트인 경우: 전체 비교
            for (size_t j = 0; j < 16; j++) {
                if (plaintext[j] != decrypted[j]) {
                    match = 0;
                    break;
                }
            }
        }
        
        if (match) {
            printf("✅ 테스트 %d 성공!\n", i + 1);
        } else {
            printf("❌ 테스트 %d 실패!\n", i + 1);
            success = 0;
        }
        
        aes_ctr_clear(&enc_ctx);
        aes_ctr_clear(&dec_ctx);
    }
    
    if (success) {
        printf("\n✅ 모든 패딩 테스트 성공!\n");
    } else {
        printf("\n❌ 일부 패딩 테스트 실패!\n");
    }
    
    return success;
}

int test_aes_ctr_different_keys() {
    printf("\n=== AES-CTR 다양한 키 길이 테스트 ===\n");
    
    struct {
        aes_keylen_t key_len;
        const char* name;
        uint8_t key[32];
    } key_tests[] = {
        {AES_128, "AES-128", {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                              0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10}},
        {AES_192, "AES-192", {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                              0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
                              0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18}},
        {AES_256, "AES-256", {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                              0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
                              0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                              0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20}}
    };
    
    uint8_t iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    
    const char* test_message = "AES CTR Test";
    size_t message_len = strlen(test_message);
    
    int num_tests = sizeof(key_tests) / sizeof(key_tests[0]);
    int success = 1;
    
    for (int i = 0; i < num_tests; i++) {
        printf("\n--- %s 테스트 ---\n", key_tests[i].name);
        
        print_hex("키", key_tests[i].key, (int)key_tests[i].key_len);
        print_hex("IV", iv, 16);
        print_string("평문", (const uint8_t*)test_message, message_len);
        
        // 암호화
        aes_ctr_ctx_t enc_ctx;
        aes_err_t err = aes_ctr_init(&enc_ctx, key_tests[i].key, key_tests[i].key_len, iv);
        if (err != AES_OK) {
            printf("❌ CTR 초기화 실패: %d\n", err);
            success = 0;
            continue;
        }
        
        uint8_t ciphertext[16];
        err = aes_ctr_crypt(&enc_ctx, (const uint8_t*)test_message, ciphertext, message_len);
        if (err != AES_OK) {
            printf("❌ 암호화 실패: %d\n", err);
            aes_ctr_clear(&enc_ctx);
            success = 0;
            continue;
        }
        
        print_hex("암호문", ciphertext, 16);
        
        // 복호화
        aes_ctr_ctx_t dec_ctx;
        err = aes_ctr_init(&dec_ctx, key_tests[i].key, key_tests[i].key_len, iv);
        if (err != AES_OK) {
            printf("❌ 복호화용 CTR 초기화 실패: %d\n", err);
            aes_ctr_clear(&enc_ctx);
            success = 0;
            continue;
        }
        
        uint8_t decrypted[16];
        err = aes_ctr_crypt(&dec_ctx, ciphertext, decrypted, 16);
        if (err != AES_OK) {
            printf("❌ 복호화 실패: %d\n", err);
            aes_ctr_clear(&enc_ctx);
            aes_ctr_clear(&dec_ctx);
            success = 0;
            continue;
        }
        
        print_hex("복호문", decrypted, 16);
        
        // 결과 확인
        int match = 1;
        for (size_t j = 0; j < message_len; j++) {
            if (test_message[j] != decrypted[j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            printf("✅ %s 테스트 성공!\n", key_tests[i].name);
        } else {
            printf("❌ %s 테스트 실패!\n", key_tests[i].name);
            success = 0;
        }
        
        aes_ctr_clear(&enc_ctx);
        aes_ctr_clear(&dec_ctx);
    }
    
    if (success) {
        printf("\n✅ 모든 키 길이 테스트 성공!\n");
    } else {
        printf("\n❌ 일부 키 길이 테스트 실패!\n");
    }
    
    return success;
}

int test_aes_ctr_counter_operations() {
    printf("\n=== AES-CTR 카운터 연산 테스트 ===\n");
    
    uint8_t key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                       0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    uint8_t iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    
    aes_ctr_ctx_t ctx;
    aes_err_t err = aes_ctr_init(&ctx, key, AES_128, iv);
    if (err != AES_OK) {
        printf("❌ CTR 초기화 실패: %d\n", err);
        return 0;
    }
    
    // 초기 카운터 확인
    uint8_t counter[16];
    aes_ctr_get_counter(&ctx, counter);
    print_hex("초기 카운터", counter, 16);
    
    // 첫 번째 암호화
    const char* test1 = "First block";
    uint8_t cipher1[16];
    err = aes_ctr_crypt(&ctx, (const uint8_t*)test1, cipher1, strlen(test1));
    if (err != AES_OK) {
        printf("❌ 첫 번째 암호화 실패: %d\n", err);
        aes_ctr_clear(&ctx);
        return 0;
    }
    
    aes_ctr_get_counter(&ctx, counter);
    print_hex("첫 번째 암호화 후 카운터", counter, 16);
    
    // 두 번째 암호화
    const char* test2 = "Second block";
    uint8_t cipher2[16];
    err = aes_ctr_crypt(&ctx, (const uint8_t*)test2, cipher2, strlen(test2));
    if (err != AES_OK) {
        printf("❌ 두 번째 암호화 실패: %d\n", err);
        aes_ctr_clear(&ctx);
        return 0;
    }
    
    aes_ctr_get_counter(&ctx, counter);
    print_hex("두 번째 암호화 후 카운터", counter, 16);
    
    // 카운터가 증가했는지 확인
    uint8_t expected_counter[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x11}; // +2 증가
    
    int counter_match = (memcmp(counter, expected_counter, 16) == 0);
    if (counter_match) {
        printf("✅ 카운터 증가 테스트 성공!\n");
    } else {
        printf("❌ 카운터 증가 테스트 실패!\n");
        print_hex("예상 카운터", expected_counter, 16);
    }
    
    aes_ctr_clear(&ctx);
    return counter_match;
}

int test_aes_ctr_error_handling() {
    printf("\n=== AES-CTR 에러 처리 테스트 ===\n");
    
    uint8_t key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                       0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    uint8_t iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    
    int success = 1;
    
    // NULL 포인터 테스트
    printf("--- NULL 포인터 테스트 ---\n");
    aes_ctr_ctx_t ctx;
    aes_err_t err = aes_ctr_init(NULL, key, AES_128, iv);
    if (err == AES_ERR_BAD_PARAM) {
        printf("✅ NULL 컨텍스트 테스트 성공\n");
    } else {
        printf("❌ NULL 컨텍스트 테스트 실패: %d\n", err);
        success = 0;
    }
    
    err = aes_ctr_init(&ctx, NULL, AES_128, iv);
    if (err == AES_ERR_BAD_PARAM) {
        printf("✅ NULL 키 테스트 성공\n");
    } else {
        printf("❌ NULL 키 테스트 실패: %d\n", err);
        success = 0;
    }
    
    err = aes_ctr_init(&ctx, key, AES_128, NULL);
    if (err == AES_ERR_BAD_PARAM) {
        printf("✅ NULL IV 테스트 성공\n");
    } else {
        printf("❌ NULL IV 테스트 실패: %d\n", err);
        success = 0;
    }
    
    // 잘못된 길이 테스트
    printf("\n--- 잘못된 길이 테스트 ---\n");
    err = aes_ctr_init(&ctx, key, AES_128, iv);
    if (err != AES_OK) {
        printf("❌ 정상 초기화 실패: %d\n", err);
        success = 0;
    } else {
        const char* test_data = "Test";
        uint8_t output[16];
        
        // 0 길이 테스트
        err = aes_ctr_crypt(&ctx, (const uint8_t*)test_data, output, 0);
        if (err == AES_ERR_BAD_PARAM) {
            printf("✅ 0 길이 테스트 성공\n");
        } else {
            printf("❌ 0 길이 테스트 실패: %d\n", err);
            success = 0;
        }
        
        // 17바이트 테스트 (16바이트 초과)
        err = aes_ctr_crypt(&ctx, (const uint8_t*)test_data, output, 17);
        if (err == AES_ERR_BAD_PARAM) {
            printf("✅ 17바이트 테스트 성공\n");
        } else {
            printf("❌ 17바이트 테스트 실패: %d\n", err);
            success = 0;
        }
        
        aes_ctr_clear(&ctx);
    }
    
    if (success) {
        printf("\n✅ 모든 에러 처리 테스트 성공!\n");
    } else {
        printf("\n❌ 일부 에러 처리 테스트 실패!\n");
    }
    
    return success;
}

int main() {
    printf("🎯 새로운 AES-CTR 모드 테스트 시작\n");
    printf("=====================================\n");
    
    int success = 1;
    
    // 패딩 테스트
    printf("\n📦 패딩 테스트");
    printf("\n=====================================");
    success &= test_aes_ctr_padding();
    
    // 다양한 키 길이 테스트
    printf("\n🔑 다양한 키 길이 테스트");
    printf("\n=====================================");
    success &= test_aes_ctr_different_keys();
    
    // 카운터 연산 테스트
    printf("\n🔢 카운터 연산 테스트");
    printf("\n=====================================");
    success &= test_aes_ctr_counter_operations();
    
    // 에러 처리 테스트
    printf("\n⚠️  에러 처리 테스트");
    printf("\n=====================================");
    success &= test_aes_ctr_error_handling();
    
    // 최종 결과
    printf("\n🏆 최종 결과");
    printf("\n=====================================");
    if (success) {
        printf("🎉 새로운 AES-CTR 모드가 완벽하게 작동합니다!\n");
        printf("✅ 16바이트 단위 패딩 처리\n");
        printf("✅ AES-128, AES-192, AES-256 지원\n");
        printf("✅ 카운터 연산\n");
        printf("✅ 에러 처리\n");
    } else {
        printf("❌ 일부 AES-CTR 기능에서 문제가 발생했습니다.\n");
    }
    
    return success ? 0 : 1;
}
