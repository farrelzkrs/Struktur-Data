/*
	Nama	: Farrel Zikri Suryahadi
	NPM		: 23081010213
	Kelas	: Struktur Data E081
	Tugas	: Double Linked List
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct node
{
    int data;
    struct node *lft;
    struct node *rgt;
};
typedef struct node node;

void tambahAwal(node **dlist);
void tambahData(node **dlist);
void tambahAkhir(node **dlist);
void delData(node **dlist);
void delAwal(node **dlist);
void delTengah(node **dlist);
void delAkhir(node **dlist);
void tampilData(node *dlist);
int countData(node *dlist);
int sumData(node *dlist);
node *srcData(node *dlist, int num);

int main()
{
    node *dlist = NULL;
    char ch;
    int num;

    do
    {
        system("cls");
        printf("Masukkan pilihan anda :\n");
        printf("1. Tambahkan data di awal\n");
        printf("2. Tambahkan data di tengah dlist\n");
        printf("3. Tambahkan data di akhir\n");
        printf("4. Hapus data\n");
        printf("5. Tampilkan semua data\n");
        printf("6. Cari data\n");
        printf("7. Tampilkan jumlah data\n");
        printf("8. Tampilkan hasil penjumlahan semua data\n");
        printf("Masukkan pilihan anda (Tekan 'x' untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &ch);

        switch (ch)
        {
        case '1':
            tambahAwal(&dlist);
            break;
        case '2':
            tambahData(&dlist);
            break;
        case '3':
            tambahAkhir(&dlist);
            break;
        case '4':
            delData(&dlist);
            getch();
            break;
        case '5':
            tampilData(dlist);
            getch();
            break;
        case '6':
            system("cls");
            printf("\nMasukkan data yang dicari : ");
            scanf("%d", &num);
            node *hasil = srcData(dlist, num);
            tampilData(dlist);
            if (hasil != NULL)
            {
                printf("Data %d ditemukan\n", hasil->data);
            }
            else
            {
                printf("Data %d tidak ditemukan\n", num);
            }
            getch();
            break;
        case '7':
            printf("\nJumlah data dalam linked dlist : %d\n", countData(dlist));
            getch();
            break;
        case '8':
            printf("\nHasil penjumlahan semua data : %d\n", sumData(dlist));
            getch();
            break;
        }

    } while (ch != 'x');

    return 0;
}

void tambahAwal(node **dlist)
{
    int num;
    node *pNew;

    system("cls");
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = num;
        pNew->rgt = *dlist;
        pNew->lft = NULL;

        if (*dlist != NULL)
        {
            (*dlist)->lft = pNew;
        }

        *dlist = pNew;
    }
    else
    {
        printf("Alokasi memori gagal");
        getch();
    }
}

void tambahData(node **dlist)
{
    int pos, num;
    node *pNew, *pCur;

    system("cls");
    tampilData(*dlist);
    printf("\nPosisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    pCur = *dlist;
    while (pCur != NULL && pCur->data != pos)
    {
        pCur = pCur->rgt;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL)
    {
        printf("\nNode tidak ditemukan\n");
        getch();
    }
    else if (pNew == NULL)
    {
        printf("\nAlokasi memori gagal\n");
        getch();
    }
    else
    {
        pNew->data = num;
        pNew->rgt = pCur->rgt;
        pNew->lft = pCur;

        if (pCur->rgt != NULL)
        {
            pCur->rgt->lft = pNew;
        }

        pCur->rgt = pNew;
    }
}

void tambahAkhir(node **dlist)
{
    int num;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL)
    {
        printf("Alokasi memori gagal");
        getch();
        return;
    }

    pNew->data = num;
    pNew->rgt = NULL;

    if (*dlist == NULL)
    {
        pNew->lft = NULL;
        *dlist = pNew;
    }
    else
    {
        pCur = *dlist;
        while (pCur->rgt != NULL)
        {
            pCur = pCur->rgt;
        }

        pCur->rgt = pNew;
        pNew->lft = pCur;
    }
}

void delData(node **dlist)
{
    int ch;

    system("cls");
    tampilData(*dlist);
    printf("\nPilih opsi hapus :\n");
    printf("1. Hapus data di awal\n");
    printf("2. Hapus data di tengah\n");
    printf("3. Hapus data di akhir\n");
    printf("Masukkan pilihan : ");
    fflush(stdin);
    scanf("%d", &ch);

    if(ch == 1) {
        delAwal(dlist);
        return;
    }
    else if (ch == 2) {
        delTengah(dlist);
        return;
    }
    else if (ch == 3) {
        delAkhir(dlist);
        return;
    }
    else {
        printf("Input salah!");
        return;
    }
}

void delAwal(node **dlist)
{
    if (*dlist == NULL)
    {
        printf("List kosong\n");
        return;
    }

    node *temp = *dlist;

    *dlist = (*dlist)->rgt;

    if (*dlist != NULL)
    {
        (*dlist)->lft = NULL;
    }

    free(temp);
    printf("Node di awal berhasil dihapus.\n");
}

void delTengah(node **dlist)
{
    if (*dlist == NULL)
    {
        printf("List kosong\n");
        return;
    }

    tampilData(*dlist);

    int data;
    printf("\nMasukkan nilai data yang ingin dihapus : ");
    fflush(stdin);
    scanf("%d", &data);

    node *pCur = *dlist;

    while (pCur != NULL && pCur->data != data)
    {
        pCur = pCur->rgt;
    }

    if (pCur == NULL)
    {
        printf("Data %d tidak ditemukan\n", data);
        return;
    }

    if (pCur->lft != NULL)
    {
        pCur->lft->rgt = pCur->rgt;
    }

    if (pCur->rgt != NULL)
    {
        pCur->rgt->lft = pCur->lft;
    }

    if (pCur == *dlist)
    {
        *dlist = pCur->rgt;
    }

    free(pCur);
    printf("Node dengan data %d berhasil dihapus.\n", data);
}

void delAkhir(node **dlist)
{
    if (*dlist == NULL)
    {
        printf("List kosong\n");
        return;
    }

    node *pCur = *dlist;

    while (pCur->rgt != NULL)
    {
        pCur = pCur->rgt;
    }

    if (pCur->lft != NULL)
    {
        pCur->lft->rgt = NULL;
    }
    else
    {
        *dlist = NULL;
    }

    free(pCur);
    printf("Node di akhir berhasil dihapus.\n");
}

node *srcData(node *dlist, int num)
{
    node *pCur = dlist;
    while (pCur != NULL)
    {
        if (pCur->data == num)
        {
            return pCur;
        }
        pCur = pCur->rgt;
    }
    return NULL;
}

void tampilData(node *dlist)
{
    node *pWalker = dlist;

    system("cls");
    printf("Data dalam double linked dlist :\n");
    if (pWalker == NULL)
    {
        printf("Linked list kosong\n\n");
    }
    else
    {
        while (pWalker != NULL)
        {
            printf("%d <=> ", pWalker->data);
            pWalker = pWalker->rgt;
        }
        printf("NULL\n\n");
    }
}

int countData(node *dlist)
{
    system("cls");
    tampilData(dlist);
    int cnt = 0;
    node *pWalker = dlist;

    while (pWalker != NULL)
    {
        cnt++;
        pWalker = pWalker->rgt;
    }

    return cnt;
}

int sumData(node *dlist)
{
    system("cls");
    tampilData(dlist);
    int sum = 0;
    node *pWalker = dlist;

    while (pWalker != NULL)
    {
        sum += pWalker->data;
        pWalker = pWalker->rgt;
    }

    return sum;
}
