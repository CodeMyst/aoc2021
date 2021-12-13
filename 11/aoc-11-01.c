#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const char INPUT_FILE[] = "input";

const int width = 10;
const int height = 10;

int flashes = 0;

void inc_neighbours(int map[height][width], int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int nx = x + i;
            int ny = y + j;

            if (nx < 0 || ny < 0 || nx >= width || ny >= height) continue;

            map[ny][nx]++;

            if (map[ny][nx] == 10) {
                inc_neighbours(map, x + i, y + j);
                flashes++;
            }
        }
    }
}

void simulate_all(int map[height][width]) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x]++;
            if (map[y][x] == 10) {
                inc_neighbours(map, x, y);
                flashes++;
            }
        }
    }

    for (int y1 = 0; y1 < height; y1++) {
        for (int x1 = 0; x1 < width; x1++) {
            if (map[y1][x1] > 9) {
                map[y1][x1] = 0;
            }
        }
    }
}

void clear() {
    printf("\e[1;1H\e[2J");
}

void print_map(int map[height][width]) {
    clear();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int v = map[y][x];

            if (v == 0) {
                printf("\e[38;5;234m");
            } else if (v == 1) {
                printf("\e[38;5;236m");
            } else if (v == 2) {
                printf("\e[38;5;238m");
            } else if (v == 3) {
                printf("\e[38;5;240m");
            } else if (v == 4) {
                printf("\e[38;5;250m");
            } else if (v == 5) {
                printf("\e[38;5;243m");
            } else if (v == 6) {
                printf("\e[38;5;247m");
            } else if (v == 7) {
                printf("\e[38;5;249m");
            } else if (v == 8) {
                printf("\e[38;5;252m");
            } else if (v == 9) {
                printf("\e[38;5;255m");
            }

            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    int map[height][width];

    // load the map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char c = fgetc(fp);
            map[y][x] = atoi(&c);
        }
        fgetc(fp);
    }

    print_map(map);

    for (int i = 0; i < 100; i++) {
        simulate_all(map);
        print_map(map);
        usleep(50 * 1000);
    }

    printf("flashes: %d\n", flashes);

    return 0;
}
