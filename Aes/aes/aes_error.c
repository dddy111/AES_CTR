/* aes_error.c - AES 에러 스택 추적 시스템 구현 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/crypto_common.h"

/* =============================================================================
 * 내부 헬퍼 함수들
 * ============================================================================= */

/**
 * @brief 에러 노드 생성
 * @param line 에러 발생 라인 번호
 * @param file 에러 발생 파일명
 * @param function 에러 발생 함수명
 * @param error_code 에러 코드
 * @param message 에러 메시지
 * @return 생성된 에러 노드 (실패 시 NULL)
 */
static aes_error_node_t* create_error_node(int line, 
                                          const char* file, 
                                          const char* function, 
                                          aes_err_t error_code, 
                                          const char* message)
{
    aes_error_node_t* node = (aes_error_node_t*)malloc(sizeof(aes_error_node_t));
    if (!node) {
        return NULL;
    }
    
    node->line = line;
    node->file = file;
    node->function = function;
    node->error_code = error_code;
    node->next = NULL;
    
    // 메시지 복사 (최대 255자)
    if (message) {
        snprintf(node->message, sizeof(node->message), "%s", message);
    } else {
        node->message[0] = '\0';
    }
    
    return node;
}

/**
 * @brief 에러 노드 해제
 * @param node 해제할 에러 노드
 */
static void free_error_node(aes_error_node_t* node)
{
    if (node) {
        free(node);
    }
}

/* =============================================================================
 * 공개 API 함수들
 * ============================================================================= */

/**
 * @brief 에러 스택 초기화
 * 
 * @param stack 초기화할 에러 스택
 * @param max_depth 최대 스택 깊이
 * @return 성공 시 AES_OK, 실패 시 오류 코드
 */
aes_err_t aes_error_init(aes_error_stack_t* stack, int max_depth)
{
    if (!stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    if (max_depth <= 0) {
        return AES_ERR_BAD_PARAM;
    }
    
    stack->head = NULL;
    stack->count = 0;
    stack->max_depth = max_depth;
    
    return AES_OK;
}

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
aes_err_t aes_error_push(aes_error_stack_t* stack, 
                        int line, 
                        const char* file, 
                        const char* function, 
                        aes_err_t error_code, 
                        const char* message)
{
    if (!stack) {
        return AES_ERR_BAD_PARAM;
    }
    
    // 최대 깊이 확인
    if (stack->count >= stack->max_depth) {
        return AES_ERR_OVERFLOW;
    }
    
    // 에러 노드 생성
    aes_error_node_t* node = create_error_node(line, file, function, error_code, message);
    if (!node) {
        return AES_ERR_MEMORY;
    }
    
    // 스택에 추가 (LIFO)
    node->next = stack->head;
    stack->head = node;
    stack->count++;
    
    return AES_OK;
}

/**
 * @brief 에러 스택에서 최상위 에러 제거
 * 
 * @param stack 에러 스택
 */
void aes_error_pop(aes_error_stack_t* stack)
{
    if (!stack || !stack->head) {
        return;
    }
    
    aes_error_node_t* node = stack->head;
    stack->head = node->next;
    stack->count--;
    
    free_error_node(node);
}

/**
 * @brief 최상위 에러 코드 반환
 * 
 * @param stack 에러 스택
 * @return 최상위 에러 코드 (스택이 비어있으면 AES_OK)
 */
aes_err_t aes_error_get_top(const aes_error_stack_t* stack)
{
    if (!stack || !stack->head) {
        return AES_OK;
    }
    
    return stack->head->error_code;
}

/**
 * @brief 에러 스택 전체 출력
 * 
 * @param stack 에러 스택
 */
void aes_error_print_stack(const aes_error_stack_t* stack)
{
    if (!stack) {
        printf("Error: NULL error stack\n");
        return;
    }
    
    if (!stack->head) {
        printf("Error stack is empty\n");
        return;
    }
    
    printf("=== Error Stack Trace ===\n");
    printf("Total errors: %d\n\n", stack->count);
    
    aes_error_node_t* current = stack->head;
    int level = 0;
    
    while (current) {
        printf("[%d] %s:%d in %s()\n", 
               level, 
               current->file, 
               current->line, 
               current->function);
        printf("    Error: %d (%s)\n", 
               current->error_code, 
               aes_error_to_string(current->error_code));
        
        if (strlen(current->message) > 0) {
            printf("    Message: %s\n", current->message);
        }
        
        printf("\n");
        
        current = current->next;
        level++;
    }
    
    printf("=== End of Stack Trace ===\n");
}

/**
 * @brief 에러 스택 정리
 * 
 * @param stack 에러 스택
 */
void aes_error_clear(aes_error_stack_t* stack)
{
    if (!stack) {
        return;
    }
    
    while (stack->head) {
        aes_error_pop(stack);
    }
    
    stack->count = 0;
}

/**
 * @brief 에러 코드를 문자열로 변환
 * 
 * @param error_code 에러 코드
 * @return 에러 코드에 해당하는 문자열
 */
const char* aes_error_to_string(aes_err_t error_code)
{
    switch (error_code) {
        case AES_OK:
            return "Success";
        case AES_ERR_BAD_PARAM:
            return "Bad parameter";
        case AES_ERR_BAD_KEY_LEN:
            return "Bad key length";
        case AES_ERR_AUTH_FAIL:
            return "Authentication failed";
        case AES_ERR_MEMORY:
            return "Memory error";
        case AES_ERR_INVALID_STATE:
            return "Invalid state";
        case AES_ERR_NOT_INIT:
            return "Not initialized";
        case AES_ERR_OVERFLOW:
            return "Overflow";
        case AES_ERR_UNDERFLOW:
            return "Underflow";
        case AES_ERR_INTERNAL:
            return "Internal error";
        case AES_ERR_SBOX_FAIL:
            return "S-Box transformation failed";
        case AES_ERR_MIX_FAIL:
            return "MixColumns transformation failed";
        case AES_ERR_SHIFT_FAIL:
            return "ShiftRows transformation failed";
        case AES_ERR_KEY_FAIL:
            return "Key scheduling failed";
        case AES_ERR_GF256_FAIL:
            return "GF(2^8) operation failed";
        default:
            return "Unknown error";
    }
}
