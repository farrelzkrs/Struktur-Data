/*
	Nama	: Farrel Zikri Suryahadi
	NPM		: 23081010213
	Kelas	: Struktur Data E081
	Tugas	: Data Stack
*/

#include <stdio.h>
#include <stdlib.h>
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
int isFull();
int cntStc(node *top);
void dltStc(node **top);
void showStc(node *top);

int main() {
    node *top = NULL;
    char ch;
    int num;

    do {
        system("cls");
        printf("Pilih operasi stack!\n");
        printf("1. Push data\n");
        printf("2. Pop data\n");
        printf("3. Stack Top\n");
        printf("4. Empty Stack\n");
        printf("5. Full Stack\n");
        printf("6. Stack Count\n");
        printf("7. Destroy Stack\n");
        printf("8. Tampilkan stack\n");
        printf("Pilihan (x = keluar) : ");
        scanf("%c", &ch);

        switch (ch) {
        case '1':
        	system("cls");
            printf("Masukkan data : ");
            scanf("%d", &num);
            push(&top, num);
            getch();
            break;
        case '2':
            num = pop(&top);
            if (num != -1)
                printf("\nPop data : %d\n", num);
            else
                printf("\nStack kosong! Tidak bisa menghapus.\n");
            getch();
            break;
        case '3':
            num = head(top);
            if (num != -1)
                printf("\nData paling atas : %d\n", num);
            else
                printf("\nStack kosong.\n");
            getch();
            break;
        case '4':
            printf(isEmpty(top) ? "\nStack kosong.\n" : "\nStack tidak kosong.\n");
            getch();
            break;
        case '5':
            printf(isFull() ? "\nStack penuh.\n" : "\nStack tidak penuh.\n");
            getch();
            break;
        case '6':
            printf("\nJumlah elemen dalam stack: %d\n", cntStc(top));
            getch();
            break;
        case '7':
            dltStc(&top);
            printf("\nSeluruh stack dihapus.\n");
            getch();
            break;
        case '8':
            showStc(top);
            getch();
            break;
        }
    } while (ch != 'x');

    return 0;
}

void push(node **top, int num) {
    if (isFull()) {
        printf("Stack penuh, tidak bisa menambahkan data.\n");
        return;
    }

    node *pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }

    pNew->data = num;
    pNew->nxt = *top;
    *top = pNew;

    printf("Data %d berhasil masuk.\n", num);
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

int isFull() {
    node *temp = (node *)malloc(sizeof(node));
    if (temp == NULL) {
        return 1;
    }
    free(temp);
    return 0;
}

int cntStc(node *top) {
    int count = 0;
    node *pWalker = top;
    while (pWalker != NULL) {
        count++;
        pWalker = pWalker->nxt;
    }
    return count;
}

void dltStc(node **top) {
    node *temp;
    while (*top != NULL) {
        temp = *top;
        *top = (*top)->nxt;
        free(temp);
    }
}

void showStc(node *top) {
    node *pWalker = top;

    printf("\nData dalam stack:\n");
    if (pWalker == NULL) {
        printf("Stack kosong\n");
    } else {
        while (pWalker != NULL) {
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->nxt;
        }
        printf("NULL\n");
    }
}
