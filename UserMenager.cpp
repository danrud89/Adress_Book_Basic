#include <iostream>
#include "Users.h"
#include "UserMenager.h"
#include "auxiliaryMethods.h"
#include "UsersFile.h"

using namespace std;

User::User(unsigned int userId, string userName, string userPassword)
{
    this -> userId = userId;
    this -> userName = userName;
    this -> userPassword = userPassword;
}

void UserMenager::RegisterNewUser()
{
    system("cls");
    cout<< ">>>REJESTRACJA NOWEGO UZYTKOWNIKA<<<" <<endl;
    cout<< "************************************" <<endl;
    cout<< endl;

    User singleUserForExport;
    int userCounter = singleUser.size();
    string userName, userPassword, userId;
    singleUserForExport.setId(userCounter + 1);
    cout<< auxiliaryMethods::PL("Podaj nazwe uzytkownika: ");
    userName = auxiliaryMethods::loadInputLine();
    singleUserForExport.setName(userName);
    for (auto itr = singleUser.begin(); itr != singleUser.end(); ++ itr)
    {
        if (itr -> getName() == userName)
        {
            cout << auxiliaryMethods::PL("Uzytkownik o takiej nazwie juz istnieje! Podaj inna nazwe: ");
            userName = auxiliaryMethods::loadInputLine();
            singleUserForExport.setName(userName);
        }
    }
    cout<< auxiliaryMethods::PL("Podaj haslo: ");
    userPassword = auxiliaryMethods::loadInputLine();
    singleUserForExport.setPassword(userPassword);
    singleUser.push_back(singleUserForExport);
    usersFile.ExportNewUser(singleUserForExport);
}

int UserMenager::LoggTheUserIn ()
{
    system("cls");
    cout << ">>>LOGOWANIE<<<" << endl;
    cout << "***************" << endl;
    cout << endl;
    if (singleUser.empty() != true)
    {
        string userName, userPassword;
        cout << "Podaj login: ";
        userName = auxiliaryMethods::loadInputLine();
        for (auto itr = singleUser.begin(); itr != singleUser.end(); ++ itr )
        {
            if (userName == itr -> getName())
            {
                for(auto attempt = 0; attempt < 3; attempt ++)
                {
                    cout<< auxiliaryMethods::PL("Podaj haslo. Pozostalo prob")<<" "<<"("<<(3 - attempt)<<")" <<": " ;
                    userPassword = auxiliaryMethods::loadInputLine();
                    if (userPassword == itr -> getPassword())
                    {
                        cout << "Logowanie poprawne" << endl;
                        LoggedInUserId = itr -> getId();
                        Sleep(1000);
                        return 0;
                    }
                }
                cout << auxiliaryMethods::PL("Wprowadzono 3 razy bledne haslo. Zaczekaj 3 sekundy przed kolejna próba...") << endl;
                Sleep(3000);
                return 0;
            }
        }
        cout << auxiliaryMethods::PL("Nie znaleziono uzytkowanika o podanym loginie. Sprobuj ponownie.") <<endl;
        Sleep(1500);
    }
    else
    cout << "Brak zalogowanych uzytkownikow! Utworz konto.";
    Sleep(1500);
}

void UserMenager::ChangeUserPassword()
{
    system("cls");
    cout<< auxiliaryMethods::PL(">>>ZMIANA HASLA<<<") <<endl;
    cout<< "******************" <<endl;
    cout<< endl;
    string newUserPassword, oldUserPassword;
    cout<< auxiliaryMethods::PL("Podaj stare haslo: ");
    oldUserPassword = auxiliaryMethods::loadInputLine();
    cout<< auxiliaryMethods::PL("Podaj nowe haslo: ");
    newUserPassword = auxiliaryMethods::loadInputLine();
    for(auto itr = singleUser.begin(); itr != singleUser.end(); ++ itr)
    {
        if (LoggedInUserId ==  itr -> getId())
        {
            if (oldUserPassword == itr -> getPassword())
            {
            itr->setPassword(newUserPassword);
            usersFile.ChangePasswordInFile(*itr);
            cout<<"Haslo zmienione pomyslnie!";
            Sleep(2000);
            break;
            }
        }
        else cout << "Nie udalo sie zmienic hasla";
    }
}

bool UserMenager::CheckUserId()
{
    if (LoggedInUserId > 0)
        return true;
    else
        return false;
}

void UserMenager::LoggTheUserOut()
{
    LoggedInUserId = 0;
}

int UserMenager::getLoggedInUserID()
{
    return LoggedInUserId;
}
