/* crypto_common.h - 공통 상수, 에러 코드, 가시성 매크로 */
#ifndef CRYPTO_COMMON_H
#define CRYPTO_COMMON_H

#include <stddef.h>
#include <stdint.h>

/* =============================================================================
 * 가시성 매크로 (선행 정의 필요)
 * ============================================================================= */

/**
 * @brief API 함수 가시성 매크로
 *
 * 라이브러리 함수의 가시성을 제어합니다.
 * 기본적으로 모든 함수는 공개됩니다.
 */
#ifndef AES_API
#  define AES_API
#endif

/* =============================================================================
 * AES 상수 정의
 * ============================================================================= */

/** @brief AES 블록 크기 (바이트) */
#define AES_BLOCK_SIZE       16u

/** @brief AES GCM 인증 태그 크기 (바이트) */
#define AES_GCM_TAG_SIZE     16u

/** @brief AES 최대 키 크기 (바이트) */
#define AES_MAX_KEY_SIZE     32u

/** @brief AES 최대 라운드 수 */
#define AES_MAX_ROUNDS       14u

/** @brief AES 최대 라운드 키 개수 */
#define AES_MAX_ROUND_KEYS   60u

/* =============================================================================
 * 키 길이 열거형
 * ============================================================================= */

/**
 * @brief AES 키 길이 정의
 * 
 * AES는 세 가지 키 길이를 지원합니다:
 * - AES_128: 128비트 (16바이트) - 10라운드
 * - AES_192: 192비트 (24바이트) - 12라운드  
 * - AES_256: 256비트 (32바이트) - 14라운드
 */
typedef enum {
    AES_128 = 16,  /**< 128비트 키 (16바이트) */
    AES_192 = 24,  /**< 192비트 키 (24바이트) */
    AES_256 = 32   /**< 256비트 키 (32바이트) */
} aes_keylen_t;

/* =============================================================================
 * 에러 코드 정의
 * ============================================================================= */

/**
 * @brief AES 라이브러리 에러 코드
 * 
 * 모든 AES 함수는 성공 시 AES_OK를, 실패 시 적절한 에러 코드를 반환합니다.
 */
typedef enum {
    AES_OK = 0,                    /**< 성공 */
    AES_ERR_BAD_PARAM = -1,        /**< 잘못된 매개변수 (NULL 포인터, 잘못된 길이 등) */
    AES_ERR_BAD_KEY_LEN = -2,      /**< 잘못된 키 길이 (16/24/32 바이트가 아님) */
    AES_ERR_AUTH_FAIL = -3,        /**< 인증 실패 (GCM/HMAC) */
    AES_ERR_MEMORY = -4,           /**< 메모리 할당 실패 */
    AES_ERR_INVALID_STATE = -5,    /**< 잘못된 상태 (초기화되지 않은 컨텍스트 등) */
    AES_ERR_NOT_INIT = -6,         /**< 초기화되지 않음 */
    AES_ERR_OVERFLOW = -7,         /**< 오버플로우 */
    AES_ERR_UNDERFLOW = -8,        /**< 언더플로우 */
    AES_ERR_INTERNAL = -9,         /**< 내부 오류 */
    AES_ERR_SBOX_FAIL = -10,       /**< S-Box 변환 실패 */
    AES_ERR_MIX_FAIL = -11,        /**< MixColumns 변환 실패 */
    AES_ERR_SHIFT_FAIL = -12,      /**< ShiftRows 변환 실패 */
    AES_ERR_KEY_FAIL = -13,        /**< 키 스케줄링 실패 */
    AES_ERR_GF256_FAIL = -14       /**< GF(2^8) 연산 실패 */
} aes_err_t;

/* =============================================================================
 * 에러 스택 추적 시스템
 * ============================================================================= */

/**
 * @brief 에러 스택 노드
 * 
 * 에러가 발생한 지점의 정보를 저장하는 노드입니다.
 * 연결 리스트로 구현되어 호출 스택을 추적할 수 있습니다.
 */
typedef struct aes_error_node {
    int line;                           /**< 에러 발생 라인 번호 */
    const char* file;                   /**< 에러 발생 파일명 */
    const char* function;               /**< 에러 발생 함수명 */
    aes_err_t error_code;               /**< 에러 코드 */
    char message[256];                  /**< 에러 메시지 */
    struct aes_error_node* next;        /**< 다음 노드 포인터 */
} aes_error_node_t;

/**
 * @brief 에러 스택
 * 
 * 에러 발생 지점들을 스택 형태로 관리하는 구조체입니다.
 * 최상위 에러부터 하위 에러까지 호출 경로를 추적할 수 있습니다.
 */
typedef struct {
    aes_error_node_t* head;             /**< 스택 헤드 (최상위 에러) */
    int count;                          /**< 현재 에러 개수 */
    int max_depth;                      /**< 최대 스택 깊이 */
} aes_error_stack_t;

/* =============================================================================
 * 에러 스택 관리 함수들
 * ============================================================================= */

/**
 * @brief 에러 스택 초기화
 * 
 * @param stack 초기화할 에러 스택
 * @param max_depth 최대 스택 깊이
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
AES_API aes_err_t aes_error_init(aes_error_stack_t* stack, int max_depth);

/**
 * @brief 에러 스택에 에러 추가
 * 
 * @param stack 에러 스택
 * @param line 에러 발생 라인 번호
 * @param file 에러 발생 파일명
 * @param function 에러 발생 함수명
 * @param error_code 에러 코드
 * @param message 에러 메시지
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
AES_API aes_err_t aes_error_push(aes_error_stack_t* stack, 
                                int line, 
                                const char* file, 
                                const char* function, 
                                aes_err_t error_code, 
                                const char* message);

/**
 * @brief 에러 스택에서 최상위 에러 제거
 * 
 * @param stack 에러 스택
 */
AES_API void aes_error_pop(aes_error_stack_t* stack);

/**
 * @brief 최상위 에러 코드 반환
 * 
 * @param stack 에러 스택
 * @return 최상위 에러 코드 (스택이 비어있으면 AES_OK)
 */
AES_API aes_err_t aes_error_get_top(const aes_error_stack_t* stack);

/**
 * @brief 에러 스택 전체 출력
 * 
 * @param stack 에러 스택
 */
AES_API void aes_error_print_stack(const aes_error_stack_t* stack);

/**
 * @brief 에러 스택 정리
 * 
 * @param stack 에러 스택
 */
AES_API void aes_error_clear(aes_error_stack_t* stack);

/**
 * @brief 에러 코드를 문자열로 변환
 * 
 * @param error_code 에러 코드
 * @return 에러 코드에 해당하는 문자열
 */
AES_API const char* aes_error_to_string(aes_err_t error_code);

/* =============================================================================
 * 에러 스택 매크로
 * ============================================================================= */

/**
 * @brief 에러 스택에 에러 추가 (매크로)
 * 
 * __LINE__, __FILE__, __FUNCTION__을 자동으로 사용합니다.
 */
#define AES_ERROR_PUSH(stack, err, msg) \
    aes_error_push(stack, __LINE__, __FILE__, __FUNCTION__, err, msg)

/**
 * @brief 에러 스택 초기화 (매크로)
 * 
 * 기본 최대 깊이 10으로 초기화합니다.
 */
#define AES_ERROR_INIT(stack) \
    aes_error_init(stack, 10)

#endif /* CRYPTO_COMMON_H */