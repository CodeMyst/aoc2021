#include <stdio.h>
#include <stdlib.h>

const char INPUT_FILE[] = "input";

void simulate(long* s) {
    for (int i = 0; i < 10; i++) {
        if (s[i] == 0) continue;

        if (i == 0) {
            s[7] += s[0];
            s[9] += s[0];
        } else {
            s[i-1] += s[i];
        }

        s[i] = 0;
    }
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    long school[10] = {0};

    char c;
    int timer;
    do {
        fscanf(fp, "%d", &timer);
        c = fgetc(fp);

        school[timer]++;
    } while (c == ',');

    for (int i = 0; i < 256; i++) {
        simulate(school);
    }

    long size = 0;
    for (int i = 0; i < 9; i++) {
        size += school[i];
    }

    printf("number of fish: %ld\n", size);

    return 0;
}
