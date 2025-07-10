/*
	Nama	: Farrel Zikri Suryahadi
	NPM		: 23081010213
	Kelas	: Struktur Data E081
	Tugas	: Circular Linked List
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct node
{
    int data;
    struct node *nxt;
};
typedef struct node node;

void tambahAwal(node **list);
void tambahData(node **list);
void tambahAkhir(node **list);
void delData(node **list);
void delAwal(node **list);
void delTengah(node **list);
void delAkhir(node **list);
void tampilData(node *list);
int countData(node *list);
int sumData(node *list);
node *srcData(node *list, int num);

int main()
{
    node *list = NULL;
    char ch;
    int num;

    do
    {
        system("cls");
        printf("Masukkan pilihan anda :\n");
        printf("1. Tambahkan data di awal\n");
        printf("2. Tambahkan data di tengah list\n");
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
            tambahAwal(&list);
            break;
        case '2':
            tambahData(&list);
            break;
        case '3':
            tambahAkhir(&list);
            break;
        case '4':
            delData(&list);
            getch();
            break;
        case '5':
            tampilData(list);
            getch();
            break;
        case '6':
            system("cls");
            printf("\nMasukkan data yang dicari : ");
            scanf("%d", &num);
            node *hasil = srcData(list, num);
            tampilData(list);
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
            printf("\nJumlah data dalam linked list : %d\n", countData(list));
            getch();
            break;
        case '8':
            printf("\nHasil penjumlahan semua data : %d\n", sumData(list));
            getch();
            break;
        }

    } while (ch != 'x');

    return 0;
}

//=====================================================
void tambahAwal(node **list)
{
    int num;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = num;
        if (*list == NULL)
        {
            *list = pNew;
            (*list)->nxt = *list;
        }
        else
        {
            pCur = *list;
            while (pCur->nxt != *list)
            {
                pCur = pCur->nxt;
            }
            pNew->nxt = *list;
            pCur->nxt = pNew;
            *list = pNew;
        }
    }
    else
    {
        printf("Alokasi memori gagal");
        getch();
    }
}
//=================================================
void tambahData(node **list)
{
    int pos, num;
    node *pNew, *pCur;

    system("cls");
    tampilData(*list);
    printf("\nPosisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    if (*list == NULL)
    {
        printf("List kosong. Tidak bisa menyisipkan.\n");
        getch();
        return;
    }

    pCur = *list;
    while (pCur->data != pos && pCur->nxt != *list)
    {
        pCur = pCur->nxt;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur->data != pos)
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
        pNew->nxt = pCur->nxt;
        pCur->nxt = pNew;
    }
}
//==================================
void tambahAkhir(node **list)
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
    if (*list == NULL)
    {
        *list = pNew;
        (*list)->nxt = *list;
    }
    else
    {
        pCur = *list;
        while (pCur->nxt != *list)
        {
            pCur = pCur->nxt;
        }
        pCur->nxt = pNew;
        pNew->nxt = *list;
    }
}
//=====================================
void delData(node **list)
{
    int ch;

    system("cls");
    tampilData(*list);
    printf("\nPilih opsi hapus :\n");
    printf("1. Hapus data di awal\n");
    printf("2. Hapus data di tengah\n");
    printf("3. Hapus data di akhir\n");
    printf("Masukkan pilihan : ");
    fflush(stdin);
    scanf("%d", &ch);

    if(ch == 1) {
        delAwal(list);
        return;
    }
    else if (ch == 2) {
        delTengah(list);
        return;
    }
    else if (ch == 3) {
        delAkhir(list);
        return;
    }
    else {
        printf("Input salah!");
        return;
    }
}
//====================================================
void delAwal(node **list)
{
    if (*list == NULL)
    {
        printf("List kosong\n");
        return;
    }

    node *temp = *list, *pCur = *list;

    while (pCur->nxt != *list)
    {
        pCur = pCur->nxt;
    }

    if (*list == pCur)
    {
        free(*list);
        *list = NULL;
    }
    else
    {
        *list = (*list)->nxt;
        pCur->nxt = *list;
        free(temp);
    }
    printf("Node di awal berhasil dihapus.\n");
}
//===================================================
void delTengah(node **list)
{
    if (*list == NULL)
    {
        printf("List kosong\n");
        return;
    }

    tampilData(*list);

    int data;
    printf("\nMasukkan nilai data yang ingin dihapus : ");
    fflush(stdin);
    scanf("%d", &data);

    node *pCur = *list, *pPre = NULL;

    do
    {
        if (pCur->data == data)
        {
            break;
        }
        pPre = pCur;
        pCur = pCur->nxt;
    } while (pCur != *list);

    if (pCur->data != data)
    {
        printf("Data %d tidak ditemukan\n", data);
        return;
    }

    if (pPre == NULL)
    {
        delAwal(list);
    }
    else
    {
        pPre->nxt = pCur->nxt;
        free(pCur);
        printf("Node dengan data %d berhasil dihapus.\n", data);
    }
}
//=================================================
void delAkhir(node **list)
{
    if (*list == NULL)
    {
        printf("List kosong\n");
        return;
    }

    node *pCur = *list, *pPre = NULL;

    while (pCur->nxt != *list)
    {
        pPre = pCur;
        pCur = pCur->nxt;
    }

    if (pCur == *list)
    {
        free(pCur);
        *list = NULL;
    }
    else
    {
        pPre->nxt = *list;
        free(pCur);
    }
    printf("Node di akhir berhasil dihapus.\n");
}
//===================================================
node *srcData(node *list, int num)
{
    node *pCur = list;
    if (list == NULL) return NULL;

    do
    {
        if (pCur->data == num)
        {
            return pCur;
        }
        pCur = pCur->nxt;
    } while (pCur != list);

    return NULL;
}
//==================================================
void tampilData(node *list)
{
    if (list == NULL)
    {
        printf("Linked list kosong\n");
        return;
    }

    node *pWalker = list;

    system("cls");
    printf("Data dalam circular linked list :\n");

    do
    {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->nxt;
    } while (pWalker != list);
    printf("BACKTOHEAD\n");
}
//============================================================
int countData(node *list)
{
    if (list == NULL) return 0;

    int cnt = 0;
    node *pWalker = list;

    do
    {
        cnt++;
        pWalker = pWalker->nxt;
    } while (pWalker != list);

    return cnt;
}

//================================================s
int sumData(node *list)
{
    if (list == NULL) return 0;

    int sum = 0;
    node *pWalker = list;

    do
    {
        sum += pWalker->data;
        pWalker = pWalker->nxt;
    } while (pWalker != list);

    return sum;
}
