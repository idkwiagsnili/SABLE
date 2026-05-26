#include <stdio.h>

int main() {
    char text[] = "SABLE WEEK5 SYMMETRIC KEY";
    char encrypted[100];
    char decrypted[100];
    char wrong_decrypted[100];

    char key = 0x12;        // A와 B가 공유한 대칭키
    char wrong_key = 0x33;  // 잘못된 키

    int i = 0;
    int len = 0;

    while (text[len] != '\0') {
        len++;
    }

    printf("=== 대칭키 암호 ===\n");
    printf("원본 데이터: %s\n", text);
    printf("공유된 키: 0x%X\n\n", key);

    printf("=== 암호화 ===\n");

    for (i = 0; i < len; i++) {
        encrypted[i] = text[i] ^ key;
    }
    encrypted[len] = '\0';

    printf("암호문 HEX: ");
    for (i = 0; i < len; i++) {
        printf("%02X ", (unsigned char)encrypted[i]);
    }
    printf("\n\n");

    printf("=== 복호화 ===\n");

    for (i = 0; i < len; i++) {
        decrypted[i] = encrypted[i] ^ key;
    }
    decrypted[len] = '\0';

    printf("올바른 키로 복호화: %s\n\n", decrypted);

    printf("=== 키 공유 문제 ===\n");

    for (i = 0; i < len; i++) {
        wrong_decrypted[i] = encrypted[i] ^ wrong_key;
    }
    wrong_decrypted[len] = '\0';

    printf("잘못된 키로 복호화: %s\n", wrong_decrypted);

    return 0;
}