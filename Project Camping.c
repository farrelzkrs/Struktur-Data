#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct mhs {
    char nama[50];
    char gender;
    struct mhs* nxt;
} mhs;

mhs* buatmhs(char* nama, char gender) {
    mhs* pNew = (mhs*)malloc(sizeof(mhs));
    if (!pNew) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(pNew->nama, nama);
    pNew->gender = gender;
    pNew->nxt = NULL;
    return pNew;
}

void addRound(mhs** list, char* nama, char gender, int* cnt) {
    mhs* pNew = buatmhs(nama, gender);

    if (*list == NULL) {
        *list = pNew;
        pNew->nxt = *list;
    } else {
        int mid = (*cnt) / 2;
        mhs* temp = *list;
        int i = 0;

        while (i < mid - 1) {
            temp = temp->nxt;
            i++;
        }

        pNew->nxt = temp->nxt;
        temp->nxt = pNew;

        if (strcmp(nama, "Cindy") == 0) {
            mhs* check = temp->nxt;
            if (check->gender == 'L') {
                printf("Cindy ngambek\n");
                delMhs(list, "Cindy", cnt);
            }
        }
    }

    (*cnt)++;
    printf("%s berhasil ditambahkan.\n", nama);
}

void addArsyadIrsyad(mhs** list, int* cnt) {
    addRound(list, "Arsyad", 'L', cnt);
    addRound(list, "Irsyad", 'L', cnt);
}

void delArsyadIrsyad(mhs** list, int* cnt) {
    delMhs(list, "Arsyad", cnt);
    delMhs(list, "Irsyad", cnt);
}

void delMhs(mhs** list, char* nama, int* cnt) {
    if (*list == NULL) {
        printf("Data masih kosong.\n");
        return;
    }

    mhs* temp = *list;
    mhs* pPre = NULL;

    do {
        if (strcmp(temp->nama, nama) == 0) {
            if (pPre == NULL) {
                mhs* pCur = *list;
                while (pCur->nxt != *list) {
                    pCur = pCur->nxt;
                }
                *list = temp->nxt;
                pCur->nxt = *list;
            } else {
                pPre->nxt = temp->nxt;
            }
            free(temp);
            (*cnt)--;
            printf("%s keluar dari lingkaran.\n", nama);

            if (strcmp(nama, "Arsyad") == 0 || strcmp(nama, "Irsyad") == 0) {
                delArsyadIrsyad(list, cnt);
            }

            return;
        }
        pPre = temp;
        temp = temp->nxt;
    } while (temp != *list);

    printf("%s tidak ada di lingkaran.\n", nama);
}

void pRound(mhs* list, char gender) {
    if (list == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    mhs* temp = list;
    do {
        if (temp->gender == gender) {
            printf("%s (%c) -> ", temp->nama, temp->gender);
        }
        temp = temp->nxt;
    } while (temp != list);
    printf("ROUND\n");
}

void choice() {
    printf("\nPilihan:\n");
    printf("1. Tambah mahasiswa/mahasiswi\n");
    printf("2. Hapus mahasiswa/mahasiswi\n");
    printf("3. Tampilkan lingkaran besar\n");
    printf("4. Tampilkan lingkaran laki-laki\n");
    printf("5. Tampilkan lingkaran perempuan\n");
    printf("0. Keluar\n");
    printf("Pilih opsi: ");
}

int main() {
    mhs* round = NULL;
    int cnt = 0;
    int ch;
    char nama[50], gender;

    do {
        system("cls");
        choice();
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("\nMasukkan nama: ");
                scanf("%s", nama);
                printf("Masukkan jenis kelamin (L/P): ");
                scanf(" %c", &gender);

                if (strcmp(nama, "Arsyad") == 0 || strcmp(nama, "Irsyad") == 0) {
                    addArsyadIrsyad(&round, &cnt);
                } else {
                    addRound(&round, nama, gender, &cnt);
                }

                getch();
                break;

            case 2:
                printf("\nMasukkan nama yang ingin dihapus: ");
                scanf("%s", nama);

                if (strcmp(nama, "Arsyad") == 0 || strcmp(nama, "Irsyad") == 0) {
                    delArsyadIrsyad(&round, &cnt);
                } else {
                    delMhs(&round, nama, &cnt);
                }

                getch();
                break;

            case 3:
                printf("Lingkaran Besar:\n");
                pRound(round, 'L');
                pRound(round, 'P');
                getch();
                break;

            case 4:
                printf("Lingkaran Laki-Laki:\n");
                pRound(round, 'L');
                getch();
                break;

            case 5:
                printf("Lingkaran Perempuan:\n");
                pRound(round, 'P');
                getch();
                break;

            case 0:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
                break;
        }

    } while (ch != 0);

    return 0;
}
