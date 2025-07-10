#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[1000];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == 1000 - 1;
}

void psh(Stack *s, char ch) {
    if (!isFull(s)) {
        s->data[++(s->top)] = ch;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';
}

char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0';
}

int match(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']') ||
           (open == '<' && close == '>');
}

int valid(const char *code) {
    Stack stc;
    initStack(&stc);
    int i = 0;

    while (code[i] != '\0') {
        char ch = code[i];
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            psh(&stc, ch);
        } else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (isEmpty(&stc) || !match(pop(&stc), ch)) {
                return 0;
            }
        }
        i++;
    }

    return isEmpty(&stc);
}

int main() {
    char code[5000];
    printf("Masukkan kode yang ingin diperiksa (akhiri dengan baris kosong):\n");

    char line[512];
    code[0] = '\0';
    while (fgets(line, sizeof(line), stdin) != NULL && line[0] != '\n') {
        strcat(code, line);
    }

    if (valid(code)) {
        printf("Kode valid: Code berjalan lancar.\n");
    } else {
        printf("Kode tidak valid: Ada bracket yang tidak sesuai.\n");
    }

    return 0;
}
