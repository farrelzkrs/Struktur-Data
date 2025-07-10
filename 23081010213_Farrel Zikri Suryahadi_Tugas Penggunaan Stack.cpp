/*
	Nama	: Farrel Zikri Suryahadi
	NPM		: 23081010213
	Kelas	: Struktur Data E081
	Tugas	: Penggunaan Stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

struct node {
    int data;
    struct node *nxt;
};
typedef struct node node;

void push(node **top, int num);
int pop(node **top);
int head(node *top);
int isEmpty(node *top);
void dltStc(node **top);
void tampilkanData(node *top);

int isBalancedParenthesis(const char *expr);
int evaluatePfx(const char *expr);
int precedence(char op);
void ifxToPfx(const char *ifx, char *pfx);

int main() {
    node *top = NULL;
    char ch;
    char exp[100];
    char pfx[100];
    int result;

    do {
        system("cls");
        printf("Pilih operasi stack!\n");
        printf("1. Matching Balancing Parenthesis\n");
        printf("2. Evaluate Postfix Expression\n");
        printf("3. Convert Infix to Postfix\n");
        printf("4. Tampilkan Data Stack\n");
        printf("Pilihan (x = keluar) : ");
        fflush(stdin);
        scanf("%c", &ch);

        switch (ch) {
        case '1':
            printf("Masukkan ekspresi dengan tanda kurung: ");
            scanf("%s", exp);
            if (isBalancedParenthesis(exp))
                printf("Tanda kurung seimbang.\n");
            else
                printf("Tanda kurung tidak seimbang.\n");
            getch();
            break;
        case '2':
            printf("Masukkan ekspresi postfix: ");
            scanf("%s", exp);
            result = evaluatePfx(exp);
            printf("Hasil evaluasi: %d\n", result);
            getch();
            break;
        case '3':
            printf("Masukkan ekspresi infix: ");
            scanf("%s", exp);
            ifxToPfx(exp, pfx);
            printf("Ekspresi postfix: %s\n", pfx);
            getch();
            break;
        case '4':
            printf("Data dalam stack: \n");
            tampilkanData(top);
            getch();
            break;
        }
    } while (ch != 'x');

    return 0;
}

void tampilkanData(node *top) {
    if (isEmpty(top)) {
        printf("Stack kosong.\n");
        return;
    }

    node *temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->nxt;
    }
    printf("\n");
}

void push(node **top, int num) {
    node *pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }

    pNew->data = num;
    pNew->nxt = *top;
    *top = pNew;
}

int pop(node **top) {
    if (*top == NULL) {
        return -1;
    }

    node *temp = *top;
    int data = temp->data;
    *top = (*top)->nxt;
    free(temp);

    return data;
}

int head(node *top) {
    if (top == NULL) {
        return -1;
    }
    return top->data;
}

int isEmpty(node *top) {
    return top == NULL;
}

void dltStc(node **top) {
    node *temp;
    while (*top != NULL) {
        temp = *top;
        *top = (*top)->nxt;
        free(temp);
    }
}

int isBalancedParenthesis(const char *expr) {
    node *stack = NULL;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
            push(&stack, expr[i]);
        } else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
            if (isEmpty(stack)) return 0;
            char topChar = pop(&stack);
            if ((expr[i] == ')' && topChar != '(') ||
                (expr[i] == '}' && topChar != '{') ||
                (expr[i] == ']' && topChar != '['))
                return 0;
        }
    }
    int balanced = isEmpty(stack);
    dltStc(&stack);
    return balanced;
}

int evaluatePfx(const char *expr) {
    node *stack = NULL;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            push(&stack, expr[i] - '0');
        } else {
            int val2 = pop(&stack);
            int val1 = pop(&stack);
            switch (expr[i]) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
            }
        }
    }
    int result = pop(&stack);
    dltStc(&stack);
    return result;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void ifxToPfx(const char *ifx, char *pfx) {
    node *stack = NULL;
    int j = 0;
    for (int i = 0; ifx[i] != '\0'; i++) {
        if (isdigit(ifx[i])) {
            pfx[j++] = ifx[i];
        } else if (ifx[i] == '(') {
            push(&stack, ifx[i]);
        } else if (ifx[i] == ')') {
            while (!isEmpty(stack) && head(stack) != '(')
                pfx[j++] = pop(&stack);
            pop(&stack);
        } else {
            while (!isEmpty(stack) && precedence(ifx[i]) <= precedence(head(stack)))
                pfx[j++] = pop(&stack);
            push(&stack, ifx[i]);
        }
    }
    while (!isEmpty(stack))
        pfx[j++] = pop(&stack);
    pfx[j] = '\0';
    dltStc(&stack);
}
