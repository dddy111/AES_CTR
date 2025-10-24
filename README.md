# AES 암호화 라이브러리

C로 구현된 AES (Advanced Encryption Standard) 암호화 라이브러리입니다.

## 📁 프로젝트 구조

```
Aes/
├── aes/                    # AES 핵심 구현 파일들
│   ├── aes_core.c         # 암호화/복호화 핵심 로직
│   ├── aes_key.c          # 키 스케줄링
│   ├── aes_mix.c          # MixColumns, ShiftRows
│   ├── aes_sbox.c         # S-Box 변환
│   └── gf256.c            # GF(2^8) 유한체 연산
├── include/               # 헤더 파일들
│   ├── aes.h             # 공개 API
│   ├── aes_internal.h    # 내부 함수 선언
│   ├── crypto_common.h   # 공통 상수 및 에러 코드
│   ├── gf256.h           # GF(2^8) 연산 헤더
│   ├── aes_ctr.c         # AES-CTR 모드 구현
│   └── ctr_mode.c        # 범용 CTR 모드
├── build/                 # 빌드 결과물
│   ├── *.obj             # 오브젝트 파일들
│   └── test_aes.exe      # 실행 파일
├── test_aes.c            # 테스트 프로그램
├── Makefile              # 빌드 설정
└── README.md             # 이 파일
```

## 🚀 빌드 및 실행

### Windows (MinGW/MSYS2)

```bash
# 프로젝트 빌드
make

# 빌드 후 테스트 실행
make test

# 빌드 파일들 정리
make clean

# 도움말 보기
make help
```

### 수동 컴파일

```bash
# 오브젝트 파일 컴파일
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c aes/aes_core.c -o build/aes_core.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c aes/aes_key.c -o build/aes_key.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c aes/aes_mix.c -o build/aes_mix.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c aes/aes_sbox.c -o build/aes_sbox.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c aes/gf256.c -o build/gf256.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c include/aes_ctr.c -o build/aes_ctr.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c include/ctr_mode.c -o build/ctr_mode.obj
gcc -Wall -Wextra -std=c99 -O2 -Iinclude -c test_aes.c -o build/test_aes.obj

# 실행 파일 링크
gcc build/*.obj -o build/test_aes.exe

# 실행
cd build && test_aes.exe
```

## ✨ 주요 기능

### AES 블록 암호화
- **AES-128/192/256** 지원
- **ECB 모드** 블록 암호화/복호화
- 표준 NIST AES 알고리즘 구현

### CTR 모드
- **스트림 암호화** 지원
- 임의 길이 데이터 암호화/복호화
- 카운터 기반 키스트림 생성

### 수학적 구현
- **GF(2^8) 유한체** 연산 직접 구현
- **S-Box/역 S-Box** 테이블
- **MixColumns** 다항식 곱셈

## 🔧 API 사용법

### 기본 AES 암호화

```c
#include "include/aes.h"

// 키 설정
aes_key_t enc_key, dec_key;
uint8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, ...}; // 16바이트 키

aes_set_encrypt_key(&enc_key, key, AES_128);
aes_set_decrypt_key(&dec_key, key, AES_128);

// 암호화
uint8_t plaintext[16] = {0x32, 0x43, 0xf6, 0xa8, ...};
uint8_t ciphertext[16];
aes_encrypt_block(&enc_key, plaintext, ciphertext);

// 복호화
uint8_t decrypted[16];
aes_decrypt_block(&dec_key, ciphertext, decrypted);

// 키 정리
aes_key_clear(&enc_key);
aes_key_clear(&dec_key);
```

### CTR 모드 사용

```c
#include "include/aes_ctr.h"

// CTR 초기화
aes_ctr_ctx_t ctr_ctx;
uint8_t key[16] = {...};
uint8_t iv[16] = {...}; // 초기화 벡터

aes_ctr_init(&ctr_ctx, key, AES_128, iv);

// 암호화/복호화
uint8_t data[] = "Hello, World!";
uint8_t encrypted[sizeof(data)];
aes_ctr_crypt(&ctr_ctx, data, encrypted, sizeof(data));

// 정리
aes_ctr_clear(&ctr_ctx);
```

## 🧪 테스트

프로젝트에는 기본 테스트가 포함되어 있습니다:

```bash
make test
```

테스트는 다음을 검증합니다:
- AES-128 암호화/복호화 정확성
- 키 스케줄링 정확성
- 메모리 안전성

## 📋 요구사항

- **C99** 호환 컴파일러 (GCC, Clang, MSVC)
- **Windows/Linux/macOS** 지원
- **MinGW/MSYS2** (Windows에서 권장)

## 🔒 보안 주의사항

- 키는 안전하게 저장하고 전송하세요
- 사용 후 `aes_key_clear()`로 키를 정리하세요
- 프로덕션 사용 전 보안 감사를 받으세요

## 📄 라이선스

이 프로젝트는 교육 및 연구 목적으로 제작되었습니다.
