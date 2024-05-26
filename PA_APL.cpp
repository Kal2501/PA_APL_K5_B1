#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct kamera{
    string kamera;
    int harga;
    string sewa;
};
struct user{
    string nama;
    string password;
    int jmlKameraUser = 0;
    kamera kmrUser[1]; //Buat nyimpan kamera yang disewa
};

user usr[100];

user *akun = usr;

kamera kmr[100];
int jmlKamera = 0;
int jmlUser = 0;
int idxUser;

string menuAdmin(){
    return "1. Tambah Kamera\n"
    "2. Lihat Kamera\n"
    "3. Hapus Kamera\n"
    "4. Edit Kamera\n"
    "5. Log out\n";
}
string menuUser(){
	return "1. Lihat Kamera\n"
	"2. Cari Kamera\n"
	"3. Sewa Kamera\n"
	"4. Kembalikan Kamera\n"
	"5. Log out\n";
}

void erorInput(){
    cout << "PILIHAN TIDAK DITEMUKAN!!!"<< endl;
}

void clearScreen(){
    system("cls||clear");
}

void lanjutkan(){
    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore(1000, '\n');
    cin.get();
    clearScreen();
}

//============Bubble Sort================
void swap(kamera &a, kamera &b) {
    kamera temp = a;
    a = b;
    b = temp;
}
void bubbleSort(kamera arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].kamera > arr[j + 1].kamera) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
//++++++++++++++++++++++++++++++++++++++

//============Binary Search=============
int binarySearch(kamera arr[], int l, int r, string x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        // Periksa apakah nama yang dicari ada di tengah
        if (arr[m].kamera == x)
            return m;
        // Jika nama berada di sebelah kiri, cari di sebelah kiri
        if (arr[m].kamera < x)
            l = m + 1;
        // Jika nama berada di sebelah kanan, cari di sebelah kanan
        else
            r = m - 1;
    }
    return -1;
}
//++++++++++++++++++++++++++++++++++++++

//=============File CSV==============
void bacaFileKameraCsv(){
    string kamera, harga, data, sewa;
    int harga_int, idx = 0;
    ifstream file("dataKamera.csv");
    if(file.is_open()){
        while(getline(file,data)){
            stringstream ss(data);
            getline(ss,kamera,',');
            getline(ss,harga,',');
            getline(ss,sewa,'\n');
            stringstream harga_string(harga);
            harga_string >> harga_int;
            kmr[idx].kamera = kamera;
            kmr[idx].harga = harga_int;
            kmr[idx].sewa = sewa;
            idx++;
            jmlKamera = idx;
        }
        file.close();
    }
}

void tambahKameraCsv(string kamera, int harga, string sewa){
    ofstream file("dataKamera.csv",ios::app);
    if (file.is_open()){
        file<<kamera<<",";
        file<<harga<<",";
        file<<sewa<<endl;
        jmlKamera++;
        file.close();
        cout << "Kamera berhasil ditambahkan" << endl;
        return;
    }else{
        cerr << "Tidak dapat membuka file" << endl;
    }
}

void tulisUlangKameraCsv(){
    ofstream file("dataKamera.csv",ios::out|ios::trunc);
    if (file.is_open()){
        for (int i = 0 ; i < jmlKamera ; i++){
            file<<kmr[i].kamera<<",";
            file<<kmr[i].harga<<",";
            file<<kmr[i].sewa<<endl;
        }
        file.close();
    }else{
        cerr <<"Tidak dapat membuka file"<<endl;
    }
}

void bacaFileUserCsv(){
    string username, password, data, jmlKamera, kameraUser;
    int jmlKameraInt, idx = 0;
    ifstream file("dataUser.csv");
    if(file.is_open()){
        while(getline(file,data)){
            stringstream ss(data);
            getline(ss,username,',');
            getline(ss,password,',');
            getline(ss,jmlKamera,',');
            getline(ss,kameraUser,'\n');
            stringstream jmlKameraString(jmlKamera);
            jmlKameraString >> jmlKameraInt;
            usr[idx].nama = username;
            usr[idx].password = password;
            usr[idx].jmlKameraUser = jmlKameraInt;
            usr[idx].kmrUser[0].kamera = kameraUser;
            idx++;
            jmlUser = idx;

        }
        file.close();
    }
}

