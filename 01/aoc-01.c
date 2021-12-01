#include <stdio.h>
#include <stdlib.h>

const char INPUT_PATH[] = "input";

const int MAX_LINE_LEN = 6;

int main() {
    FILE* fp = fopen(INPUT_PATH, "r");

    if (fp == NULL) return 1;

    char buffer[10];

    int prev = -1;
    int increments = 0;
    while (fgets(buffer, 10, fp)) {
        int val = atoi(buffer);

        if (prev != -1 && val > prev) increments++;

        prev = val;
    }

    printf("number of increments: %d\n", increments);

    fclose(fp);

    return 0;
}
