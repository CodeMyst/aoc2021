#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[] = "input";

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    int res = 0;

    char c;
    int delim = 0;
    char buff[10];
    do {
        if (!delim) {
            c = fgetc(fp);

            if (c == '|') delim = 1;
        } else {
            for (int i = 0; i < 4; i++) {
                fscanf(fp, "%s", buff);

                int len = strlen(buff);

                if (len == 2 || // 1
                    len == 4 || // 4
                    len == 3 || // 7
                    len == 7) { // 8
                    res++;
                }
            }
            delim = 0;
        }
    } while (c != EOF);

    printf("res: %d\n", res);

    return 0;
}
