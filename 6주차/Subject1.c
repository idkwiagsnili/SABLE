#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 4
#define TOTAL_SIZE 16

int main(void) {
    unsigned char plain[TOTAL_SIZE + 1] = "ABCDABCDABCDABCD";

    unsigned char key[BLOCK_SIZE] = { 'K', 'E', 'Y', '1' };
    unsigned char iv[BLOCK_SIZE] = { 'I', 'V', '1', '2' };
    unsigned char iv2[BLOCK_SIZE] = { 'A', 'B', 'C', 'D' };

    unsigned char ecb_cipher[TOTAL_SIZE];
    unsigned char ecb_decrypted[TOTAL_SIZE + 1];

    unsigned char cbc_cipher[TOTAL_SIZE];
    unsigned char cbc_cipher2[TOTAL_SIZE];
    unsigned char cbc_decrypted[TOTAL_SIZE + 1];

    unsigned char ctr_cipher[TOTAL_SIZE];
    unsigned char ctr_decrypted[TOTAL_SIZE + 1];

    unsigned char prev[BLOCK_SIZE];
    unsigned char temp[BLOCK_SIZE];
    unsigned char counter[BLOCK_SIZE];
    unsigned char stream[BLOCK_SIZE];

    int i, j;

    printf("====================================\n");
    printf("6주차 - 블록 암호 운영 모드 예제\n");
    printf("====================================\n\n");

    printf("원문 : %s\n", plain);
    printf("블록 크기 : %d바이트\n", BLOCK_SIZE);
    printf("키 : KEY1\n");
    printf("IV : IV12\n\n");

    printf("[원문 블록]\n");
    for (i = 0; i < TOTAL_SIZE; i++) {
        printf("%c", plain[i]);

        if ((i + 1) % BLOCK_SIZE == 0) {
            printf(" | ");
        }
    }
    printf("\n\n");

    /*
        실제 보안용 암호가 아니라 학습용 예제이다.
        여기서는 블록 암호를 단순히 XOR로 흉내낸다.
    */

    printf("====================================\n");
    printf("1. ECB 모드\n");
    printf("====================================\n");

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            ecb_cipher[i + j] = plain[i + j] ^ key[j];
        }
    }

    printf("암호문 : ");
    for (i = 0; i < TOTAL_SIZE; i++) {
        printf("%02X ", ecb_cipher[i]);

        if ((i + 1) % BLOCK_SIZE == 0) {
            printf("| ");
        }
    }
    printf("\n");

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            ecb_decrypted[i + j] = ecb_cipher[i + j] ^ key[j];
        }
    }
    ecb_decrypted[TOTAL_SIZE] = '\0';

    printf("복호화 결과 : %s\n", ecb_decrypted);
    printf("설명 : ECB는 같은 평문 블록이 같은 암호문 블록으로 반복된다.\n\n");

    printf("====================================\n");
    printf("2. CBC 모드\n");
    printf("====================================\n");

    memcpy(prev, iv, BLOCK_SIZE);

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plain[i + j] ^ prev[j];
            cbc_cipher[i + j] = temp[j] ^ key[j];
        }

        memcpy(prev, cbc_cipher + i, BLOCK_SIZE);
    }

    printf("암호문 : ");
    for (i = 0; i < TOTAL_SIZE; i++) {
        printf("%02X ", cbc_cipher[i]);

        if ((i + 1) % BLOCK_SIZE == 0) {
            printf("| ");
        }
    }
    printf("\n");

    memcpy(prev, iv, BLOCK_SIZE);

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = cbc_cipher[i + j] ^ key[j];
            cbc_decrypted[i + j] = temp[j] ^ prev[j];
        }

        memcpy(prev, cbc_cipher + i, BLOCK_SIZE);
    }
    cbc_decrypted[TOTAL_SIZE] = '\0';

    printf("복호화 결과 : %s\n", cbc_decrypted);
    printf("설명 : CBC는 IV와 이전 암호문 블록을 섞어서 암호화한다.\n\n");

    printf("====================================\n");
    printf("3. CBC에서 IV를 바꾼 경우\n");
    printf("====================================\n");

    memcpy(prev, iv2, BLOCK_SIZE);

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plain[i + j] ^ prev[j];
            cbc_cipher2[i + j] = temp[j] ^ key[j];
        }

        memcpy(prev, cbc_cipher2 + i, BLOCK_SIZE);
    }

    printf("다른 IV 암호문 : ");
    for (i = 0; i < TOTAL_SIZE; i++) {
        printf("%02X ", cbc_cipher2[i]);

        if ((i + 1) % BLOCK_SIZE == 0) {
            printf("| ");
        }
    }
    printf("\n");

    printf("설명 : 같은 평문과 같은 키여도 IV가 다르면 암호문이 달라진다.\n\n");

    printf("====================================\n");
    printf("4. CTR 모드\n");
    printf("====================================\n");

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        counter[0] = 'N';
        counter[1] = 'O';
        counter[2] = '0';
        counter[3] = (unsigned char)(i / BLOCK_SIZE);

        for (j = 0; j < BLOCK_SIZE; j++) {
            stream[j] = counter[j] ^ key[j];
            ctr_cipher[i + j] = plain[i + j] ^ stream[j];
        }
    }

    printf("암호문 : ");
    for (i = 0; i < TOTAL_SIZE; i++) {
        printf("%02X ", ctr_cipher[i]);

        if ((i + 1) % BLOCK_SIZE == 0) {
            printf("| ");
        }
    }
    printf("\n");

    for (i = 0; i < TOTAL_SIZE; i += BLOCK_SIZE) {
        counter[0] = 'N';
        counter[1] = 'O';
        counter[2] = '0';
        counter[3] = (unsigned char)(i / BLOCK_SIZE);

        for (j = 0; j < BLOCK_SIZE; j++) {
            stream[j] = counter[j] ^ key[j];
            ctr_decrypted[i + j] = ctr_cipher[i + j] ^ stream[j];
        }
    }
    ctr_decrypted[TOTAL_SIZE] = '\0';

    printf("복호화 결과 : %s\n", ctr_decrypted);
    printf("설명 : CTR은 nonce와 counter로 만든 값을 평문과 XOR한다.\n\n");

    return 0;
}