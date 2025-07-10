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
            printf("Masukkan data yang dicari : ");
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
    node *pNew;

    system("cls");
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = num;
        pNew->nxt = pNew;
        *list = pNew;
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
    node *pNew, *pPre;

    system("cls");
    tampilData(*list);
    printf("\nPosisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan : ");
    fflush(stdin);
    scanf("%d", &num);

    pPre = *list;
    while (pPre != NULL && pPre->data != pos)
    {
        pPre = pPre->nxt;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pPre == NULL)
    {
        pNew->nxt = pNew;
        *list = pNew;
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
        pNew->nxt = pPre->nxt;
        pPre->nxt = pNew;
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
    pNew->nxt = NULL;

    if (*list == NULL)
    {
        *list = pNew;
    }
    else
    {
        pCur = *list;
        while (pCur->nxt != NULL)
        {
            pCur = pCur->nxt;
        }
        pCur->nxt = pNew;
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

    if (ch == 1) {
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
    node *temp = *list;
    *list = (*list)->nxt;
    free(temp);
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

    node *pCur = *list, *pPrev = NULL;

    while (pCur != NULL && pCur->data != data)
    {
        pPrev = pCur;
        pCur = pCur->nxt;
    }

    if (pCur == NULL)
    {
        printf("Data %d tidak ditemukan\n", data);
        return;
    }

    if (pPrev == NULL)
    {
        *list = pCur->nxt;
    }
    else
    {
        pPrev->nxt = pCur->nxt;
    }
    free(pCur);
    printf("Node dengan data %d berhasil dihapus.\n", data);
}
//=================================================
void delAkhir(node **list)
{
    if (*list == NULL)
    {
        printf("List kosong\n");
        return;
    }

    node *pCur = *list, *pPrev = NULL;

    if (pCur->nxt == NULL)
    {
        free(pCur);
        *list = NULL;
        printf("Node di akhir berhasil dihapus.\n");
        return;
    }

    while (pCur->nxt != NULL)
    {
        pPrev = pCur;
        pCur = pCur->nxt;
    }

    pPrev->nxt = NULL;
    free(pCur);
    printf("Node di akhir berhasil dihapus.\n");
}
//===================================================
node *srcData(node *list, int num)
{
    node *pCur = list;
    while (pCur != NULL)
    {
        if (pCur->data == num)
        {
            return pCur;
        }
        pCur = pCur->nxt;
    }
    return NULL;
}
//==================================================
void tampilData(node *list)
{
    node *pWalker = list;

    system("cls");
    printf("Data dalam linked list :\n");
    if (pWalker == NULL)
    {
        printf("Linked list kosong\n");
    }
    else
    {
        while (pWalker != NULL)
        {
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->nxt;
        }
        printf("NULL\n");
    }
}
//============================================================
int countData(node *list)
{
	system("cls");
    tampilData(list);
    int cnt = 0;
    node *pWalker = list;

    while (pWalker != NULL)
    {
        cnt++;
        pWalker = pWalker->nxt;
    }

    return cnt;
}

//================================================s
int sumData(node *list)
{
	system("cls");
    tampilData(list);
    int sum = 0;
    node *pWalker = list;

    while (pWalker != NULL)
    {
        sum += pWalker->data;
        pWalker = pWalker->nxt;
    }

    return sum;
}
