#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>

#define MAX 256
#define SALT "sable_week4_salt"

/*
    학습용 예제 코드다.
    실제 서비스 비밀번호 저장에는 SHA-256 단독보다
    bcrypt, scrypt, Argon2 같은 전용 비밀번호 해시 함수를 사용하는 것이 좋다.
*/

/* 1. 암호화 - 카이사르 암호 */
char caesar_char(char ch, int key) {
    if (isupper((unsigned char)ch)) {
        int moved = (ch - 'A' + key) % 26;
        return 'A' + moved;
    }

    if (islower((unsigned char)ch)) {
        int moved = (ch - 'a' + key) % 26;
        return 'a' + moved;
    }

    return ch;
}

void caesar_encrypt(const char input[], char output[], int key) {
    int i;

    for (i = 0; input[i] != '\0'; i++) {
        output[i] = caesar_char(input[i], key);
    }

    output[i] = '\0';
}

void caesar_decrypt(const char input[], char output[], int key) {
    caesar_encrypt(input, output, 26 - key);
}

/* 2. 인코딩 - Base64 */
void base64_encode(const unsigned char input[], char output[]) {
    const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int len = strlen((const char *)input);
    int i, j = 0;

    for (i = 0; i < len; i += 3) {
        int value = 0;
        int remain = len - i;

        value |= input[i] << 16;

        if (remain > 1) {
            value |= input[i + 1] << 8;
        }

        if (remain > 2) {
            value |= input[i + 2];
        }

        output[j++] = table[(value >> 18) & 0x3F];
        output[j++] = table[(value >> 12) & 0x3F];

        if (remain > 1) {
            output[j++] = table[(value >> 6) & 0x3F];
        } else {
            output[j++] = '=';
        }

        if (remain > 2) {
            output[j++] = table[value & 0x3F];
        } else {
            output[j++] = '=';
        }
    }

    output[j] = '\0';
}

/* 3. 해시 - SHA-256 */
void sha256_hash(const char input[], unsigned char hash[]) {
    SHA256((const unsigned char *)input, strlen(input), hash);
}

void print_hash(unsigned char hash[]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
}

/* Salt + 비밀번호 SHA-256 해시 */
void password_hash(const char password[], unsigned char hash[]) {
    char temp[MAX];

    snprintf(temp, sizeof(temp), "%s%s", SALT, password);

    sha256_hash(temp, hash);
}

int main(void) {
    const char text[] = "hello";
    const int key = 5;

    char encrypted[MAX];
    char decrypted[MAX];
    char encoded[MAX];

    unsigned char text_hash[SHA256_DIGEST_LENGTH];

    const char signup_pw[] = "hello";
    const char login_pw[] = "Hello";

    unsigned char stored_hash[SHA256_DIGEST_LENGTH];
    unsigned char login_hash[SHA256_DIGEST_LENGTH];

    printf("==============================\n");
    printf("1. 암호화\n");
    printf("==============================\n");

    caesar_encrypt(text, encrypted, key);
    caesar_decrypt(encrypted, decrypted, key);

    printf("원문   : %s\n", text);
    printf("키     : %d\n", key);
    printf("암호문 : %s\n", encrypted);
    printf("복호문 : %s\n", decrypted);
    printf("설명   : 암호화는 키가 있으면 다시 복호화할 수 있다.\n");

    printf("\n==============================\n");
    printf("2. 인코딩\n");
    printf("==============================\n");

    base64_encode((const unsigned char *)text, encoded);

    printf("원문          : %s\n", text);
    printf("Base64 인코딩 : %s\n", encoded);
    printf("설명          : 인코딩은 데이터를 다른 표현 방식으로 바꾸는 것이다.\n");

    printf("\n==============================\n");
    printf("3. 해시\n");
    printf("==============================\n");

    sha256_hash(text, text_hash);

    printf("원문   : %s\n", text);
    printf("SHA-256 해시값 : ");
    print_hash(text_hash);
    printf("\n");
    printf("설명   : 해시는 원래 값으로 되돌리는 것이 거의 불가능한 일방향 방식이다.\n");

    printf("\n==============================\n");
    printf("4. 비밀번호 해시 검증\n");
    printf("==============================\n");

    password_hash(signup_pw, stored_hash);
    password_hash(login_pw, login_hash);

    printf("회원가입 비밀번호 : %s\n", signup_pw);
    printf("로그인 비밀번호   : %s\n", login_pw);

    printf("\n[DB에 저장되는 값]\n");
    printf("Salt : %s\n", SALT);
    printf("Hash : ");
    print_hash(stored_hash);
    printf("\n");
    printf("원문 비밀번호는 저장하지 않는다.\n");

    printf("\n[검증 과정]\n");
    printf("저장된 해시값 : ");
    print_hash(stored_hash);
    printf("\n");

    printf("입력값 해시값 : ");
    print_hash(login_hash);
    printf("\n");

    if (memcmp(stored_hash, login_hash, SHA256_DIGEST_LENGTH) == 0) {
        printf("결과 : 로그인 성공\n");
    } else {
        printf("결과 : 로그인 실패\n");
    }

    return 0;
}