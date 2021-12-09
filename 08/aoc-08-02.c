#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[] = "input";

// counts the number of common characters between 2 strings
int common(char* a, char* b) {
    int c = 0;

    for (int i = 0; i < strlen(a); i++) {
        for (int j = 0; j < strlen(b); j++) {
            if (a[i] == b[j]) c++;
        }
    }

    return c;
}

// gets the proper digit based on the known four and seven characters
//
// 4 and 0 -> 3 common
// 4 and 2 -> 2 common
// 4 and 3 -> 3 common
// 4 and 5 -> 3 common
// 4 and 6 -> 3 common
// 4 and 9 -> 4 common
//
// 7 and 0 -> 3 common
// 7 and 2 -> 2 common
// 7 and 3 -> 3 common
// 7 and 5 -> 2 common
// 7 and 6 -> 2 common
// 7 and 9 -> 3 common
char get_digit(char* four, char* seven, char* input) {
    char digit = 0;

    int len = strlen(input);

    // 2 | 3 | 5
    if (len == 5) {
        // 2
        if (common(four, input) == 2 && common(seven, input) == 2) { digit = 2; }
        // 3
        else if (common(four, input) == 3 && common(seven, input) == 3) { digit = 3; }
        // 5
        else if (common(four, input) == 3 && common(seven, input) == 2) { digit = 5; }
    // 0 | 6 | 9
    } else if (len == 6) {
        // 0
        if (common(four, input) == 3 && common(seven, input) == 3) { digit = 0; }
        // 6
        else if (common(four, input) == 3 && common(seven, input) == 2) { digit = 6; }
        // 9
        else if (common(four, input) == 4) { digit = 9; }
    // 4
    } else if (len == 4) {
        digit = 4;
    // 7
    } else if (len == 3) {
        digit = 7;
    // 1
    } else if (len == 2) {
        digit = 1;
    // 8
    } else if (len == 7) {
        digit = 8;
    }

    return digit;
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    char four[5];
    char seven[4];

    char buff[8];

    int singleres = 0;
    int res = 0;

    while (1) {
        // read input and find 4 and 7 numbers
        for (int i = 0; i < 10; i++) {
            fscanf(fp, "%s", buff);

            int len = strlen(buff);

            if (len == 4) { // 4
                strcpy(four, buff);
            } else if (len == 3) { // 7
                strcpy(seven, buff);
            }
        }

        // skip delimiter
        fgetc(fp);
        fgetc(fp);

        singleres = 0;

        // read output
        for (int i = 0; i < 4; i++) {
            fscanf(fp, "%s", buff);
            singleres = (singleres * 10) + get_digit(four, seven, buff);
        }

        if (fgetc(fp) == EOF) break;

        res += singleres;
    }

    printf("res: %d\n", res);

    return 0;
}
