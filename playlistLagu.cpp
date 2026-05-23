#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Lagu {
    char judul[100];
    char artis[100];
    char genre[50];
    int tahun;
    float rating;
    Lagu* kanan;
    Lagu* kiri;
};

Lagu* akar = NULL;
Lagu* ekor = NULL;
int totalLagu = 0;

//FUNGSI BUAT NODE
Lagu* buatNode(char judul[], char artis[], char genre[], int tahun, float rating) {
    Lagu* baru = new Lagu();
    strcpy(baru->judul, judul);
    strcpy(baru->artis, artis);
    strcpy(baru->genre, genre);
    baru->tahun = tahun;
    baru->rating = rating;
    baru->kanan = NULL;
    baru->kiri  = NULL;
    return baru;
}

//SIMPAN KE FILE
void simpanKeFile(char namaFile[]) {
    FILE* fptr = fopen(namaFile, "w");
    if (fptr == NULL) {
        cout << "File tidak bisa dibuka!" << endl;
        return;
    }

    Lagu* current = akar;

    while (current != NULL) {
        fprintf(fptr, "%s|%s|%s|%d|%.2f\n",
            current->judul, current->artis, current->genre,
            current->tahun, current->rating);
        current = current->kanan;
    }

    fclose(fptr);
}

//MUAT DARI FILE
void dariFile(char namaFile[]) {
    FILE* fptr = fopen(namaFile, "r");
    if (fptr == NULL) return;

    // Hapus linked list lama
    while (akar != NULL) {
        Lagu* temp = akar;
        akar = akar->kanan;
        delete temp;
    }

    akar = ekor = NULL;
    totalLagu = 0;

    char judul[100], artis[100], genre[50];
    int tahun;
    float rating;

    while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%d|%f\n", judul, artis, genre, &tahun, &rating) == 5) {

        Lagu* baru = buatNode(judul, artis, genre, tahun, rating);

        if (akar == NULL) {
            akar = ekor = baru;
        } else {
            ekor->kanan = baru;
            baru->kiri  = ekor;
            ekor = baru;
        }
        totalLagu++;
    }
    fclose(fptr);
}

//TAMBAH LAGU
void tambahLagu(){
    system ("cls");
    char namaFile[30];
    int jumlah;

    cout << "           TAMBAH LAGU" << endl;
    cout << "======================================" << endl;
    cout << "Disimpan di file: "; cin >> namaFile;
    cout << "Jumlah lagu: "; cin >> jumlah;
    dariFile(namaFile);

    for (int i = 0; i < jumlah; i++) {
        char judul[100], artis[100], genre[50];
        int tahun;
        float rating;

        cout << "\nData ke-" << i + 1 << endl; cin.ignore();
        cout << "Judul Lagu : "; cin.getline(judul, 100);
        cout << "Artis      : "; cin.getline(artis, 100);
        cout << "Genre      : "; cin.getline(genre, 50);
        cout << "Tahun Rilis: "; cin >> tahun;
        cout << "Rating     : "; cin >> rating;

        Lagu* baru = buatNode(judul, artis, genre, tahun, rating);

        if (akar == NULL) {
            akar = ekor = baru;
        } else {
            ekor->kanan = baru;
            baru->kiri  = ekor;
            ekor = baru;
        }
        totalLagu++;
    }
    simpanKeFile(namaFile);
    cout << "======================================" << endl;
    cout << "Data berhasil disimpan!\n" << endl;
}

//TAMPIL PLAYLIST
void tampilPlaylist(){
    system ("cls");
    char namaFile[30];

    cout << "         TAMPILKAN PLAYLIST" << endl;
    cout << "======================================" << endl;
    cout << "Data yang akan ditampilkan dari file: ";
    cin >> namaFile;

    dariFile(namaFile);

    if (akar == NULL){
        cout << "Playlist kosong.\n" << endl;
        return;
    }

    Lagu* current = akar;
    int nomor = 1;

    while (current != NULL) {
        cout << "\nData ke-" << nomor++ << endl;
        cout << "======================================" << endl;
        cout << "Judul Lagu : " << current->judul  << endl;
        cout << "Artis      : " << current->artis  << endl;
        cout << "Genre      : " << current->genre  << endl;
        cout << "Tahun Rilis: " << current->tahun  << endl;
        cout << "Rating     : " << current->rating << endl;
        cout << "======================================" << endl;
        current = current->kanan;
    }
    cout << "Total Lagu: " << totalLagu << endl;
}

