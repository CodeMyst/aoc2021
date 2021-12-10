#include <stdio.h>
#include <stdlib.h>

const char INPUT_FILE[] = "input";

enum { STACK_SIZE = 100 };

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
    if (c == ')') return 1;
    else if (c == ']') return 2;
    else if (c == '}') return 3;
    else return 4;
}

char get_reverse(char c) {
    if (c == '(') return ')';
    else if (c == '[') return ']';
    else if (c == '{') return '}';
    else return '>';
}

void sort(long arr[], int n) {
    for (int i = 1; i < n; i++) {
        long key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    // if a line is invalid we'll just skip further checking until a new line is started
    int invalid = 0;

    int scores_i = 0;
    long scores[100];

    char c;
    do {
        c = fgetc(fp);

        if (!invalid) {
            if (c == '(' || c == '[' || c == '{' || c == '<') {
                stack_push(c);
            } else if (c == ')' || c == ']' || c == '}' || c == '>') {
                // closing but not opened
                if (stack_empty()) {
                    invalid = 1;
                }

                char last = stack_pop();

                // wrong closing
                if (!compat(last, c)) {
                    invalid = 1;
                }
            }
        }

        if (c == '\n') {
            // missing closing
            if (!invalid && !stack_empty()) {
                long score = 0;
                while (!stack_empty()) {
                    char closing = get_reverse(stack_pop());
                    score = score * 5 + get_score(closing);
                }
                scores[scores_i++] = score;
            }
            
            stack_reset();
            
            invalid = 0;
        }
    } while (c != EOF);

    sort(scores, scores_i);

    printf("middle score: %ld\n", scores[scores_i / 2]);

    return 0;
}
