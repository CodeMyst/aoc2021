#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[] = "input";

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    int width = 0;
    int height = 0;

    // calculate the width and height
    char buffer[200];
    while (fgets(buffer, 200, fp) != NULL) {
        width = strlen(buffer) - 1;

        height++;
    }
    rewind(fp);

    int map[width][height];

    // load the map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char c = fgetc(fp);
            map[x][y] = atoi(&c);
        }
        fgetc(fp);
    }

    // print map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%d", map[x][y]);
        }
        printf("\n");
    }

    int sum = 0;

    // check lowest points
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // number of neighbours larger then current cell
            int n = 0;

            int c = map[x][y];

            // if on edge
            if (x == 0) n++;
            if (x == width - 1) n++;
            if (y == 0) n++;
            if (y == height - 1) n++;

            // if not on edge and larger
            if (x > 0 && map[x-1][y] > c) n++;
            if (x < width - 1 && map[x+1][y] > c) n++;
            if (y > 0 && map[x][y-1] > c) n++;
            if (y < height - 1 && map[x][y+1] > c) n++;

            if (n == 4) sum += c + 1;
        }
    }

    printf("res: %d\n", sum);

    return 0;
}
