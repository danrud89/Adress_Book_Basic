#include <iostream>
#include "users.h"
#include "UserMenager.h"

using namespace std;

User::User(string uid, string name, string password)
{
    userId = uid;
    userName = name;
    userPassword = password;
}

bool UserMenager::fileExists (const string& fileName)
{
    fstream Database;
    Database.open(fileName.c_str(), ios::in);
    if ( Database.is_open() )
    {
        Database.close();
        return true;
    }
    Database.close();
    return false;
}

string UserMenager::intToString(int IdNumber)
{
    ostringstream ss;
    ss << IdNumber;
    return  ss.str();
}

void UserMenager::ImportAllUsers(vector <User> &singleUser)
{
    vector <string> individualUser;
    string personalUserData;
    fstream DatabaseUser;
    DatabaseUser.open("Uzytkownicy.txt", ios :: in);

    if (DatabaseUser.good() == true)
    {
        while(getline(DatabaseUser,personalUserData))
        {
            string individualUserData;
            auto singleUserNumber = 1;

            for (auto index = 0; index < personalUserData.length(); index ++)
            {
                if (personalUserData[index] != '|')
                {
                    individualUserData += personalUserData[index];
                }
                else
                {
                    switch(singleUserNumber)
                    {
                    case 1:
                        individualUser.push_back(individualUserData);
                        break;
                    case 2:
                        individualUser.push_back(individualUserData);
                        break;
                    case 3:
                        individualUser.push_back(individualUserData);
                        break;
                    }
                    individualUserData = "";
                    singleUserNumber ++;
                }
            }
            singleUser.push_back(User(individualUser[0], individualUser[1],
                                      individualUser[2]));
        }
    }
    DatabaseUser.close();
}

void UserMenager::ExportNewUser (vector<User>& singleUser)
{
    fstream DatabaseUser;
    DatabaseUser.open("Uzytkownicy.txt", ios::out|ios::app);
    if (DatabaseUser.good() == true)
    {
        for(auto index = 0; index < singleUser.size(); index ++)
        {
            DatabaseUser<< singleUser[index].userId + "|"
                        + singleUser[index].userName + "|"
                        + singleUser[index].userPassword + "|";
            DatabaseUser <<endl;
        }

        DatabaseUser.close();
        singleUser.clear();
        cout<< endl;
        cout<< "Dodano nowego uzytkownika." <<endl;
        Sleep(1500);
    }
    else
    {
        cout<< "Nie odnaleziono pliku!" <<endl;
        Sleep(1500);
    }
}

void UserMenager::RegisterNewUser(vector <User> &singleUser)
{
    system("cls");
    cout<< ">>>REJESTRACJA NOWEGO UZYTKOWNIKA<<<" <<endl;
    cout<< "************************************" <<endl;
    cout<< endl;

    vector <User> singleUserForExport;
    if(fileExists("Uzytkownicy.txt") == false) ofstream DatabaseUser( "Uzytkownicy.txt" );
    else
    {
        string userName, userPassword, userId;
        cout<< "Podaj nazwe uzytkownika: ";
        cin>> userName;
        for (auto index = 0; index < singleUser.size(); index ++)
        {
            if (singleUser[index].userName == userName)
            {
                cout << "Uzytkownik o takiej nazwie juz istnieje! Podaj inna nazwe: ";
                cin >> userName;
                index = 0;
            }
        }
        cout<< "Podaj haslo: ";
        cin>> userPassword;
        userId = intToString(singleUser.size() + 1);

        singleUserForExport.push_back(User(userId, userName, userPassword));
        UserMenager exportUser;
        exportUser.ExportNewUser(singleUserForExport);
        singleUserForExport.clear();
    }
}

int UserMenager::LoggTheUserIn (vector <User> &singleUser)
{
    system("cls");
    cout << ">>>LOGOWANIE<<<" << endl;
    cout << "***************" << endl;
    cout << endl;
    string userName, userPassword;
    cout << "Podaj login: ";
    cin >> userName;
    for (auto index = 0; index < singleUser.size(); index ++)
    {
        if (singleUser[index].userName == userName)
        {
            for(auto attempt = 0; attempt < 3; attempt ++)
            {
                cout<< "Podaj haslo. Pozostalo prob (" << 3 - attempt << "): ";
                cin >> userPassword;
                if (singleUser[index].userPassword == userPassword)
                {
                    cout << "Logowanie poprawne" << endl;
                    Sleep(1000);
                    return atoi(singleUser[index].userId.c_str());
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo. Zaczekaj 3 sekundy przed kolejna proba..." << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout<< "Nie znaleziono uzytkowanika o podanym loginie. Sprobuj ponownie." <<endl;
    Sleep(1500);
    return 0;
}

void UserMenager::ChangeUserPassword (vector<User> &singleUser, int &loggedUserId)
{
    system("cls");
    cout<< ">>>ZMIANA HASLA<<<" <<endl;
    cout<< "******************" <<endl;
    cout<< endl;
    string newUserPassword;
    cout<< "Podaj nowe haslo: ";
    cin>> newUserPassword;
    for(auto index = 0; index < singleUser.size(); index++)
    {
        if (singleUser[index].userId == intToString(loggedUserId))
        {
            singleUser[index].userPassword = newUserPassword;
        }
    }
    fstream DatabaseUser;
    DatabaseUser.open("Uzytkownicy.txt", ios::out);
    if (DatabaseUser.good() == true)
    {
        for(int index = 0; index < singleUser.size(); index++)
        {
            DatabaseUser<< singleUser[index].userId + "|"
                        + singleUser[index].userName + "|"
                        + singleUser[index].userPassword + "|";
            DatabaseUser <<endl;
        }
        DatabaseUser.close();
        cout<< "Haslo zmienione!" <<endl;
        Sleep(1500);
    }
}