//CARI LAGU
void cariLagu(){
    system ("cls");
    char cari[100];
    char namaFile[30];

    cout << "            CARI LAGU" << endl;
    cout << "======================================" << endl;
    cout << "Data yang akan dicari dari file: "; cin >> namaFile;

    dariFile(namaFile);
    cin.ignore();

    cout << "Judul lagu yang dicari: "; cin.getline(cari, 100);

    Lagu* current = akar;
    bool ketemu = false;

    while (current != NULL) {
        if (strcmp(current->judul, cari) == 0) {
            cout << "\nData ditemukan!" << endl;
            cout << "======================================" << endl;
            cout << "Judul Lagu : " << current->judul  << endl;
            cout << "Artis      : " << current->artis  << endl;
            cout << "Genre      : " << current->genre  << endl;
            cout << "Tahun Rilis: " << current->tahun  << endl;
            cout << "Rating     : " << current->rating << endl;
            cout << "======================================" << endl;
            ketemu = true;
            break;
        }
        current = current->kanan;
    }
    if (!ketemu) {
        cout << "Data tidak ditemukan.\n" << endl;
    }
}

void urutLagu(){
    system("cls");
    char namaFile[30];

    cout << "          URUTKAN LAGU" << endl;
    cout << "======================================" << endl;
    cout << "Data yang akan diurutkan dari file: "; 
    cin >> namaFile;

    dariFile(namaFile);

    if (akar == NULL) {
        cout << "Playlist kosong!\n" << endl;
        return;
    }

    Lagu* arr[100];
    int count = 0;

    Lagu* current = akar;

    while (current != NULL) {
        arr[count++] = current;
        current = current->kanan;
    }

    int pilih;

    cout << "\n1. Judul (A -> Z)" << endl;
    cout << "2. Rating (Tertinggi -> Terendah)" << endl;
    cout << "Pilih: "; cin >> pilih;

    if (pilih == 1) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (strcmp(arr[j]->judul, arr[j + 1]->judul) > 0) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        cout << "\nData diurutkan: Judul A -> Z" << endl;

    } else if (pilih == 2) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (arr[j]->rating < arr[j + 1]->rating) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        cout << "\nData diurutkan: Rating Tertinggi -> Terendah" << endl;

    } else {
        cout << "Pilihan tidak valid!\n" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        arr[i]->kanan = (i + 1 < count) ? arr[i + 1] : NULL;
        arr[i]->kiri  = (i - 1 >= 0) ? arr[i - 1] : NULL;
    }

    akar = arr[0];
    ekor = arr[count - 1];
    ekor->kanan = NULL;

    for (int i = 0; i < count; i++) {
        cout << "\nData ke-" << i + 1 << endl;
        cout << "======================================" << endl;
        cout << "Judul Lagu : " << arr[i]->judul  << endl;
        cout << "Artis      : " << arr[i]->artis  << endl;
        cout << "Genre      : " << arr[i]->genre  << endl;
        cout << "Tahun Rilis: " << arr[i]->tahun  << endl;
        cout << "Rating     : " << arr[i]->rating << endl;
        cout << "======================================" << endl;
    }

    simpanKeFile(namaFile);

    cout << "Data berhasil disimpan ke file." << endl;
}