void tambahUserCsv(string username, string password){
    int jmlKameraUser = 0;
    string kameraUser;
    ofstream file("dataUser.csv",ios::app);
    if (file.is_open()){
        file<<username<<",";
        file<<password<<",";
        file<<jmlKameraUser<<",";
        file<<kameraUser<<endl;
        jmlUser++;
        file.close();
        return;
    }else{
        cerr << "Tidak dapat membuka file" << endl;
    }
}

void tulisUlangUserCsv(){
    ofstream file("dataUser.csv",ios::out);
    if (file.is_open()){
        for (int i = 0 ; i < jmlUser ; i++){
            file<<usr[i].nama<<",";
            file<<usr[i].password<<",";
            file<<usr[i].jmlKameraUser<<",";
            file<<usr[i].kmrUser[0].kamera<<endl;
        }
        file.close();
    }else{
        cerr <<"Tidak dapat membuka file"<<endl;
    }
}
//++++++++++++++++++++++++++++++++++++++

//=============Fitur Admin==============
void tambahKameraAdmin(){
    bacaFileKameraCsv();
    if(jmlKamera < 100){
        string nama, sewa = "Tersedia";
        string konfirmasi;
        int harga;
        while(true){
            cin.ignore();
            cout << "Masukkan nama kamera: ";
            getline(cin, nama);
            if(nama.empty()){
                cout << "Input tidak boleh kosong!";
            }else{
                while(true){
                    cout << "Masukkan harga kamera(per minggu): ";
                    cin >> harga;
                    cin.ignore();
                    if(cin.fail()|| harga < 0){
                        cout<<"Input tidak valid atau harga kurang dari sama dengan 0";
                        cin.clear();
                        cin.ignore(1000,'\n');
                    }else{
                        while (true){
                        cout << "Kamera\t\t:" << nama << endl;
                        cout << "Harga sewa\t: Rp. " << harga << endl;
                        cout << "Apakan ingin menambahkan data tersebut(y/n)?";
                        cin >> konfirmasi;
                        if (konfirmasi == "y" || konfirmasi == "Y"){
                            tambahKameraCsv(nama, harga, sewa);
                            return;
                        }else if (konfirmasi == "n" || konfirmasi == "N"){
                            return;
                        }else{
                            erorInput();
                        }
                    }
                    }
                }
            }
        }
    }else{
        cout << "Tidak dapat menambahkan kamera" << endl;
    }
}

void lihatKameraAdmin(){
    bacaFileKameraCsv();
    if (jmlKamera == 0){
        cout << "Tidak ada data kamera" << endl;
    }else{
    	bubbleSort(kmr, jmlKamera);
        for (int i =0; i< jmlKamera;i++){
            cout << i+1 << ".\tnama : " << kmr[i].kamera << endl;
            cout << "\tharga : Rp. " << kmr[i].harga << endl;
            if (kmr[i].sewa == "Tersedia"){
                cout << "\tstatus : Tersedia"<< endl;
                cout << endl;
            }else{
                cout << "\tstatus : Disewakan oleh "<< kmr[i].sewa << endl;
                cout << endl;
            }
        }
    }
}
void hapusKameraAdmin(){
    bacaFileKameraCsv();
    if (jmlKamera == 0){
        cout << "Tidak ada data kamera" << endl;
    }else{
        int idx;
        lihatKameraAdmin();
        while(true){
            cout << "Masukkan indeks kamera yang ingin di hapus ('0' untuk kembali): ";
            cin >> idx;
            if(cin.fail()){
                cout<<"Input tidak valid!"<<endl;
                cin.clear();
                cin.ignore(1000,'\n');
            }else if(idx == 0){
                return;
            }else{
                if (idx > jmlKamera || idx < 1){
                cout << "Indeks kamera tidak ditemukan" << endl;
                }else{
                    if(kmr[idx-1].sewa == "Tersedia"){
                        string konfirmasi;
                        while(true){
                            cout << "Kamera\t\t:" << kmr[idx-1].kamera << endl;
                            cout << "Harga sewa\t: Rp. " << kmr[idx-1].harga << endl;
                            cout << "Apakan ingin menghapus data tersebut(y/n)?";
                            cin >> konfirmasi;
                            if (konfirmasi == "y" || konfirmasi == "Y"){
                                for (int i = idx-1; i< jmlKamera;i++){
                                    kmr[i] = kmr[i+1];
                                }
                                jmlKamera--;
                                tulisUlangKameraCsv();
                                break;
                            }else if (konfirmasi == "n" || konfirmasi == "N"){
                                break;
                            }else{
                                erorInput();
                            }
                        }
                        break;
                    }else{
                        cout << "Kamera tersebut sedang disewakan, tidak dapat dihapus" << endl;
                    }
                }
            }
        }
    }
}

