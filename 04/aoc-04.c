#include <stdlib.h>
#include <stdio.h>

// after lots of painful hours i finally did it...

const char INPUT_FILE[] = "input";

int check_bingo(int b[5][5]) {
    int sum = 0;
    for (int x = 0; x < 5; x++) {
        sum = 0;
        for (int y = 0; y < 5; y++) {
            sum += b[x][y];
        }

        if (sum == -5) return 1;
    }

    for (int x = 0; x < 5; x++) {
        sum = 0;
        for (int y = 0; y < 5; y++) {
            sum += b[y][x];
        }

        if (sum == -5) return 1;
    }

    return 0;
}

int sum(int b[5][5]) {
    int sum = 0;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (b[x][y] != -1) sum += b[x][y];
        }
    }

    return sum;
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    // count combinations
    int comb_size = 1;
    char c;
    while ((c = getc(fp)) != EOF) {
        if (c == ',') comb_size++;
    }
    fseek(fp, 0, SEEK_SET);

    // count boards
    int boards_size = 0;
    char prevc = 0;
    while ((c = getc(fp)) != EOF) {
        if (c == '\n' && prevc == '\n') {
            boards_size++;
        }
        prevc = c;       
    }
    fseek(fp, 0, SEEK_SET);

    int combs[comb_size];

    // read combinations
    for (int i = 0; i < comb_size; i++) {
        fscanf(fp, "%d", &combs[i]);
        fseek(fp, 1, SEEK_CUR);
    }

    int boards[boards_size][5][5];

    // skip combinations
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp, "%*[^\n]\n");

    for (int i = 0; i < boards_size; i++) {
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                fscanf(fp, "%d", &boards[i][x][y]);
            }
        }
    }

    int won_boards[boards_size];
    for (int i = 0; i < boards_size; i++) won_boards[i] = 0;
    int nwon = 0;

    int first = 0;
    int last = 0;

    // for every combination
    for (int i = 0; i < comb_size; i++) {
        // for every board
        for (int b = 0; b < boards_size; b++) {
            if (won_boards[b] == 1) continue;

            // mark hits
            for (int x = 0; x < 5; x++) {
                for (int y = 0; y < 5; y++) {
                    if (boards[b][x][y] == combs[i]) {
                        boards[b][x][y] = -1;
                    }
                }
            }

            if (check_bingo(boards[b])) {
                if (nwon == 0) first = sum(boards[b]) * combs[i];
                if (nwon == boards_size - 1) last = sum(boards[b]) * combs[i];

                nwon++;
                won_boards[b] = 1;
            }
        }
    }

    printf("first to win sum: %d\n", first);
    printf("last to win sum: %d\n", last);

    return 0;
}
