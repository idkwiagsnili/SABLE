#include <stdio.h>
#include <string.h>

void caesar_encrypt(char text[], int key) {
    int i;

    key = key % 26;

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' + key) % 26) + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = ((text[i] - 'a' + key) % 26) + 'a';
        }
    }
}

void caesar_decrypt(char text[], int key) {
    int i;

    key = key % 26;

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' - key + 26) % 26) + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = ((text[i] - 'a' - key + 26) % 26) + 'a';
        }
    }
}

void substitution_encrypt(char text[], char key[]) {
    int i;
    int index;

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            index = text[i] - 'A';
            text[i] = key[index];
        }
    }
}

void substitution_decrypt(char text[], char key[]) {
    int i, j;

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            for (j = 0; j < 26; j++) {
                if (text[i] == key[j]) {
                    text[i] = 'A' + j;
                    break;
                }
            }
        }
    }
}

int main() {
    char original[100] = "HELLO";

    char caesarText[100];
    char caesarText2[100];
    char substitutionText[100];

    int caesarKey1 = 3;
    int caesarKey2 = 5;

    char substitutionKey[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("===== 카이사르 암호 =====\n");

    strcpy(caesarText, original);

    printf("원문        : %s\n", caesarText);
    printf("키          : %d칸 이동\n", caesarKey1);

    caesar_encrypt(caesarText, caesarKey1);

    printf("암호문      : %s\n", caesarText);

    caesar_decrypt(caesarText, caesarKey1);

    printf("복호화 결과 : %s\n\n", caesarText);


    printf("===== 암호화 속 키의 활용 =====\n");

    strcpy(caesarText, original);
    strcpy(caesarText2, original);

    printf("원문        : %s\n", original);

    caesar_encrypt(caesarText, caesarKey1);
    caesar_encrypt(caesarText2, caesarKey2);

    printf("키 %d 사용 시 암호문 : %s\n", caesarKey1, caesarText);
    printf("키 %d 사용 시 암호문 : %s\n\n", caesarKey2, caesarText2);


    printf("===== 단순 치환 암호 =====\n");

    strcpy(substitutionText, original);

    printf("원문        : %s\n", substitutionText);
    printf("치환 키    : %s\n", substitutionKey);

    substitution_encrypt(substitutionText, substitutionKey);

    printf("암호문      : %s\n", substitutionText);

    substitution_decrypt(substitutionText, substitutionKey);

    printf("복호화 결과 : %s\n", substitutionText);

    return 0;
}
