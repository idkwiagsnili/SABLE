#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

long long find_d(long long e, long long phi) {
    long long d = 1;

    while ((e * d) % phi != 1) {
        d++;
    }

    return d;
}

int main(void) {
    long long p = 61;
    long long q = 53;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    long long d;
    long long message = 123;
    long long encrypted;
    long long decrypted;

    printf("=== 8주차: RSA 구조 ===\n");
    printf("p = %lld, q = %lld\n", p, q);
    printf("n = p * q = %lld\n", n);
    printf("phi = (p - 1) * (q - 1) = %lld\n\n", phi);

    printf("=== 공개 지수 선택 ===\n");
    printf("e = %lld\n", e);
    printf("gcd(e, phi) = %lld\n", gcd(e, phi));

    d = find_d(e, phi);

    printf("d = %lld\n", d);
    printf("(e * d) mod phi = %lld\n\n", (e * d) % phi);

    printf("=== 공개키와 개인키 ===\n");
    printf("공개키: (n = %lld, e = %lld)\n", n, e);
    printf("개인키: (n = %lld, d = %lld)\n\n", n, d);

    printf("=== 암호화와 복호화 ===\n");
    printf("원본 메시지: %lld\n", message);

    encrypted = mod_pow(message, e, n);
    printf("암호화 결과: %lld\n", encrypted);

    decrypted = mod_pow(encrypted, d, n);
    printf("복호화 결과: %lld\n\n", decrypted);

    printf("=== 핵심 ===\n");
    printf("공개되는 값은 n과 e이다.\n");
    printf("p, q, d는 숨겨야 한다.\n");
    printf("n만 보고 p와 q를 찾기 어렵다는 점이 RSA의 핵심이다.\n");

    return 0;
}
