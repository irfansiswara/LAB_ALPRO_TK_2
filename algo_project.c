/*
LAB Project Team
COMP6112036 - AYCA - LAB
Group-4:
1. 2902814942 - Alfira Putri Nurlita
2. 2902804014 - Christian Hotasi Viccare Hutagaol
3. 2902816336 - Christoffer Yoel Evandri Viebrian
4. 2902813126 - Irfan Siswara
5. 2902827232 - Muh Faisal Bimantara
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char kode[10];
    char nama[100];
    char jenis[100];
    double harga;
} Book;

typedef struct
{
    char kodeBuku[10];
    int jumlahTerjual;
    double totalHarga;
} History;

Book books[100];
History histories[100];

int totalBook = 0;
int totalHistory = 0;

//read file databuku.txt
void loadBook() {
    FILE *fp = fopen("databuku.txt", "r");

    if (fp == NULL) {
        return;
    }

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%lf\n",
        books[totalBook].kode,
        books[totalBook].nama,
        books[totalBook].jenis,
        &books[totalBook].harga) != EOF
    ) {
        totalBook++;
    }

    fclose(fp);
}

void generateBookCode(char code[]) {
    sprintf(code, "BK%03d", totalBook + 1);
}

// Function untuk menambahkan data buku baru
void inputBook() {
    int validation_harga;

    printf("\nInput Data Buku\n");

    //Kode buku
    generateBookCode(books[totalBook].kode);
    printf("Kode Buku : %s\n", books[totalBook].kode);

    //Nama buku
    do {
        printf("Nama Buku : ");
        scanf(" %[^\n]", books[totalBook].nama);
        if (strlen(books[totalBook].nama) == 0) {
            printf("Nama buku tidak boleh kosong!\n");
        }
    } while (strlen(books[totalBook].nama) == 0);

    //Jenis buku
    do {
        printf("Jenis Buku : ");
        scanf(" %[^\n]", books[totalBook].jenis);
        if (strlen(books[totalBook].jenis) == 0) {
            printf("Jenis buku tidak boleh kosong!\n");
        }
    } while (strlen(books[totalBook].nama) == 0);

    //Harga buku
    do {
        printf("Harga Buku : ");
        validation_harga = scanf("%lf", &books[totalBook].harga);
        while (getchar() != '\n');
        if (validation_harga != 1) {
            printf("Harga harus angka!\n");
        }
        else if (books[totalBook].harga <= 0) {
            printf("Harga harus lebih dari 0!\n");
            validation_harga = 0;
        }
    } while (validation_harga != 1);

    totalBook++;
    printf("\nData buku berhasil ditambahkan!\n");
}

void viewHistory() {
    if (totalHistory == 0){
        printf("\nTidak ada data penjualan!\n");
        return;
    }

    printf("\n--- Daftar Riwayat Penjualan ---\n");
    for (int i = 0; i < totalHistory; i++){
        printf("%d. %s | %d | %.2lf\n",
        i + 1,
        histories[i].kodeBuku,
        histories[i].jumlahTerjual,
        histories[i].totalHarga);
    }
}

// Function untuk menampilkan seluruh data buku
void viewBook() {
    if (totalBook == 0) {
        printf("\nTidak ada data buku!\n");
        return;
    }

    for (int i = 0; i < totalBook; i++) {
        printf("%d. %s | %s | %s | %.2lf\n",
            i + 1,
            books[i].kode,
            books[i].nama,
            books[i].jenis,
            books[i].harga);
    }
}

//Function untuk menghapus seluruh data history transaksi
void deleteHistory() {
    if (totalHistory == 0) {
        printf("\nTidak ada data transaksi!\n");
        return;
    }

    int index;
    int validation;

    printf("\nList History Transaksi\n");

    for(int i = 0; i < totalHistory; i++) {
        printf("%d. %s | Jumlah: %d | Total: %.2lf\n",
            i + 1,
            histories[i].kodeBuku,
            histories[i].jumlahTerjual,
            histories[i].totalHarga);
    }

    do {
        printf("\nPilih index yang ingin dihapus [1-%d]: ", totalHistory);
        validation = scanf("%d", &index);
        while (getchar() != '\n');
        if (validation != 1) {
            printf("Input harus angka!\n");
            while (getchar() != '\n');
            index = 0;
        } else if (index < 1 || index > totalHistory) {
            printf("Index tidak valid!\n");
        }
    } while (index < 1 || index > totalHistory);

    //geser data history setelah index yang dihapus
    for (int i = index - 1; i < totalHistory - 1; i++) {
        histories[i] = histories[i + 1];
    }
    totalHistory--;
    printf("\nData Successfully Deleted!\n");
}

//Function untuk menghapus seluruh data buku
void deleteBook() {
    if (totalBook == 0) {
        printf("\nTidak ada data buku!\n");
        return;
    }
    
    int index;
    int validation;

    printf("\nList Data Buku\n");

    for(int i = 0; i < totalBook; i++) {
        printf("%d. %s | %s | %s | %.2lf\n",
            i + 1,
            books[i].kode,
            books[i].nama,
            books[i].jenis,
            books[i].harga);
    }

    do {
        printf("\nPilih index yang ingin dihapus [1-%d]: ", totalBook);
        validation = scanf("%d", &index);
        while (getchar() != '\n');
        if (validation != 1) {
            printf("Input harus angka!\n");
            while (getchar() != '\n');
            index = 0;
        } else if (index < 1 || index > totalBook) {
            printf("Index tidak valid!\n");
        }
    } while (index < 1 || index > totalBook);

    //geser data buku setelah index yang dihapus
    for (int i = index - 1; i < totalBook - 1; i++) {
        books[i] = books[i + 1];
    }
    totalBook--;
    printf("\nData Successfully Deleted!\n");

}

void saveBookAndHistory() {
    FILE *fpBook = fopen("databuku.txt", "w");

    if (fpBook == NULL){
        printf("[Error] Gagal membuka databuku.txt!\n");
    }
    else{
        for (int i = 0; i < totalBook; i++){
            fprintf(fpBook, "%s|%s|%s|%.2lf\n",
                    books[i].kode,
                    books[i].nama,
                    books[i].jenis,
                    books[i].harga);
        }
        fclose(fpBook);
        printf("[Sukses] Data buku berhasil tersimpan.\n");
    }

    FILE *fpHistory = fopen("datahistoris.txt", "w");

    if (fpHistory == NULL){
        printf("[Error] Gagal membuka datatransaksi.txt!\n");
    }
    else
    {
        for (int i = 0; i < totalHistory; i++){
            fprintf(fpHistory, "%s|%d|%.2lf\n",
                    histories[i].kodeBuku,
                    histories[i].jumlahTerjual,
                    histories[i].totalHarga);
        }
        fclose(fpHistory);
        printf("[Sukses] Data transaksi berhasil tersimpan.\n");
    }

    if (fpBook == NULL || fpHistory == NULL){
        printf("\nTekan ENTER untuk melanjutkan proses keluar sistem tanpa menyimpan data yang gagal...");
        getchar();
    }
}

//function untuk melakukan input transaksi
void inputTransaction() {

    if (totalBook == 0) {
        printf("\nTidak ada data buku!\n");
        return;
    }

    char inputKode[10];
    int jumlah;
    int validation;
    int foundIndex = -1;

    printf("\n--- Input Transaksi Penjualan ---\n");

    // menampilkann daftar buku untuk dipilih
    printf("\nDaftar Buku:\n");
    for (int i = 0; i < totalBook; i++) {
        printf("%d. %s | %s | %.2lf\n",
            i + 1,
            books[i].kode,
            books[i].nama,
            books[i].harga);
    }

    // input kode buku
    do {
        printf("\nMasukkan kode buku: ");
        scanf("%9s", inputKode);
        while (getchar() != '\n');

        foundIndex = -1;

        // cari kode buku
        for (int i = 0; i < totalBook; i++) {
            if (strcmp(books[i].kode, inputKode) == 0) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1) {
            printf("Kode buku tidak ditemukan!\n");
        }

    } while (foundIndex == -1);

    // input jumlah terjual
    do {
        printf("Jumlah terjual: ");
        validation = scanf("%d", &jumlah);
        while (getchar() != '\n');

        if (validation != 1) {
            printf("Input harus angka!\n");
        }
        else if (jumlah <= 0) {
            printf("Jumlah harus lebih dari 0!\n");
            validation = 0;
        }

    } while (validation != 1);

    // simpan ke histori
    strcpy(histories[totalHistory].kodeBuku,
           books[foundIndex].kode);

    histories[totalHistory].jumlahTerjual = jumlah;

    histories[totalHistory].totalHarga =
        jumlah * books[foundIndex].harga;

    totalHistory++;

    printf("\nTransaksi berhasil disimpan.\n");
}

void sortByName() {
    if (totalBook == 0) {
        printf("\nTidak ada data buku untuk diurutkan.\n");
        return;
    }

    for (int i = 0; i < totalBook - 1; i++) {
        for (int j = 0; j < totalBook - i - 1; j++) {
            if (strcmp(books[j].nama, books[j + 1].nama) > 0) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    printf("\nData buku berhasil diurutkan berdasarkan nama (A-Z):\n");
    viewBook();
}

void sortByPrice() {
    if (totalBook == 0) {
        printf("\nTidak ada data buku untuk diurutkan.\n");
        return;
    }

    for (int i = 0; i < totalBook - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < totalBook; j++) {
            if (books[j].harga > books[maxIdx].harga) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Book temp = books[i];
            books[i] = books[maxIdx];
            books[maxIdx] = temp;
        }
    }

    printf("\nData buku berhasil diurutkan berdasarkan harga (Tertinggi ke Terendah):\n");
    viewBook();
}

void sortBookMenu() {
    int choice;
    do {
        printf("\n--- Menu Sort Buku ---\n");
        printf("1. Urutkan berdasarkan nama buku (A-Z)\n");
        printf("2. Urutkan berdasarkan harga buku (Tertinggi ke Terendah)\n");
        printf("3. Kembali ke menu utama\n");
        printf("Pilih opsi [1-3]: ");
        int validation = scanf("%d", &choice);
        while (getchar() != '\n');

        if (validation != 1 || choice < 1 || choice > 3) {
            printf("Input tidak valid!\n");
            choice = 0;
        } else {
            switch (choice) {
                case 1:
                    sortByName();
                    break;
                case 2:
                    sortByPrice();
                    break;
                case 3:
                    return;
            }
        }

        printf("\nTekan Enter untuk kembali ke menu Sort Buku...");
        getchar();

    } while (choice != 3);
}

int main(void)
{
    int select_menu;
    int menu_validation;

    //get book and history data
    loadBook();

    while (1)
    {
        // clear terminal
        system("cls");

        puts("Toko Buku Literasi Nusantara Jaya");
        puts("1. Input Data Buku Baru");
        puts("2. View History Transaksi Penjualan");
        puts("3. View Buku");
        puts("4. Delete History");
        puts("5. Delete Buku");
        puts("6. Exit");
        puts("7. Input Transaksi Penjualan");
        puts("8. Sort Buku (berdasarkan nama dan harga)");

        do
        {
            printf("\nPilih Menu [1-8]: ");
            menu_validation = scanf("%d", &select_menu);
            while (getchar() != '\n');

            if (menu_validation != 1) {
                printf("Input harus angka!\n");
                while (getchar() != '\n');
                select_menu = 0;
            }else if (select_menu < 1 || select_menu > 8) {
                printf("Menu tidak tersedia!\n");
            }
        }while(select_menu < 1 || select_menu > 8);

        switch (select_menu) {
            case 1:
                inputBook();
                break;
            case 2:
                viewHistory();
                break;
            case 3:
                viewBook();
                break;
            case 4:
                deleteHistory();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                saveBookAndHistory();
                return 0;
            case 7:
                inputTransaction();
                break;
            case 8:
                sortBookMenu();
            break;
        }

        printf("\nTekan Enter untuk kembali ke menu awal");
        getchar();
        printf("\n");
    }

    return 0;
}
