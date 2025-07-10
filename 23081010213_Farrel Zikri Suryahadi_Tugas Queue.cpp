#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 20

typedef struct Queue {
    int nilai[max];
    int front;
    int rear;
    int cnt;
} antre;

antre* makeQueue() {
    antre* q = (antre*)malloc(sizeof(antre));
    if (q == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    q->front = -1;
    q->rear = -1;
    q->cnt = 0;
    return q;
}

bool empty(antre* q) {
    return q->cnt == 0;
}

bool full(antre* q) {
    return q->cnt == max;
}

void enqueue(antre* q, int n) {
    if (full(q)) {
        printf("Antrean penuh, tidak dapat menambahkan nilai %d\n", n);
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear = (q->rear + 1) % max;
    q->nilai[q->rear] = n;
    q->cnt++;
    printf("Nilai %d berhasil ditambahkan.\n", n);
}

int dequeue(antre* q) {
    if (empty(q)) {
        printf("Antrean kosong.\n");
        return -1;
    }
    int n = q->nilai[q->front];
    q->front = (q->front + 1) % max;
    q->cnt--;
    printf("Nilai %d berhasil dihapus.\n", n);
    return n;
}

int queueFront(antre* q) {
    if (empty(q)) {
        printf("Antrean kosong.\n");
        return -1;
    }
    return q->nilai[q->front];
}

int queueCnt(antre* q) {
    return q->cnt;
}

void destroyQueue(antre* q) {
    if (q != NULL) {
        free(q);
        printf("Antrean dihapus sepenuhnya.\n");
    }
}

int main() {
    antre* q = makeQueue();
    int ch, n;

    do {
        system("cls");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Queue Front\n");
        printf("4. Empty Queue(?)\n");
        printf("5. Full Queue(?)\n");
        printf("6. Count Queue\n");
        printf("7. Destroy Queue\n");
        printf("8. Keluar Program\n\n");
        printf("Masukkan Pilihan Anda: ");
        scanf("%d", &ch);

        system("cls");

        switch (ch) {
            case 1:
                printf("Masukkan nilai untuk ditambahkan : ");
                scanf("%d", &n);
                enqueue(q, n);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                n = queueFront(q);
                if (n != -1) printf("Antrean pertama / terdepan : %d\n", n);
                break;
            case 4:
                printf(empty(q) ? "Antrean kosong.\n" : "Antrean tidak kosong.\n");
                break;
            case 5:
                printf(full(q) ? "Antrean penuh.\n" : "Antrean tidak penuh.\n");
                break;
            case 6:
                printf("Jumlah nilai dalam queue : %d\n", queueCnt(q));
                break;
            case 7:
                destroyQueue(q);
                q = makeQueue();
                break;
            case 8:
                printf("Keluar dari program.\n");
                destroyQueue(q);
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

        if (ch != 8) {
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
            getchar();
        }
    } while (ch != 8);

    return 0;
}