//UPDATE LAGU
void updateLagu(){
    system ("cls");
    char cari[100];
    char namaFile[30];

    cout << "       UPDATE RATING LAGU" << endl;
    cout << "======================================" << endl;
    cout << "Data yang akan dicari dari file: "; cin >> namaFile;

    dariFile(namaFile);

    cin.ignore();

    cout << "Masukkan judul lagu: "; cin.getline(cari, 100);

    Lagu* current = akar;
    bool ketemu = false;

    while (current != NULL) {
        if (strcmp(current->judul, cari) == 0) {
            cout << "\nData ditemukan:" << endl;
            cout << "Judul  : " << current->judul  << endl;
            cout << "Rating : " << current->rating << endl;
            cout << "\nMasukkan rating baru: ";
            cin >> current->rating;
            ketemu = true;
            break;
        }
        current = current->kanan;
    }

    if (!ketemu) {
        cout << "======================================" << endl;
        cout << "Data tidak ditemukan.\n" << endl;
        return;
    }
    simpanKeFile(namaFile);
    cout << "Rating berhasil diupdate!" << endl;
    cout << "======================================" << endl;

}

//HAPUS LAGU
void hapusLagu(){
    system("cls");
    char namaFile[30];
    char cari[100];

    cout << "            HAPUS LAGU" << endl;
    cout << "======================================" << endl;
    cout << "Data yang akan dihapus dari file: "; cin >> namaFile;

    dariFile(namaFile);

    if (akar == NULL) {
        cout << "Playlist kosong!\n" << endl;
        return;
    }

    cin.ignore();

    cout << "Judul lagu yang ingin dihapus: ";
    cin.getline(cari, 100);

    Lagu* current = akar;
    bool ketemu = false;

    while (current != NULL) {
        if (strcmp(current->judul, cari) == 0) {
            cout << "\nData ditemukan!" << endl;
            cout << "======================================" << endl;
            cout << "Judul Lagu : " << current->judul  << endl;
            cout << "Artis      : " << current->artis  << endl;
            cout << "Genre      : " << current->genre  << endl;
            cout << "Tahun Rilis: " << current->tahun  << endl;
            cout << "Rating     : " << current->rating << endl;
            cout << "======================================" << endl;

            if (current->kiri != NULL) {
                current->kiri->kanan = current->kanan;
            } else {
                akar = current->kanan;
            }

            if (current->kanan != NULL) {
                current->kanan->kiri = current->kiri;
            } else {
                ekor = current->kiri;
            }

            delete current;
            totalLagu--;

            simpanKeFile(namaFile);

            cout << "Lagu berhasil dihapus!" << endl;
            ketemu = true;
            break;
        }
        current = current->kanan;
    }
    if (!ketemu) {
        cout << "======================================" << endl;
        cout << "Data tidak ditemukan.\n" << endl;
    }
}

int main() {
    system ("cls");
	int pilih;
    char lagi;
	
	do {
        cout << "               MENU" << endl;
        cout << "======================================" << endl;
        cout << "1. TAMBAH LAGU" << endl;
        cout << "2. TAMPILKAN PLAYLIST" << endl;
        cout << "3. CARI LAGU" << endl;
        cout << "4. URUTKAN LAGU" << endl;
        cout << "5. UPDATE LAGU" << endl;
        cout << "6. HAPUS LAGU" << endl;
        cout << "7. EXIT" << endl;
        cout << "======================================" << endl;
        cout << "Pilih: "; cin >> pilih;
        cout << endl;
	
        switch (pilih) {
            case 1: 
                tambahLagu();
                break;
            case 2:
                tampilPlaylist();
                break;
            case 3:
                cariLagu();
                break;
            case 4:
                urutLagu();
                break;
            case 5:
                updateLagu();
                break;
            case 6:
                hapusLagu();
                break;
            case 7:
                cout << "======================================" << endl;
                cout << "    Terima kasih telah menggunakan \n  Sistem Manajemen Playlist Musik" << endl;
                cout << "======================================" << endl;
                return 0;
            default:
                cout << "Pilihan menu tidak ada." << endl;
        }

        cout << "Kembali ke Menu Utama (y/t)? "; cin >> lagi;
        cin.ignore(); 
        system ("cls");

    } while (lagi == 'y' || lagi == 'Y');
	
	return 0;
}

