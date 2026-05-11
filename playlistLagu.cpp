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
    system ("cls");
    FILE *fptr;
    char namaFile[30];

    cout << "TAMPILKAN PLAYLIST" << endl;
    cout << "===============================" << endl;
    cout << "Data yang akan ditampilkan dari file: ";
    cin >> namaFile;

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

    while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%d|%f\n", 
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
    system("cls");
    FILE *fptr;
    char namaFile[30];

    cout << "URUTKAN LAGU" << endl;
    cout << "===============================" << endl;
    cout << "Data yang akan diurutkan dari file: "; 
    cin >> namaFile;

    fptr = fopen(namaFile, "r");
    if (fptr == NULL) {
        cout << "File tidak bisa ditemukan!" << endl;
        return;
    }
    
    n = 0;
 
    while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%d|%f\n",
        data[n].judul, data[n].artis, data[n].genre, &data[n].tahun, &data[n].rating) != EOF) {
        n++;
    }
    fclose(fptr);

    if (n == 0) {
        cout << "Playlist kosong!" << endl;
        return;
    }

    int pilih;
    cout << "\n1. Judul (A -> Z)" << endl;
    cout << "2. Rating (Tertinggi -> Terendah)" << endl;
    cout << "Pilih: "; 
    cin >> pilih;

    if (pilih == 1) {
        for (int i = 0; i < n - 1; i++;) {
            for (int j = 0; j < n - i - 1; j++) {
                if (strcmp(data[j].judul, data[j+1].judul) > 0) {
                    Lagu temp = data [j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
        }
        cout << "\nData diurutkan: Judul A -> Z" << endl;
    } else if (pilih == 2){
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++){
                if (data[j] = 0; j < n - i - 1; j++){
                    if (data[j].rating < data[j+1].rating){
                        Lagu temp = data[j];
                        data[j] = data[j+1];
                        data[j+1] = temp;
                    }
                }
            }
            cout << "Data diurutkan: Rating Tertinggi -> Terendah " << endl;
        } else {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }

    for (int i = 0; i < n; i++) {
        cout << "\nData ke-" << i + 1 << endl;
        cout << "===============================" << endl;
        cout << "Judul Lagu : " << data[i].judul << endl;
        cout << "Artis      : " << data[i].artis << endl;
        cout << "Genre      : " << data[i].genre << endl;
        cout << "Tahun Rilis: " << data[i].tahun << endl;
        cout << "Rating     : " << data[i].rating << endl;
        cout << "===============================" << endl;
    }

    fptr = fopen(namaFile, "w");
    for (int i = 0; i < n; i++) {
        fprintf(fptr, "%s|%s|%s|%d|%.2f\n",
            data[i].judul, data[i].artis, data[i].genre, data[i].tahun, data[i].rating);
    }
    fclose(fptr);
    cout << "Data berhasil disimpan ke file." << endl;
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
    system("cls");
    FILE *fptr;
    char namaFile[30];
    char cari[100];
    bool ketemu = false;

    cout << "HAPUS LAGU" << endl;
    cout << "===============================" << endl; 
    cout << "Data yang akan dihapus dari file: ";
    cin >> namaFile;

    fptr = fopen(namaFile, "r");

    if (fptr == NULL) {
        cout << "File tidak ditemukan!" << endl;
    }

    n = 0;
    while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%d|%f\n",
        data[n].judul, data[n].artis, data[n].genre, &data[n].tahun, &data[n].rating) != EOF) {
        n++;
        }
        fclose(fptr);

        if (n == 0) {
            cout << "Playlist kosong!" << endl;
            return;
        }

        cin.ignore();
        cout << "Judul lagu yang ingin dihapus: "; cin.getline(cari, 100);

    for (int i = 0; i < n; i++) {
         if (strcmp(data[i].judul, cari) == 0) {
        cout << "\nData ditemukan" << endl;
        cout << "===============================" << endl;
        cout << "Judul Lagu : " << data[i].judul << endl;
        cout << "Artis      : " << data[i].artis << endl;
        cout << "Genre      : " << data[i].genre << endl;
        cout << "Tahun Rilis: " << data[i].tahun << endl;
        cout << "Rating     : " << data[i].rating << endl;
        cout << "===============================" << endl;

        for (int j = i; j < n - 1; j++) {
                data[j] = data[j+1];
            }
            n--;
            
            fptr = fopen(namaFile, "w");
            for (int j = 0; j < n; j++) {
                fprintf(fptr, "%s|%s|%s|%d|%.2f\n",
                    data[j].judul, data[j].artis, data[j].genre, data[j].tahun, data[j].rating);
            }
            fclose(fptr);
            cout << "Lagu berhasil dihapus!" << endl;

            ketemu = true;
            break;
        }
    }
    if (ketemu){
    } else {
		cout << "===============================" << endl;
        cout << "Data tidak ditemukan" << endl;
    }
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

