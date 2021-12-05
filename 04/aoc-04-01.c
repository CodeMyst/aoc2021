#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[] = "input";

// board as a linked list
typedef struct BoardData {
    int data[5][5];
    struct BoardData* next;
} Board;

// adds the board as the last elements in the linked list
void board_add(Board** root, int data[5][5]) {
    Board* new = (Board*) malloc(sizeof(Board)); 
    Board* last = *root;
    
    memcpy(new->data, data, 25 * sizeof(int));

    new->next = NULL;

    if (*root == NULL) {
        *root = new;
        return;
    }

    while (last->next != NULL) last = last->next;

    last->next = new;
}

int boards_size(Board* root) {
    int size = 1;
    while (root->next != NULL) {
        size++;
        root = root->next;
    }

    return size;
}

void board_print(Board* root) {
    while (root->next != NULL) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                printf("%d ", root->data[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        root = root->next;
    }
}

// checks if the board won
int board_check(Board* root, int combs[], int combs_size) {
    int hits = 0;
    int won = 0;
    long sum = 0;

    // for every row
    for (int i = 0; i < 5; i++) {
        // for every column
        for (int j = 0; j < 5; j++) {
            // for every combination
            int hit = 0;
            for (int k = 0; k < combs_size; k++) {
                if (root->data[i][j] == combs[k]) {
                    hits++;
                    hit = 1;
                    break;
                }
            }

            if (!hit) {
                sum += root->data[i][j];
            }
        }

        if (hits == 5) {
            won = 1;
        } else {
            hits = 0;
        }
    }

    if (won) {
        return sum * combs[combs_size-1];
    }

    return 0;
}

void boards_free(Board* root) {
    Board* tmp;
    
    while (root != NULL) {
        tmp = root;
        root = root->next;
        free(tmp);
    }
}

// check all boards
int boards_check(Board* root, int combs[], int combs_size) {
    while (root->next != NULL) {
        int res = board_check(root, combs, combs_size);

        if (res != 0) return res;

        root = root->next;
    }

    return 0;
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    int combinations[50];
    int comb_i = 0;

    // load all combinations
    char del;
    do {
        fscanf(fp, "%d", &combinations[comb_i]);
        fscanf(fp, "%c", &del);
        comb_i++;
    } while (del == ',');

    // skip newline
    fseek(fp, 1, SEEK_CUR);

    Board* boards = NULL;

    char buffer[20];
    int nums[5][5];

    // load boards
    int empty = 0;
    while(!empty) {
        for (int i = 0; i < 5; i++) {
            if (fgets(buffer, 20, fp) == NULL) {
                empty = 1;
                break;
            }

            sscanf(buffer, "%d %d %d %d %d", &nums[i][0], &nums[i][1], &nums[i][2], &nums[i][3], &nums[i][4]);
        }

        if (!empty) {
            // skip newline
            fseek(fp, 1, SEEK_CUR);

            board_add(&boards, nums);
        }
    }

    printf("number of boards: %d\n\n", boards_size(boards));

    /* board_print(boards); */

    // check winning boards
    for (int i = 0; i < comb_i; i++) {
        int res = boards_check(boards, combinations, i+1);

        if (res != 0) {
            printf("bingo, res: %d\n", res);
            break;
        }
    }

    boards_free(boards);

    fclose(fp);

    return 0;
}
