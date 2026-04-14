#include <stdio.h>
#include <string.h>

int main() {
    printf("=== 평문, 키, 암호화의 3요소 ===\n\n");

    // 1. 평문 (Plaintext): 우리가 보호하려는 원본 데이터
    char text[] = "Hacking"; 
    
    // 2. 키 (Key): 암호화와 복호화에 사용되는 비밀 값
    // (여기서는 숫자 7을 키로 사용합니다)
    int secret_key = 7; 

    printf("[단계 1] 원본 데이터 준비\n");
    printf("-> 평문: %s\n", text);
    printf("-> 암호 키: %d\n\n", secret_key);

    // ------------------------------------------------
    // 3. 암호화 (Encryption) 과정
    // ------------------------------------------------
    printf("[단계 2] 암호화 진행 (평문 ^ 키)\n");
    for (int i = 0; i < strlen(text); i++) {
        text[i] = text[i] ^ secret_key; // 평문 글자에 키값을 XOR 연산
    }
    // 결과적으로 글자가 깨져서 알아볼 수 없는 '암호문'이 됩니다.
    printf("-> 생성된 암호문: %s\n\n", text);

    // ------------------------------------------------
    // 4. 복호화 (Decryption) 과정
    // ------------------------------------------------
    printf("[단계 3] 복호화 진행 (암호문 ^ 키)\n");
    for (int i = 0; i < strlen(text); i++) {
        text[i] = text[i] ^ secret_key; // 암호문에 '동일한 키'로 다시 XOR 연산
    }
    // 동일한 키로 연산했기 때문에 다시 원래의 '평문'으로 돌아옵니다.
    printf("-> 복구된 평문: %s\n", text);

    return 0;
}
