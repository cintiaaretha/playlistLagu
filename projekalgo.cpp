#include <iostream>
using namespace std;

struct lagu{
    char judul[100];
    char artis[100];
    char genre[50];
    int tahun;
    float rating;
};

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
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nData ke-" << i + 1 << endl;
        cout << "Judul Lagu : "; getline(cin, lagu[i].judul);
        cout << "Artis      : "; getline(cin, lagu[i].artis);
        cout << "Genre      : "; getline(cin, lagu[i].genre);
        cout << "Tahun Rilis: "; cin >> lagu[i].tahun;
        cout << "Rating     : "; cin >> lagu[i].rating;

        fprintf(fptr, "%s %s %s %d %f\n", 
            lagu[i].judul, lagu[i].artis, lagu[i].genre, lagu[i].tahun, lagu[i].rating
        );
    }
    fclose(fptr);
    cout << "===============================" << endl;
}

void tampilPlaylist(){
}

void cariLagu(){
    char ulang; 

    do {
        system ("cls");
        FILE *fptr;
        int cari;
        bool ketemu = false;
        char namaFile[30];

        cout << "SEQUENSIAL SEARCH" << endl;
        cout << "===============================" << endl;
        cout << "\nData yang akan dicari dari file: "; cin >> namaFile;

        fptr = fopen(namaFile, "r");

        if (fptr == NULL) {
            cout << "File tidak ditemukan";
            return;
        }

        n = 0;

        while (fscanf(fptr, "%s %s %s %d %f",
                lagu[n].judul, lagu[n].artis, lagu[n].genre, &lagu[n].tahun, &lagu[n].rating)!=EOF) {
                n++;
        }

        fclose(fptr);

        cout << "\nJudul Lagu yang dicari: ";  cin >> cari;

        for (int i = 0; i < n; i++) {
            if (lagu[i].judul==cari) {
                cout << "\nData ditemukan" << endl;
                cout << "===============================" << endl;
                cout << "Judul Lagu : " << lagu[i].judul;
                cout << "Artis      : " << lagu[i].artis;
                cout << "Genre      : " << lagu[i].genre;
                cout << "Tahun Rilis: " << lagu[i].tahun;
                cout << "Rating     : " << lagu[i].rating;
                cout << "===============================" << endl;

                ketemu = true;
                break;
            }
        }
        if (!ketemu)
            cout << "Data tidak ditemukan..." << endl;

        cout << "\nUlangi (y/t)?"; cin >> ulang;
    
    } while (ulang == 'y' || ulang == 'Y');
}

void urutLagu(){
}

void updateLagu(){
    system ("cls");
    FILE *fptr;
    string cari;

    cout << "UPDATE RATING LAGU" << endl;
    cout << "===============================" << endl;
    cout << "\nData yang akan dicari dari file: "; cin >> namaFile;

    fptr = fopen(namaFile, "r");

    if (fptr == NULL) {
        cout << "File tidak ditemukan";
        return;
    }
    cout << "Masukkan judul buku: "; getline(cin, cari);

    bacaFile();

    int index = sequentialSearch(cari);

	if (index != -1) {
		cout << "\nData Saat Ini:" << endl;
		cout << "Judul: "<< data[index].judul << endl;
        cout << "Stok : "<< data[index].stok << endl;
        cout << "Tahun: "<< data[index].tahun << endl;
		
		cout << "\nMasukkan stok baru: "; cin >> data[index].stok;
    
		simpanFile();
		cout << "Data berhasil disimpan ke file." << endl;
		
		cout << "\nStok berhasil diupdate!" << endl;
		cout << "Stok baru: " << data[index].stok << endl;
	} else {
		cout << "Data tidak ditemukan..." << endl;
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

