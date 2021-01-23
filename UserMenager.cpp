#include <iostream>
#include "users.h"
#include "UserMenager.h"
#include "auxiliaryMethods.h"

using namespace std;

User::User(string userId, string userName, string userPassword)
{
    this -> userId = userId;
    this -> userName = userName;
    this -> userPassword = userPassword;
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
        cout<< auxiliaryMethods::PL("Dodano nowego u¿ytkownika.") <<endl;
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
    cout<< auxiliaryMethods::PL(">>>REJESTRACJA NOWEGO U¯YTKOWNIKA<<<") <<endl;
    cout<< "************************************" <<endl;
    cout<< endl;

    vector <User> singleUserForExport;
    if(auxiliaryMethods::fileExists("Uzytkownicy.txt") == false) ofstream DatabaseUser( "Uzytkownicy.txt" );
    else
    {
        string userName, userPassword, userId;
        cout<< auxiliaryMethods::PL("Podaj nazwê u¿ytkownika: ");
        cin>> userName;
        for (auto index = 0; index < singleUser.size(); index ++)
        {
            if (singleUser[index].userName == userName)
            {
                cout << auxiliaryMethods::PL("U¿ytkownik o takiej nazwie ju¿ istnieje! Podaj inn¹ nazwê: ");
                cin >> userName;
                index = 0;
            }
        }
        cout<< auxiliaryMethods::PL("Podaj has³o: ");
        cin>> userPassword;
        userId = auxiliaryMethods::intToString(singleUser.size() + 1);

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
                cout<< auxiliaryMethods::PL("Podaj has³o. Pozosta³o prób")<<" "<<"("<<(3 - attempt)<<")" <<": " ;
                cin >> userPassword;
                if (singleUser[index].userPassword == userPassword)
                {
                    cout << "Logowanie poprawne" << endl;
                    Sleep(1000);
                    return atoi(singleUser[index].userId.c_str());
                }
            }
            cout << auxiliaryMethods::PL("Wprowadzono 3 razy b³êdne has³o. Zaczekaj 3 sekundy przed kolejn¹ prób¹...") << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout<< auxiliaryMethods::PL("Nie znaleziono u¿ytkowanika o podanym loginie. Spróbuj ponownie.") <<endl;
    Sleep(1500);
    return 0;
}

void UserMenager::ChangeUserPassword (vector<User> &singleUser, int &loggedUserId)
{
    system("cls");
    cout<< auxiliaryMethods::PL(">>>ZMIANA HAS£A<<<") <<endl;
    cout<< "******************" <<endl;
    cout<< endl;
    string newUserPassword;
    cout<< auxiliaryMethods::PL("Podaj nowe has³o: ");
    cin>> newUserPassword;
    for(auto index = 0; index < singleUser.size(); index++)
    {
        if (singleUser[index].userId == auxiliaryMethods::intToString(loggedUserId))
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
        cout<< auxiliaryMethods::PL("Has³o zmienione!") <<endl;
        Sleep(1500);
    }
}