void editKameraAdmin(){
    bacaFileKameraCsv();
    if (jmlKamera == 0){
        cout << "Tidak ada data kamera" << endl;
    }else{
        int idx;
        lihatKameraAdmin();
        while(true){
            cout << "Masukkan indeks kamera yang ingin di edit ('0' untuk kembali): ";
            cin >> idx;
            if(cin.fail()){
                cout<<"Input tidak valid!"<<endl;
                cin.clear();
                cin.ignore(1000,'\n');
            }else if(idx == 0){
                return;
            }else{
                if (idx > jmlKamera || idx < 1){
                    cout << "Indeks kamera tidak ditemukan" << endl;
                }else{
                    if (kmr[idx-1].sewa == "Tersedia"){
                        string nama, konfirmasi;
                        int harga;
                        cout << "Kamera\t\t:" << kmr[idx-1].kamera << endl;
                        cout << "Harga sewa\t: Rp. " << kmr[idx-1].harga << endl;
                        cin.ignore();
                        cout << "Masukkan nama yang baru: ";
                        getline(cin, nama);
                        while(true){
                            cout << "Masukkan harga yang baru: ";
                            cin >> harga;
                            if(cin.fail() || harga < 0 ){
                                 cout<<"Input tidak valid atau harga kurang dari sama dengan 0"<<endl;
                                 cin.clear();
                                 cin.ignore(1000,'\n');
                            }else{
                                while (true){
                                    cout << "Kamera\t\t:" << kmr[idx-1].kamera << " Menjadi: " << nama << endl;
                                    cout << "Harga sewa\t: Rp. " << kmr[idx-1].harga << " Menjadi: Rp. " << harga << endl;
                                    cout << "Apakan ingin mengubah data tersebut(y/n)?";
                                    cin >> konfirmasi;
                                    if (konfirmasi == "y" || konfirmasi == "Y"){
                                        kmr[idx-1].kamera = nama;
                                        kmr[idx-1].harga = harga;
                                        tulisUlangKameraCsv();
                                        break;
                                    }else if (konfirmasi == "n" || konfirmasi == "N"){
                                        break;
                                    }else{
                                        erorInput();
                                    }
                                }
                                break;
                            }
                        }
                    }else{
                        cout << "Kamera sedang disewakan, tidak dapat merubah data!!!"<< endl;
                    }
                }
            break;
            }
        }
    }
}

void tampilanAdmin(){
        string pilihMenu;
        cout << menuAdmin() ;
        cout << "Masukkan pilihan: ";
        cin >> pilihMenu;
        if(pilihMenu == "1"){
            clearScreen();
            tambahKameraAdmin();
            lanjutkan();
            tampilanAdmin();
        }else if(pilihMenu == "2"){
            clearScreen();
            lihatKameraAdmin();
            lanjutkan();
            tampilanAdmin();
        }else if(pilihMenu == "3"){
            clearScreen();
            hapusKameraAdmin();
            lanjutkan();
            tampilanAdmin();
        }else if(pilihMenu == "4"){
            clearScreen();
            editKameraAdmin();
            lanjutkan();
            tampilanAdmin();
        }else if(pilihMenu == "5"){
            clearScreen();
            return;
        }else{
            erorInput();
            lanjutkan();
            tampilanAdmin();
    }     
}
//++++++++++++++++++++++++++++++++++++

