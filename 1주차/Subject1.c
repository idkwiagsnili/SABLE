#include <stdio.h>
#include <string.h>

// 1. 인증 (Authentication): 간단한 문자열 비교
int authenticate(const char* id, const char* pw) {
    const char* valid_id = "admin";
    const char* valid_pw = "1234";
    
    if (strcmp(id, valid_id) == 0 && strcmp(pw, valid_pw) == 0) {
        return 1; // 인증 성공
    }
    return 0; // 인증 실패
}

// 2. 기밀성 (Confidentiality): 인덱스 기반 가변 XOR 암호화
void encrypt(char* text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        // 인덱스가 커질수록 XOR하는 키 값(i + 1)도 점점 커짐
        text[i] = text[i] ^ (i + 1); 
    }
}

void decrypt(char* text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        // XOR 연산은 같은 값으로 다시 연산하면 원본으로 복원됨
        text[i] = text[i] ^ (i + 1); 
    }
}

// 3. 무결성 (Integrity): 초간단 체크섬 (글자의 아스키 값 총합)
int calculate_checksum(const char* text) {
    int sum = 0;
    for (int i = 0; i < strlen(text); i++) {
        sum += text[i];
    }
    return sum;
}

// 4. 부인 방지 (Non-repudiation): 메시지에 발신자 서명 결합
void sign_message(const char* message, const char* sender_id, char* signed_doc) {
    sprintf(signed_doc, "[Message: %s | Signed_by: %s]", message, sender_id);
}

int main() {
    // [1] 인증 테스트
    printf("--- 1. 인증 (Authentication) ---\n");
    if (authenticate("admin", "1234")) {
        printf("-> 인증 성공! 시스템에 접근합니다.\n\n");
    } else {
        printf("-> 인증 실패!\n\n");
        return 0;
    }

    // [2] 기밀성 테스트
    printf("--- 2. 기밀성 (Confidentiality) ---\n");
    char secret_data[100] = "Attack at dawn";
    printf("원본 데이터: %s\n", secret_data);
    
    encrypt(secret_data);
    printf("암호화됨(해커가 보는 화면): %s\n", secret_data);
    
    decrypt(secret_data);
    printf("복호화됨(정상 수신 화면): %s\n\n", secret_data);

    // [3] 무결성 테스트
    printf("--- 3. 무결성 (Integrity) ---\n");
    char original_msg[] = "Transfer $100";
    int original_checksum = calculate_checksum(original_msg);
    printf("원본 메시지: '%s', 체크섬: %d\n", original_msg, original_checksum);

    // 해커가 메시지를 변조했다고 가정
    char hacked_msg[] = "Transfer $999"; 
    int new_checksum = calculate_checksum(hacked_msg);
    printf("변조된 메시지: '%s', 체크섬: %d\n", hacked_msg, new_checksum);
    
    if (original_checksum != new_checksum) {
        printf("-> 경고: 체크섬이 다릅니다! 데이터가 변조되었습니다.\n\n");
    }

    // [4] 부인 방지 테스트
    printf("--- 4. 부인 방지 (Non-repudiation) ---\n");
    char contract[] = "I agree to the terms";
    char sender[] = "User_Alice";
    char digital_signature[150];
    
    sign_message(contract, sender, digital_signature);
    printf("생성된 전자 서명 문서: \n%s\n", digital_signature);
    printf("-> %s는 문서 끝에 자신의 서명이 박혀 있으므로 발송 사실을 부인할 수 없습니다.\n\n", sender);

    return 0;
}
