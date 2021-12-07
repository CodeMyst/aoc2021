#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

const char INPUT_FILE[] = "input";

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    char c;
    int pos;
    int ncrabs = 0;
    int max_pos = -1;
    do {
        fscanf(fp, "%d", &pos);
        c = fgetc(fp);

        if (pos > max_pos) max_pos = pos;

        ncrabs++;
    } while (c == ',');
    fseek(fp, 0, SEEK_SET);

    int crabs[ncrabs];

    for (int i = 0; i < ncrabs; i++) {
        fscanf(fp, "%d", &crabs[i]);
        fseek(fp, 1, SEEK_CUR);
    }

    int fuel = 0;
    int min_fuel = INT_MAX;
    int min_pos = 0;
    for (int i = 0; i < max_pos; i++) {
        fuel = 0;

        for (int j = 0; j < ncrabs; j++) {
            fuel += abs(crabs[j] - i);
        }

        if (fuel < min_fuel) {
            min_fuel = fuel;
            min_pos = i;
        }
    }

    printf("min fuel to align crabs: %d, to %d\n", min_fuel, min_pos);

    return 0;
}