//=============Fitur User=============

void lihatKameraUser(){
    bacaFileKameraCsv();
    if (jmlKamera == 0){
        cout << "Tidak ada data kamera" << endl;
    }else{
    	bubbleSort(kmr, jmlKamera);
        for (int i =0; i< jmlKamera;i++){
            cout << i+1 << ".\tnama : " << kmr[i].kamera << endl;
            cout << "\tharga : Rp. " << kmr[i].harga << endl;
            if (kmr[i].sewa == "Tersedia"){
                cout << "\tstatus : Tersedia"<< endl;
                cout << endl;
            }else{
                cout << "\tstatus : Tidak dapat disewakan"<< endl;
                cout << endl;
            }
        }
    }
}

void kembalikanKameraUser(){
    bacaFileKameraCsv();
    string konfirmasi;
    string nama = usr[idxUser].kmrUser[0].kamera;
    if (usr[idxUser].jmlKameraUser == 0){
        cout << "Anda belum menyewa kamera"<< endl;
    }else{
        while(true){
            cout << "Nama: "<< nama << endl;
            cout << "Apakah anda ingin mengembalikan kamera tersebut?(y/n): ";
            cin >> konfirmasi;
            if(konfirmasi == "y" || konfirmasi == "Y"){
                for (int i = 0; i < jmlKamera; i++){
                    if (kmr[i].kamera == nama){
                        kmr[i] = usr[idxUser].kmrUser[0];
                        usr[idxUser].kmrUser[0] = usr[idxUser].kmrUser[1];
                        usr[idxUser].jmlKameraUser--;
                        tulisUlangKameraCsv();
                        tulisUlangUserCsv();
                        cout << "Berhasil mengembalikan kamera"<< endl;
                        return;
                    }
                }
            }else if(konfirmasi == "n" || konfirmasi == "N"){
                cout << "Gagal mengembalikan kamera" << endl;
                return;
            }else{
                erorInput();
            }
        }
    }
}

void konfirmasiSewa(int sewa){
    string konfirmasi;
	while(true){
    	cout << "\tnama : " << kmr[sewa].kamera << endl;
        cout << "\tharga : Rp. " << kmr[sewa].harga << endl;
        cout << "Apakah anda ingin menyewa kamera tersebut(y/n)?";
        cin >> konfirmasi;
        if (konfirmasi == "y" || konfirmasi == "Y"){
            cout << "Kamera berhasil disewakan" << endl;
            usr[idxUser].kmrUser[0] = kmr[sewa];
            kmr[sewa].sewa = usr[idxUser].nama;
            usr[idxUser].jmlKameraUser++;
            tulisUlangKameraCsv();
            tulisUlangUserCsv();
            return;
        }else if (konfirmasi == "n" || konfirmasi == "N"){
            cout << "Sewa dibatalkan" << endl;
            return;
        }else{
            erorInput();
		}
	}
}
void cariBinarySearch(){
    bacaFileKameraCsv();
	if (jmlKamera == 0){
		cout << "Belum ada data kamera" << endl;
	}else{
		string cari;
		cin.ignore();
		cout << "Masukkan nama kamera: ";
		getline(cin, cari);
		bubbleSort(kmr, jmlKamera);
		int hasil = binarySearch(kmr, 0, jmlKamera-1, cari);
		if (hasil == -1){
			cout << "Nama tidak ditemukan." << endl;
		}else{
            if (kmr[hasil].sewa == "Tersedia"){
                if(usr[idxUser].jmlKameraUser == 1){
                    cout << "\tnama : " << kmr[hasil].kamera << endl;
                    cout << "\tharga : Rp. " << kmr[hasil].harga << endl;
                    cout << "\tstatus : "<< kmr[hasil].sewa << endl;
                }else{
                    konfirmasiSewa(hasil);
                    cout << endl;
                }
            }else{
				cout << "\tnama : " << kmr[hasil].kamera << endl;
            	cout << "\tharga : Rp. " << kmr[hasil].harga << endl;
                cout << "\tstatus : Tidak dapat disewakan"<< endl;
                cout << endl;
            }
		}	
	}
}

