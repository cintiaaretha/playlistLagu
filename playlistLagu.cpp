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
};

Lagu data[100];
int n = 0;

void tambahLagu(){
    system ("cls");
    FILE *fptr;
    char namaFile[30];

    cout << "TAMBAH LAGU" << endl;
    cout << "===============================" << endl;
    cout << "Disimpan di file: "; cin >> namaFile;

    fptr = fopen(namaFile, "a");

    if(fptr == NULL) {
        cout << "File tidak bisa dibuka!" << endl;
        return;
    }

    cout << "Jumlah lagu: "; cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nData ke-" << i + 1 << endl;

        cout << "Judul Lagu : "; cin.getline(data[i].judul, 100);
        cout << "Artis      : "; cin.getline(data[i].artis, 100);
        cout << "Genre      : "; cin.getline(data[i].genre, 50);
        cout << "Tahun Rilis: "; cin >> data[i].tahun;
        cout << "Rating     : "; cin >> data[i].rating;

        fprintf(fptr, "%s|%s|%s|%d|%.2f\n", 
            data[i].judul, data[i].artis, data[i].genre, data[i].tahun, data[i].rating
        );
    }
    fclose(fptr);
    cout << "===============================" << endl;
    cout << "Data berhasil disimpan!" << endl;
}

void tampilPlaylist(){
    sytem ("cls");
    FILE *fptr;
    char namaFile[30];

    cout << "TAMPILKAN PLAYLIST" << endl;
    cout << "===============================" << endl;
    cout << "Data yang akan ditampilkan dari file: "; cin >> namaFile;

    fptr = fopen(namaFile, "r");

    if (fptr == NULL){
        cout << "File tidak ditemukan" << endl;
        return;
    }

    n = 0;
    while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%d|%f\n",
        data[n]. judul, data[n].artis, data[n].genre, &data[n].tahun, &data[n].rating) !=EOF) {
        n++;
    } 
    fclose(fptr);
    
    if (n == 0) {
        cout << "Playlist kosong!" << endl;
        return; 
    }

    for (int i = 0; i < n; i++){
        cout << "\nData ke-" << i + 1 << endl;
            cout << "===============================" << endl;
            cout << "Judul Lagu : " << data[i].judul << endl;
            cout << "Artis      : " << data[i].artis << endl;
            cout << "Genre      : " << data[i].genre << endl;
            cout << "Tahun Rilis: " << data[i].tahun << endl;
            cout << "Rating     : " << data[i].rating << endl;
            cout << "===============================" << endl;
    }
    cout << "Total Lagu: " << n << endl;
}

void cariLagu(){
    system ("cls");
    FILE *fptr;
    char cari[100];
    bool ketemu = false;
    char namaFile[30];

    cout << "CARI LAGU" << endl;
    cout << "===============================" << endl;
    cout << "\nData yang akan dicari dari file: "; cin >> namaFile;

    fptr = fopen(namaFile, "r");

    if (fptr == NULL) {
        cout << "File tidak ditemukan";
        return;
    }

    n = 0;

    while (fscanf(fptr, "%[^|]%[^|]%[^|]|%d|%f\n", 
        data[n].judul, data[n].artis, data[n].genre, &data[n].tahun, &data[n].rating)!=EOF) {
        n++;
    }

    fclose(fptr);

    cin.ignore();
    cout << "\nJudul Lagu yang dicari: ";  cin.getline(cari, 100);

    for (int i = 0; i < n; i++) {
        if (strcmp(data[i].judul, cari) == 0) {
            cout << "\nData ditemukan" << endl;
            cout << "===============================" << endl;
            cout << "Judul Lagu : " << data[i].judul;
            cout << "Artis      : " << data[i].artis;
            cout << "Genre      : " << data[i].genre;
            cout << "Tahun Rilis: " << data[i].tahun;
            cout << "Rating     : " << data[i].rating;
            cout << "===============================" << endl;

            ketemu = true;
            break;
        }
    }
    if (!ketemu) {
        cout << "Data tidak ditemukan..." << endl;
    }
    
}

void urutLagu(){
    cout << "aaaa";
}

void updateLagu(){
    system ("cls");
    FILE *fptr;
    char cari[100];
    char namaFile[30];
    bool ketemu = false;

    cout << "UPDATE RATING LAGU" << endl;
    cout << "===============================" << endl;
    cout << "\nData yang akan dicari dari file: "; cin >> namaFile;

    fptr = fopen(namaFile, "r");

    if (fptr == NULL) {
        cout << "File tidak ditemukan";
        return;
    }
}

void hapusLagu(){
}

int main() {
    system ("cls");
	int pilih;
    char lagi;
	
	do {
        cout << "MENU" << endl;
        cout << "===============================" << endl;
        cout << "1. TAMBAH LAGU" << endl;
        cout << "2. TAMPILKAN PLAYLIST" << endl;
        cout << "3. CARI LAGU" << endl;
        cout << "4. URUTKAN LAGU" << endl;
        cout << "5. UPDATE LAGU" << endl;
        cout << "6. HAPUS LAGU" << endl;
        cout << "7. EXIT" << endl;
        cout << "===============================" << endl;
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
                cout << "Pilihan menu tidak ada..." << endl;
        }

        cout << "Kembali ke Menu Utama (y/t)?"; cin >> lagi;
        system ("cls");

    } while (lagi == 'y' || lagi == 'Y');
	
	return 0;
}

