#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

const char INPUT_FILE[] = "input";

// store graph vertex names, the index is used in the graph
char name_index[100][20] = {0};
size_t top = 0;

// store the visited caves
int caves[100] = {0};
size_t cave_top = 0;

// sets the adjacency matrix to 0
void init_mat(int n, int mat[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = 0;
        }
    }
}

// adds an edge to the adjacency matrix
void add_edge(int n, int mat[][n], int i, int j) {
    mat[i][j] = 1;
    mat[j][i] = 1;
}

// prints the adjacency matrix
void print_mat(int n, int mat[][n]) {
    for (int i = 0; i < n; i++) {
        printf("%5s: ", name_index[i]);
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// checks if the cave exists in the name index
int check_cave_exists(char* cave) {
    for (int i = 0; i < top; i++) {
        if (strcmp(cave, name_index[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

// returns the index of a cave by name
int get_cave_index(char* cave) {
    for (int i = 0; i < top; i++) {
        if (strcmp(cave, name_index[i]) == 0) {
            return i;
        }
    }

    return -1;
}

// adds the cave to the name index, if it exists already just returns the index
int add_cave_index(char* cave) {
    if (check_cave_exists(cave)) return get_cave_index(cave);

    strcpy(name_index[top++], cave);
    return top-1;
}

int paths = 0;

void count_paths(int n, int mat[][n], int src) {
    // if end print all caves
    if (src == get_cave_index("end")) {
        // adding the final cave to the stack just for printing
        caves[cave_top++] = src;

        for (int i = 0; i < cave_top; i++) {
            printf("%s ", name_index[caves[i]]);
        }
        printf("\n");

        paths++;
        cave_top--;

        return;
    }

    // if smol cave
    if (name_index[src][0] > 'Z') {
        // check if smol cave exists in visited caves
        for (int i = 0; i < cave_top; i++) {
            if (strcmp(name_index[src], name_index[caves[i]]) == 0) {
                return;
            }
        }
    }

    // add current cave to stack
    caves[cave_top++] = src;

    // count paths for adjacent nodes
    for (int i = 0; i < n; i++) {
        if (mat[src][i] == 1 || mat[i][src]) count_paths(n, mat, i);
    }

    // remove the current cave from the stack
    cave_top--;
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    // load all cave indices
    char buff[20];
    while (fgets(buff, 20, fp) != NULL) {
        char* a = strtok(buff, "-\n\r");
        int ind_a = add_cave_index(a);

        char* b = strtok(NULL, "-\n\r");
        int ind_b = add_cave_index(b);
    }
    rewind(fp);

    int adj[top][top];
    init_mat(top, adj);

    // load the caves into the adjacency matrix
    while (fgets(buff, 20, fp) != NULL) {
        char* a = strtok(buff, "-\n\r");
        int ind_a = get_cave_index(a);

        char* b = strtok(NULL, "-\n\r");
        int ind_b = get_cave_index(b);

        add_edge(top, adj, ind_a, ind_b);
    }

    print_mat(top, adj);

    printf("---\n");

    count_paths(top, adj, get_cave_index("start"));

    printf("paths: %d\n", paths);

    return 0;
}