void sewaKameraUser(){
    bacaFileKameraCsv();
    if (jmlKamera == 0){
        cout << "Tidak ada data kamera" << endl;
    }else{
        if(usr[idxUser].jmlKameraUser == 1){
            cout << "Anda sudah menyewa kamera, silahkan mengembalikan kamera terlebih dahulu!!!" << endl;
        }else{
            int idx;
            while(true){
                lihatKameraUser();
                cout << "Masukkan indeks kamera yang ingin disewakan('0' untuk kembali): ";
                cin >> idx;
                if(cin.fail()){
                    cout<<"Input tidak valid!"<<endl;
                    cin.clear();
                    cin.ignore(1000,'\n');
                }else if(idx == 0){
                    return;
                }else if(kmr[idx-1].sewa != "Tersedia"){
                    cout << "Kamera tidak dapat disewakan!!!"<< endl;
                }else{
                	int sewa = idx-1;
                    konfirmasiSewa(sewa);
                    return;
                }
            }  
        }
    }
}

void tampilanUser(){
    while (true){
        string pilihMenu;
        //cout <<"Indeks: "<<  idxUser<< endl;
        cout << menuUser();
        cout << "Masukkan pilihan: ";
        cin >> pilihMenu;
        if(pilihMenu == "1"){
            clearScreen();
            lihatKameraUser();
            lanjutkan();
        }else if(pilihMenu == "2"){
            clearScreen();
        	cariBinarySearch();
            lanjutkan();
        }else if(pilihMenu == "3"){
            clearScreen();
            sewaKameraUser();
            lanjutkan();
        }else if(pilihMenu == "4"){
            clearScreen();
            kembalikanKameraUser();
            lanjutkan();
        }else if(pilihMenu == "5"){
            clearScreen();
            break;
        }else{
            erorInput();
            lanjutkan();
        }
    }     
}
//++++++++++++++++++++++++++++++++++++++

//=====Fitur Login & Registrasi=========
int loginUser(string username, string password){
    bacaFileUserCsv();
    for (int i=0; i<jmlUser; i++){
    	if (usr[i].nama == username && usr[i].password == password){
    		idxUser = i;
    		return 1;	
		}
	}
	return -1;
}

void login(){
	string username;
	string password;
	cin.ignore();
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);
	if (username == "admin" && password == "admin"){
        clearScreen();
		tampilanAdmin();
        lanjutkan();
	}else if (loginUser(username, password) == 1){
        clearScreen();
		tampilanUser();
        lanjutkan();
	}else{
		cout << "Username atau password salah!!!" << endl;
        lanjutkan();
	}
}

void registerUser(){
    bacaFileUserCsv();
    if (jmlUser < 100) {
        string username, password;
        while(true){
            cin.ignore();
            cout << "Masukkan username: ";
            getline(cin, username);
            if(username.empty()){
                cout << "Input tidak boleh kosong!";
            }else{
                while(true){
                    cout << "Masukkan password: ";
                    getline(cin, password);
                    if(password.empty()){
                        cout << "Input tidak boleh kosong";
                    }else{
                        for(int i = 0; i < jmlUser; i++){
                            if(username == usr[i].nama || username == "admin"){
                                cout << "Username sudah digunakan" << endl;
                                return;
                            }
                        }
                        usr[jmlUser].nama = username;
                        usr[jmlUser].password = password;
                        tambahUserCsv(username, password);
                        cout << "Register berhasil " << endl;
                        return;
                    }
                }
            }
        }
    }else{
        cout << "Penuh" << endl;
    }
}
//+++++++++++++++++++++++++++++++

void menuAwal(){
	while (true){
		cout << "1. Login\n"
		"2. Registrasi\n"
		"3. Keluar\n";
		string pilih;
		cout << "Masukkan pilihan: ";
		cin >> pilih;
		if (pilih == "1"){
            clearScreen();
			login();
		}else if (pilih == "2"){
            clearScreen();
			registerUser();
		}else if (pilih == "3"){
			return;
		}else{
			erorInput();
		}
	}
}

int main(){
    menuAwal();
    return 0;
}