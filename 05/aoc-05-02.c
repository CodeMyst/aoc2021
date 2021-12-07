#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char INPUT_FILE[] = "input";

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    int max_x = 0;
    int max_y = 0;

    char buffer[25];
    while (fgets(buffer, 25, fp) != NULL) {
        int x1;
        int x2;
        int y1;
        int y2;

        sscanf(buffer, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

        if (x1 > max_x) max_x = x1;
        if (x2 > max_x) max_x = x2;
        if (y1 > max_y) max_y = y1;
        if (y2 > max_y) max_y = y2;
    }
    fseek(fp, 0, SEEK_SET);

    max_x++;
    max_y++;

    printf("%d %d\n", max_x, max_y);

    int field[max_x][max_y];

    for (int y = 0; y < max_y; y++) {
        for (int x = 0; x < max_x; x++) {
            field[x][y] = 0;
        }
    }

    while (fgets(buffer, 25, fp) != NULL) {
        int x1;
        int x2;
        int y1;
        int y2;

        sscanf(buffer, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

        int start = -1;
        int end = -1;

        if (y1 == y2) {
            start = x1;
            end = x2;

            if (start > end) {
                start = x2;
                end = x1;
            }

            for (int x = start; x <= end; x++) {
                field[x][y1]++;
            }
        } else if (x1 == x2) {
            start = y1;
            end = y2;

            if (start > end) {
                start = y2;
                end = y1;
            }

            for (int y = start; y <= end; y++) {
                field[x1][y]++;
            }
        } else if (abs(x1 - x2) == abs(y1 - y2)) {
            int s = abs(x1 - x2);

            int startx = x1;
            int starty = y1;

            int slopex = x1 > x2 ? 1 : -1;
            int slopey = y1 > y2 ? 1 : -1;

            for (int i = 0; i <= s; i++) {
                field[startx][starty]++;
                startx -= slopex;
                starty -= slopey;
            }
        }
    }

    int points = 0;

    for (int y = 0; y < max_y; y++) {
        for (int x = 0; x < max_x; x++) {
            printf("%d ", field[x][y]);
            if (field[x][y] >= 2) points++;
        }
        printf("\n");
    }

    printf("points: %d\n", points);

    return 0;
}
