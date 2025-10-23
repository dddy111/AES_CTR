# AES 라이브러리 Makefile

# 컴파일러 설정
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
INCLUDES = -Iinclude

# 디렉토리 설정
SRC_DIR = aes
BUILD_DIR = build
INCLUDE_DIR = include

# 소스 파일들
AES_SOURCES = $(SRC_DIR)/aes_core.c $(SRC_DIR)/aes_key.c $(SRC_DIR)/aes_round.c \
              $(SRC_DIR)/aes_sbox.c $(SRC_DIR)/gf256.c $(SRC_DIR)/aes_error.c
CTR_SOURCES = $(INCLUDE_DIR)/aes_ctr.c $(INCLUDE_DIR)/ctr_mode.c
TEST_SOURCE = test_aes.c

# 오브젝트 파일들
AES_OBJECTS = $(AES_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.obj)
CTR_OBJECTS = $(CTR_SOURCES:$(INCLUDE_DIR)/%.c=$(BUILD_DIR)/%.obj)
TEST_OBJECT = $(BUILD_DIR)/test_aes.obj

# 실행 파일
TARGET = $(BUILD_DIR)/aes.exe

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(AES_OBJECTS) $(CTR_OBJECTS) $(TEST_OBJECT)
	$(CC) $(AES_OBJECTS) $(CTR_OBJECTS) $(TEST_OBJECT) -o $@

# 오브젝트 파일 컴파일
$(BUILD_DIR)/%.obj: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.obj: $(INCLUDE_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/test_aes.obj: test_aes.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 빌드 디렉토리 생성
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# 테스트 실행
test: $(TARGET)
	cd $(BUILD_DIR) && .\aes.exe

# 정리
clean:
	rmdir /s /q $(BUILD_DIR)

# 도움말
help:
	@echo 사용 가능한 명령어:
	@echo   make      - AES 라이브러리 빌드
	@echo   make test - 빌드 후 테스트 실행
	@echo   make clean - 빌드 파일들 정리
	@echo   make help  - 이 도움말 표시

.PHONY: all test clean help