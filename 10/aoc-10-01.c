#include <stdio.h>
#include <stdlib.h>

const char INPUT_FILE[] = "input";

enum { STACK_SIZE = 50 };

size_t top = -1;

char stack[STACK_SIZE];

int stack_empty() {
    return top == -1 ? 1 : 0;
}

int stack_full() {
    return top == STACK_SIZE;
}

char stack_peek() {
    return stack[top];
}

char stack_pop() {
    if (stack_empty()) {
        printf("trying to pop an empty stack");
        return 0;
    }

    return stack[top--];
}

void stack_push(char data) {
    if (stack_full()) {
        printf("trying to push to a full stack");
        return;
    }

    stack[++top] = data;
}

void stack_reset() {
    top = -1;
}

int compat(char a, char b) {
    if (a == '(') return b == ')';
    else if (a == '[') return b == ']';
    else if (a == '{') return b == '}';
    else return b == '>';
}

int get_score(char c) {
    if (c == ')') return 3;
    else if (c == ']') return 57;
    else if (c == '}') return 1197;
    else return 25137;
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    // if a line is invalid we'll just skip further checking until a new line is started
    int invalid = 0;

    int score = 0;

    char c;
    do {
        c = fgetc(fp);

        if (!invalid) {
            if (c == '(' || c == '[' || c == '{' || c == '<') {
                stack_push(c);
            } else if (c == ')' || c == ']' || c == '}' || c == '>') {
                if (stack_empty()) {
                    printf("incomplete line, skipping...\n");
                    invalid = 1;
                }

                char last = stack_pop();

                if (!compat(last, c)) {
                    score += get_score(c);
                    printf("expected closing %c, found %c, score: %d\n", last, c, get_score(c));
                    invalid = 1;
                }
            }
        }

        if (c == '\n') {
            if (!invalid) printf("line was valid\n");
            stack_reset();
            invalid = 0;
        }
    } while (c != EOF);

    printf("score: %d\n", score);

    return 0;
}
