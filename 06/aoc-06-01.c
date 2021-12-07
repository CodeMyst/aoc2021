#include <stdio.h>
#include <stdlib.h>

const char INPUT_FILE[] = "input_example";

typedef struct {
    char timer;
} Fish;

typedef struct {
    Fish* arr;
    size_t length;
    size_t capacity;
} School;

void init_school(School* s, size_t initial_capacity) {
    s->arr = malloc(initial_capacity * sizeof(Fish));
    s->length = 0;
    s->capacity = initial_capacity;
}

void insert_school(School* s, Fish fish) {
    if (s->length == s->capacity) {
        s->capacity *= 2;
        s->arr = realloc(s->arr, s->capacity * sizeof(Fish));
    }

    s->arr[s->length++] = fish;
}

void print_school(School* s) {
    for (int i = 0; i < s->length; i++) {
        if (i == s->length - 1) {
            printf("%d", s->arr[i].timer);
        } else {
            printf("%d, ", s->arr[i].timer);
        }
    }
}

void simulate_school(School* s) {
    for (int i = 0; i < s->length; i++) {
        if (s->arr[i].timer == 0) {
            s->arr[i].timer = 6;

            Fish new = { 9 };
            insert_school(s, new);
        } else {
            s->arr[i].timer--;
        }
    }
}

void free_school(School* s) {
    free(s->arr);
    s->arr = NULL;
    s->length = 0;
    s->capacity = 0;
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    School school;
    init_school(&school, 1);

    char c;
    int timer;
    do {
        fscanf(fp, "%d", &timer);
        c = fgetc(fp);

        Fish f = { timer };
        insert_school(&school, f);
    } while (c == ',');

    printf("initial state: ");
    print_school(&school);
    printf("\n");

    for (int i = 0; i < 80; i++) {
        simulate_school(&school);
    }

    printf("number of fish: %ld\n", school.length);

    free_school(&school);

    return 0;
}
