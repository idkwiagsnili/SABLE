#include <stdio.h>

unsigned long long power(int base, int exp) {
    unsigned long long result = 1;

    for (int i = 0; i < exp; i++) {
        result *= base;
    }

    return result;
}

int main(void) {
    int charset_size;
    int length;
    unsigned long long key_space;

    printf("사용 가능한 문자 개수 입력: ");
    scanf("%d", &charset_size);

    printf("비밀번호 길이 입력: ");
    scanf("%d", &length);

    key_space = power(charset_size, length);

    printf("\n[키 공간 계산 결과]\n");
    printf("문자 종류: %d개\n", charset_size);
    printf("비밀번호 길이: %d자리\n", length);
    printf("키 공간: %llu개\n", key_space);

    return 0;
}