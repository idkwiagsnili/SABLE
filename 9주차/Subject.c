#include <stdio.h>
#include <string.h>

unsigned long long hash_string(const char *str) {
    unsigned long long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main() {
    char password[] = "123456";
    char salt1[] = "A1";
    char salt2[] = "B7";

    char input1[100];
    char input2[100];

    snprintf(input1, sizeof(input1), "%s%s", password, salt1);
    snprintf(input2, sizeof(input2), "%s%s", password, salt2);

    unsigned long long hash1 = hash_string(input1);
    unsigned long long hash2 = hash_string(input2);

    printf("=== Password Hash + Salt ===\n");
    printf("password: %s\n", password);
    printf("salt1: %s\n", salt1);
    printf("hash(password + salt1): %llu\n\n", hash1);

    printf("password: %s\n", password);
    printf("salt2: %s\n", salt2);
    printf("hash(password + salt2): %llu\n\n", hash2);

    if (hash1 != hash2) {
        printf("같은 비밀번호라도 salt가 다르면 해시값이 달라진다.\n\n");
    }

    unsigned long long n = 3233;
    unsigned long long e = 17;
    unsigned long long d = 2753;

    char message[] = "pay 10000 won";
    char tampered_message[] = "pay 90000 won";

    unsigned long long message_hash = hash_string(message) % n;
    unsigned long long signature = mod_pow(message_hash, d, n);

    unsigned long long verify_hash = mod_pow(signature, e, n);
    unsigned long long received_hash = hash_string(message) % n;
    unsigned long long tampered_hash = hash_string(tampered_message) % n;

    printf("=== Digital Signature ===\n");
    printf("message: %s\n", message);
    printf("hash(message): %llu\n", message_hash);
    printf("signature: %llu\n\n", signature);

    printf("=== Verify Original Message ===\n");
    printf("verify_hash: %llu\n", verify_hash);
    printf("received_hash: %llu\n", received_hash);

    if (verify_hash == received_hash) {
        printf("검증 성공: 메시지가 변조되지 않았고 올바른 서명이다.\n\n");
    } else {
        printf("검증 실패: 메시지 또는 서명이 올바르지 않다.\n\n");
    }

    printf("=== Verify Tampered Message ===\n");
    printf("tampered_message: %s\n", tampered_message);
    printf("verify_hash: %llu\n", verify_hash);
    printf("tampered_hash: %llu\n", tampered_hash);

    if (verify_hash == tampered_hash) {
        printf("검증 성공\n");
    } else {
        printf("검증 실패: 메시지가 변조되었기 때문에 기존 서명과 맞지 않는다.\n");
    }

    return 0;
}
