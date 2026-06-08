#include <stdio.h>

int main(void) {
    char text[] = "SABLE WEEK7 KEY DISTRIBUTION";
    char encrypted[100];
    char decrypted[100];

    int symmetricKey = 18;

    int publicKey = 17;
    int privateKey = 2753;
    int n = 3233;

    int protectedKey = 1;
    int recoveredKey = 1;
    int length = 0;
    int i;

    while (text[length] != '\0') {
        length++;
    }

    printf("=== 7주차: 키 분배 문제 ===\n");
    printf("원본 대칭 키: %d\n\n", symmetricKey);

    for (i = 0; i < publicKey; i++) {
        protectedKey = (protectedKey * symmetricKey) % n;
    }

    printf("=== 공개 키의 역할 ===\n");
    printf("공개 키로 보호한 대칭 키: %d\n", protectedKey);
    printf("공격자가 전송 중 확인하는 값: %d\n", protectedKey);
    printf("원본 대칭 키는 그대로 전송하지 않는다.\n\n");

    for (i = 0; i < privateKey; i++) {
        recoveredKey = (recoveredKey * protectedKey) % n;
    }

    printf("개인 키로 복구한 대칭 키: %d\n\n", recoveredKey);

    printf("=== 대칭 키의 역할 ===\n");
    printf("원본 데이터: %s\n", text);

    for (i = 0; i < length; i++) {
        encrypted[i] = text[i] ^ recoveredKey;
    }

    encrypted[length] = '\0';

    printf("암호문 HEX: ");

    for (i = 0; i < length; i++) {
        printf("%02X ", (unsigned char)encrypted[i]);
    }

    printf("\n");

    for (i = 0; i < length; i++) {
        decrypted[i] = encrypted[i] ^ recoveredKey;
    }

    decrypted[length] = '\0';

    printf("복호화 결과: %s\n", decrypted);

    return 0;
}
