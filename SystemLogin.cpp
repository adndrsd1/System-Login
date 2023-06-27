#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

string **readFile()
{
    string **arrdata = new string*[10]; 
    for (int i = 0; i < 10; i++)
    {
        arrdata[i] = new string[3];
    }
    
    string data, substring, strsplit;
    ifstream kelas_B("kelas_B.txt");
    int i = 0;
    while (getline(kelas_B, data))
    {
        int counter = 0;
        string temp[3];
        substring = data.substr(1, data.length() - 1);
        istringstream str(substring);
        while (getline(str, strsplit, ';'))
        {
            arrdata[i][counter++] = strsplit;
        }
        i++;
    }
    kelas_B.close();
    return arrdata; 
}

void clear(string **arrdata)
{
    for (int i = 0; i < 10; i++)
    {
        delete[] arrdata[i];
    }
    delete[] arrdata;
    
}

void lihatData()
{
    string arrdata;
    ifstream kelas_B("kelas_B.txt");
    while (getline(kelas_B, arrdata))
    {
        cout << arrdata << endl;
    }
    kelas_B.close();
}

void regist()
{
    string nim_input, nama_input, pass_input, pass2_input;
    string data, substring, strsplit;
    fstream kelas_B;
    bool status = true;
    cout << "====================================\n";
    cout << "             REGISTRASI             \n";
    cout << "====================================\n";
    cout << "NIM : ";
    cin >> nim_input;
    cin.ignore();
    cout << "Nama : ";
    getline(cin, nama_input);
    cout << "Kata Sandi : ";
    cin >> pass_input;
    cout << "Konfirmasi Kata Sandi : ";
    cin >> pass2_input;

    string **arrdata = readFile();
    int j;
    for (j = 0; j < 10; j++)
    {
        if (nim_input == arrdata[j][0])
        {
            system("cls");
            cout << "NIM sudah digunakan, coba lagi!" << endl;
            status = false;
        }
    }

    if (pass_input != pass2_input)
    {
        system("cls");
        cout << "Kata sandi tidak cocok, coba lagi!" << endl;
        status = false;
    }

    if (status)
    {
        kelas_B.open("kelas_B.txt", ios ::app);
        kelas_B << "#" + nim_input + ";" + nama_input + ";" + pass_input + ";" << endl;
        cout << "Registrasi Berhasil!\n";
        kelas_B.close();
    }
    else
    {
        regist();
    }
    clear(arrdata);
}

void login()
{
    string nim_input, pass_input;
    string data, substring, strsplit;
    fstream kelas_B;
    bool status = false;

    cout << "==================================\n";
    cout << "               LOGIN              \n";
    cout << "==================================\n";
    cout << "NIM : ";
    cin >> nim_input;
    cout << "Kata sandi : ";
    cin >> pass_input;

    string **arrdata = readFile();
    for (int j = 0; j < 10; j++)
    {
        if (nim_input == arrdata[j][0] && pass_input == arrdata[j][2])
        {
            system("cls");
            cout << "Login Berhasil!\n";
            cout << "Selamat datang " << arrdata[j][1] << endl;
            status = true;
            break;
        }
    }

    if (!status)
    {
        system("cls");
        cout << "Login Gagal. Periksa kembali NIM dan Kata Sandi!" << endl;
    }
    clear(arrdata);
}
    
void deleteAkun()
{
    string nim_input, pass_input;
    string data, substring, strsplit;
    fstream kelas_B;
    bool status = false;

    cout << "====================================\n";
    cout << "             DELETE AKUN            \n";
    cout << "====================================\n";
    cout << "NIM : ";
    cin >> nim_input;
    cout << "Kata sandi : ";
    cin >> pass_input;

    string **arrdata = readFile();
    int i;
    for (i = 0; i < 10; i++)
    {
        if (nim_input == arrdata[i][0] && pass_input == arrdata[i][2])
        {
            status = true;
            break;
        }
    }
    if (status)
    {
        for (int j = i; j < 10 - 1; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                arrdata[j][k] = arrdata[j + 1][k];
            }
        }
    }   
    else
    {
        cout << "Akun tidak ditemukan!" << endl;
    }

    kelas_B.open("kelas_B.txt", ios ::out);
    for (int i = 0; i < 10; i++)
    {
        if (arrdata[i][0] == "")
        {
            kelas_B << "";
        }
        else
        {
            kelas_B << "#";
            for (int j = 0; j < 3; j++)
            {
                kelas_B << arrdata[i][j] + ";";
            }
            kelas_B << endl;
        }
    }
    kelas_B.close();
    clear(arrdata);
}

int main()
{
    int option;
    char option2;
    do
    {
        system("cls");
        cout << "=========================================\n";
        cout << "             SELAMAT DATANG              \n";
        cout << "=========================================\n";

        cout << "[1] Registrasi " << endl;
        cout << "[2] Login " << endl;
        cout << "[3] Lihat Data " << endl;
        cout << "[4] Delete Akun " << endl;
        cout << "[0] Keluar " << endl;
        cout << "Masukkan pilihan : ";
        cin >> option;

        switch (option)
        {
        case 1:
            system("cls");
            regist();
            break;
        case 2:
            system("cls");
            login();
            break;
        case 3:
            system("cls");
            lihatData();
            break;
        case 4:
            system("cls");
            deleteAkun();
            break;
        case 0:
            system("cls");
            cout << "Terima kasih!";
            exit(1);
            break;
        default:
            system("cls");
            cout << "Pilihan tidak tersedia" << endl;
            break;
        }
        cout << "\nApakah ingin melanjutkan? [Y/N] : ";
        cin >> option2;
        option2 = toupper(option2);
    } while (option2 != 'N');

    return 0;
}