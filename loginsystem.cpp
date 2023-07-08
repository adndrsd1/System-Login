#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

void regist()
{
    string user_input, pass_input, pass2_input, data;
    bool status = true;
    cout << "========================================\n";
    cout << "               REGISTRASI               \n";
    cout << "========================================\n";
    cout << "Username : ";
    cin >> user_input;
    cout << "Kata Sandi : ";
    cin >> pass_input;
    cout << "Konfirmasi Kata Sandi : ";
    cin >> pass2_input;

    fstream database;
    database.open("database.txt", ios :: in);
    while (getline(database, data))
    {
        istringstream str(data);
        string username, password, password2;
        str >> username >> password >> password2;

        if (user_input != username)
        {
            if (pass_input == password)
            {
                system("cls");
                cout << "Kata sandi sudah digunakan, coba lagi!" << endl;
                status = false;
                regist();
            }
        }
        else
        {
            system("cls");
            cout << "Username sudah digunakan, coba lagi!" << endl;
            status = false;
            regist();
        }
    }
    if (pass_input != pass2_input)
    {
        system("cls");
        cout << "Kata sandi tidak cocok, coba lagi!" << endl;
        regist();
    }
    database.close();
    
    if (status)
    {
        database.open("database.txt", ios ::app);
        database << user_input + " " + pass_input << endl;
        database.close();
    }
    cout << "Registrasi Berhasil!\n";
}

void login()
{
    int count;
    string user_input, pass_input, username, password;
    cout << "========================================\n";
    cout << "                  LOGIN                 \n";
    cout << "========================================\n";
    cout << "Username : "; cin >> user_input;
    cout << "Kata Sandi : "; cin >> pass_input;

    fstream database;
    database.open("database.txt", ios :: in);

    while (database >> username >> password)
    {
        if (username == user_input && password == pass_input)
        {
            count = 1;
            system("cls");
        }
    }
    database.close();

    if (count == 1)
    {
        cout << "Login Berhasil!\n";
    }
    else
    {
        cout << "Login Gagal!\n";
    }
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
        cout << "[3] Keluar " << endl;
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
                cout << "Terima kasih!";
                break;
            default:
                system("cls");
                cout << "Pilihan tidak tersedia" << endl;
                main();
        }
        cout << "Apakah ingin melanjutkan? [Y/N] : "; 
        cin >> option2;
    } while (option2 != 'N');
    
    return 0;
}