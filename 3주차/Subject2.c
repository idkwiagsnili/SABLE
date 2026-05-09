#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[4096];
    int count[26] = {0};
    int total = 0;

    printf("문자열 입력: ");

    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("입력 오류\n");
        return 1;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = tolower((unsigned char)text[i]);

        if (ch >= 'a' && ch <= 'z') {
            count[ch - 'a']++;
            total++;
        }
    }

    printf("\n[빈도 분석 결과]\n");

    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            printf("%c : %d회\n", 'a' + i, count[i]);
        }
    }

    printf("\n총 알파벳 개수: %d\n", total);

    return 0;
}