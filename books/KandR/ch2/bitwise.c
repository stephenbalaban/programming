#include <stdio.h>
#include <string.h>

float power(float base, int exp) {
    if (base == 0)
        return 1;
    float r = 1.0f;
    int i;
    for(i = 0; i < exp; i++)
        r *= base ;
    return r;
}

void bitwise(int n, int b) {
    printf("%d & %d = %d\n", n, b, (n & b));
}

int isDecimal(char c) {
    return c >= '0' && c <= '9';
}

// assumes char is already a decimal
int charToInt(char c) {
    return c - '0';
}

int parseInt(char s[]) {
    int r = 0, i, len = strlen(s), place;
//    for(i = 0; i < len; i++)  { place = power(10, i);
    for(i = len - 1; i >= 0; i--)  {
        place = power(10, len - i - 1);
        r += charToInt(s[i]) * place;
    }
    return r;
}

void testIsDecimal() {
    int i;
    char chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c' };
    int len = sizeof(chars) / sizeof(char);
    for(i = 0; i < len; i++) {
        printf("isDecimal('%c'):  %d\n", chars[i], isDecimal(chars[i]));
    }
}

void testPower() {
    int i, j;
    float bases[] = { 0.0, 0.5, 2.0, 3.0, 4.0, 5.0 }; 
    int exps[] = { 0, 1, 2, 3 };
    int lenBas = sizeof(bases) / sizeof(int);
    int lenExp = sizeof(exps) / sizeof(int);
    for(i = 0; i < lenBas; i++)
        for (j = 0; j < lenExp; j++)
            printf("power(%.1f, %d):  %f\n", bases[i], exps[j], power(bases[i], exps[j]));
}

void testParseInt() {
    int i, len;
    char* str[] = { "0", "1", "3", "10", "13", "199", "2000", "23031" };
    len = sizeof(str) / sizeof(str[0]);
    for(i = 0; i < len; i++)
        printf("\"%s\" -> %d\n", str[i], parseInt(str[i]));
}

void testCharToInt() {
    int i;
    char chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c' };
    int len = sizeof(chars) / sizeof(char);
    for(i = 0; i < len; i++) {
        printf("charToInt('%c'):  %d\n", chars[i], charToInt(chars[i]));
    }
}
/*
void testParseBinary() {
    int i, len;
    char* str[] = { "00011", "100", "110", "1000", "10000" };
    len = sizeof(str) / sizeof(str[0]);
    for(i = 0; i < len; i++)
        printf("\"%s\" -> %b\n", str[i], parseInt(str[i]));
}
*/

main(int argc, char** argv) {
//    testIsDecimal();
//    testPower();
//    testCharToInt();
//    testParseInt();
    if (argc >= 3) {
        bitwise(parseInt(argv[1]), parseInt(argv[2]));
    } else {
        printf("Usage: ./bitwise <n> <b>\n");
    }
}
