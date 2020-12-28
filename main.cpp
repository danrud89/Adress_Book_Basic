#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <conio.h>

using namespace std;

struct User
{
    string userId;
    string userName;
    string userPassword;
};

struct Contact
{
    string contactId;
    string userId;
    string contactName;
    string contactLastName;
    string contactPhoneNumber;
    string contactEmail;
    string contactAddress;
};

string intToString(int IdNumber)
{
    ostringstream ss;
    ss << IdNumber;
    return  ss.str();
}

bool checkIfContactExists(vector <Contact> singleContact, int contactNumberToBeChanged)
{
    vector <string> IdNumbersOnly;
    for(auto index = 0; index < singleContact.size(); index ++)
    {
        IdNumbersOnly.push_back(singleContact[index].contactId);
    }
    auto itr = find(IdNumbersOnly.begin(), IdNumbersOnly.end(), intToString(contactNumberToBeChanged));
    if (itr != IdNumbersOnly.end()) return true;
    else return false;
}

bool fileExists (const string& fileName)
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

int FindPositionInVector (vector <Contact> singleContact, int contactNumberToBeChanged)
{
    vector <string> IdNumbersOnly;
    for(auto index = 0; index < singleContact.size(); index ++)
    {
        IdNumbersOnly.push_back(singleContact[index].contactId);
    }

    for (auto index = 0; index < IdNumbersOnly.size(); index ++)
    {
        if (IdNumbersOnly[index] == intToString(contactNumberToBeChanged))
            return index;
    }
}

void ImportAllUsers(vector <User> &singleUser)
{
    User individualUser;
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
                        individualUser.userId = individualUserData;
                        break;
                    case 2:
                        individualUser.userName = individualUserData;
                        break;
                    case 3:
                        individualUser.userPassword = individualUserData;
                        break;
                    }
                    individualUserData = "";
                    singleUserNumber ++;
                }
            }
            singleUser.push_back(individualUser);
        }
    }
    DatabaseUser.close();
}

void ExportNewUser (vector<User>& singleUser)
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

void RegisterNewUser(vector <User> &singleUser)
{
    system("cls");
    cout<< ">>>REJESTRACJA NOWEGO UZYTKOWNIKA<<<" <<endl;
    cout<< "************************************" <<endl;
    cout<< endl;

    if(fileExists("Uzytkownicy.txt") == false) ofstream DatabaseUser( "Uzytkownicy.txt" );
    else
    {
        User individualUser;
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

        individualUser.userId = userId;
        individualUser.userName = userName;
        individualUser.userPassword = userPassword;

        singleUser.push_back(individualUser);
        ExportNewUser(singleUser);
    }
}

int LoggTheUserIn (vector <User> &singleUser)
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

void ChangeUserPassword (vector<User> &singleUser, int &loggedUserId)
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

void ImportAllContacts (vector <Contact> &singleContact)
{
    Contact individualContact;
    string personalData;
    fstream DatabaseContact;
    DatabaseContact.open("Kontakty.txt", ios :: in);

    if (DatabaseContact.good() == true)
    {
        while(getline(DatabaseContact,personalData))
        {
            string individualPersonalData;
            auto singleContactNumber = 1;

            for (auto index = 0; index < personalData.length(); index ++)
            {
                if (personalData[index] != '|')
                {
                    individualPersonalData += personalData[index];
                }
                else
                {
                    switch(singleContactNumber)
                    {
                    case 1:
                        individualContact.contactId = individualPersonalData;
                        break;
                    case 2:
                        individualContact.userId = individualPersonalData;
                        break;
                    case 3:
                        individualContact.contactName = individualPersonalData;
                        break;
                    case 4:
                        individualContact.contactLastName = individualPersonalData;
                        break;
                    case 5:
                        individualContact.contactPhoneNumber = individualPersonalData;
                        break;
                    case 6:
                        individualContact.contactEmail = individualPersonalData;
                        break;
                    case 7:
                        individualContact.contactAddress = individualPersonalData;
                        break;
                    }
                    individualPersonalData = "";
                    singleContactNumber ++;
                }
            }
            singleContact.push_back(individualContact);
        }
    }
    DatabaseContact.close();
}

int ReturnLastContactNumber (vector <Contact> singleContact)
{
    ImportAllContacts(singleContact);
    if (singleContact.empty() == true )
        return 0;
    else
    {
        auto lastContactNumber = singleContact.size() - 1;
        return atoi(singleContact[lastContactNumber].contactId.c_str());
    }
}

void ImportContactsForLoggedUser (vector <Contact> &singleContact, int &loggedUserId)
{
    Contact individualContact;
    string personalData;
    fstream DatabaseContact;
    DatabaseContact.open("Kontakty.txt", ios :: in);

    if (DatabaseContact.good() == true)
    {
        while(getline(DatabaseContact,personalData))
        {
            string individualPersonalData;
            auto singleContactNumber = 1;

            for (auto index = 0; index < personalData.length(); index ++)
            {
                if (personalData[index] != '|')
                {
                    individualPersonalData += personalData[index];
                }
                else
                {
                    switch(singleContactNumber)
                    {
                    case 1:
                        individualContact.contactId = individualPersonalData;
                        break;
                    case 2:
                        individualContact.userId = individualPersonalData;
                        break;
                    case 3:
                        individualContact.contactName = individualPersonalData;
                        break;
                    case 4:
                        individualContact.contactLastName = individualPersonalData;
                        break;
                    case 5:
                        individualContact.contactPhoneNumber = individualPersonalData;
                        break;
                    case 6:
                        individualContact.contactEmail = individualPersonalData;
                        break;
                    case 7:
                        individualContact.contactAddress = individualPersonalData;
                        break;
                    }
                    individualPersonalData = "";
                    singleContactNumber ++;
                }
            }
            if (individualContact.userId == intToString(loggedUserId))
                singleContact.push_back(individualContact);
            else continue;
        }
    }
    DatabaseContact.close();
}

void ExportContactIntoFile (vector <Contact> &singleContactForExport )
{
    fstream DatabaseContact;
    DatabaseContact.open("Kontakty.txt",ios :: out | ios :: app);
    if (DatabaseContact.good() == true)
    {
        for (auto index = 0; index < singleContactForExport.size(); index ++)
        {
            DatabaseContact << singleContactForExport[index].contactId + "|" + singleContactForExport[index].userId + "|"
                            + singleContactForExport[index].contactName + "|" + singleContactForExport[index].contactLastName
                            + "|" + singleContactForExport[index].contactPhoneNumber + "|" + singleContactForExport[index].contactEmail
                            + "|" + singleContactForExport[index].contactAddress + "|";
            DatabaseContact << endl;

        }
        DatabaseContact.close();
    }
    cout << "Dodano nowy kontakt" << endl;
    Sleep(1000);
}

void AddNewContact (vector<Contact>& singleContact, int &loggedUserId)
{
    system("cls");
    cout << ">>>DODAJ NOWY KONTAKT<<<" << endl;
    cout << "************************" << endl;

    if(fileExists("Kontakty.txt") == false) ofstream DatabaseContact( "Kontakty.txt" );
    else
    {
        Contact individualContact;
        vector<Contact> singleContactForExport;
        string contactName, contactLastName, contactPhoneNumber, contactEmail, contactAddress;
        int contactNumber = ReturnLastContactNumber(singleContact)+1;
        string IdNumber = intToString(contactNumber);
        cout << "Podaj imie: ";
        cin >> contactName;
        cout << "Podaj nazwisko: ";
        cin >> contactLastName;
        cout << "Podaj numer telefonu: ";
        cin >> contactPhoneNumber;
        cout << "Podaj adres e-mail: ";
        cin >> contactEmail;
        cout << "Podaj adres (ulica, kod pocztowy, miasto): ";
        cin.ignore();
        getline(cin, contactAddress);

        individualContact.contactId = IdNumber;
        individualContact.userId = intToString(loggedUserId);
        individualContact.contactName = contactName;
        individualContact.contactLastName = contactLastName;
        individualContact.contactPhoneNumber = contactPhoneNumber;
        individualContact.contactEmail = contactEmail;
        individualContact.contactAddress = contactAddress;

        singleContactForExport.push_back(individualContact);

        ExportContactIntoFile(singleContactForExport);
        singleContactForExport.clear();
    }
}

void SearchByName (vector <Contact> & singleContact, string nameToSearch)
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO IMIENIU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    cout << "Podaj imie: ";
    cin >> nameToSearch;
    for (auto index = 0; index < singleContact.size(); index ++)
    {
        if (singleContact[index].contactName == nameToSearch)
        {
            cout << singleContact[index].contactName << " " << singleContact[index].contactLastName << " " << endl;
            cout << singleContact[index].contactPhoneNumber << " " << endl;
            cout << singleContact[index].contactEmail << " " << endl;
            cout << singleContact[index].contactAddress << " " << endl;
        }
    }
    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
    getch();
}

void SearchByLastName (vector <Contact> & singleContact, string lastNameToSearch)
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO NAZWISKU<<<" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    cout << "Podaj nazwisko: ";
    cin >> lastNameToSearch;
    for (auto index = 0; index < singleContact.size(); index ++)
    {
        if (singleContact[index].contactLastName == lastNameToSearch)
        {
            cout << singleContact[index].contactName << " " << singleContact[index].contactLastName << " " << endl;
            cout << singleContact[index].contactPhoneNumber << " " << endl;
            cout << singleContact[index].contactEmail << " " << endl;
            cout << singleContact[index].contactAddress << " " << endl;
        }
    }
    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
    getch();
}

void SearchForAContact (vector <Contact> &singleContact)
{
    string nameToSearch, lastNameToSearch;
    int userSelect;

    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT<<<" << endl;
    cout << "**********************" << endl;
    cout << endl;
    cout << "1. >>Wyszukaj po imieniu<<" << endl;
    cout << "2. >>Wyszukaj po nazwisku<<" << endl;
    cout << "3. >>Powrot do Menu Glownego<<" << endl;
    cout << endl;
    cout << "Prosze wybrac opcje: " << endl;
    cin >> userSelect;

    if (userSelect == 1 || userSelect == 2 || userSelect == 3)
    {
        switch(userSelect)
        {
        case 1:
            SearchByName (singleContact, nameToSearch);
            break;
        case 2:
            SearchByLastName (singleContact, lastNameToSearch);
            break;
        case 3:
            break;
        }
    }
    else
    {
        cout << "Podales niewlasciwa cyfre. Sproboj jeszcze raz." << endl;
        Sleep(1500);
    }
}

void ViewAllContacts (vector <Contact> &singleContact, int &loggedUserId)
{
    system("cls");
    cout << ">>>LISTA WSZYSTKICH KONTAKTOW<<<" << endl;
    cout << "********************************" << endl;

    for (auto index = 0; index < singleContact.size(); index ++)
    {
        if (singleContact[index].userId == intToString(loggedUserId))
        {
         cout << singleContact[index].contactId << endl;
         cout << singleContact[index].contactName << " " << singleContact[index].contactLastName << " " << endl;
         cout << singleContact[index].contactPhoneNumber << " " << singleContact[index].contactEmail << " " << endl;
         cout << singleContact[index].contactAddress << " " << endl;
        }
    }
    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
    getch();
}

void updateDatabaseContactFile(vector <Contact> &singleContact)
{
    fstream DatabaseContact;
    DatabaseContact.open("Kontakty.txt",ios::out);
    if (DatabaseContact.good() == true)
    {
        for(auto index = 0; index < singleContact.size(); index ++)
        {
            DatabaseContact << singleContact[index].contactId + "|" + singleContact[index].userId + "|"
                            + singleContact[index].contactName + "|" + singleContact[index].contactLastName
                            + "|" + singleContact[index].contactPhoneNumber + "|" + singleContact[index].contactEmail
                            + "|" + singleContact[index].contactAddress + "|";
            DatabaseContact << endl;
        }
        DatabaseContact.close();
        cout << "Kontakt zostal zmieniony!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "Nie udalo sie zmienic kontaktu!" << endl;
        Sleep(1500);
    }
}

void ContactEdition(vector <Contact> &singleContact, int &loggedUserId)
{
    singleContact.clear();
    ImportAllContacts(singleContact);
    ViewAllContacts(singleContact,loggedUserId);
    cout << endl;
    string newPhoneNumber, newEmail, newAdress;
    int contactNumberToBeChanged = 0;
    cout << "Podaj numer kontaktu, ktory chcesz edytowac: " << endl;
    cin >> contactNumberToBeChanged;
    int positionInVector = FindPositionInVector(singleContact, contactNumberToBeChanged);
    if ((checkIfContactExists(singleContact, contactNumberToBeChanged) == true ) && (singleContact[positionInVector].userId == intToString(loggedUserId)))
    {
        for(auto index = 0; index < singleContact.size(); index ++)
        {
            if (singleContact[index].contactId == intToString(contactNumberToBeChanged))
            {
                cout << singleContact[index].contactName << " " << singleContact[index].contactLastName << " " << endl;
                cout << singleContact[index].contactPhoneNumber << " " << singleContact[index].contactEmail << " " << endl;
                cout << singleContact[index].contactAddress << " " << endl;
            }
        }
        cout << endl;
        cout << "Wybierz dane do zmiany: " << endl;
        cout << "1. Numer telefonu" << endl;
        cout << "2. Adres e-mail" << endl;
        cout << "3. Adres zamieszkania" << endl;
        cout << endl;
        int userChoice = 0;
        cin >> userChoice;
        switch(userChoice)
        {
        case 1:
        {
            cout << "Podaj nowy numer telefonu: ";
            cin.ignore();
            getline(cin, newPhoneNumber);
            singleContact[positionInVector].contactPhoneNumber = newPhoneNumber;
        }
        break;

        case 2:
        {
            cout << "Podaj nowy adres mailowy: ";
            cin >> newEmail;
            singleContact[positionInVector].contactEmail = newEmail;
        }
        break;

        case 3:
        {
            cout << "Podaj nowy adres zamieszkania: ";
            cin.ignore();
            getline(cin, newAdress);
            singleContact[positionInVector].contactAddress = newAdress;
        }
        break;
        }
        updateDatabaseContactFile(singleContact);
    }
    else
    {
        cout<< "Kontakt o takim numerze ID nie istnieje !" <<endl;
        Sleep(2000);
    }
}

void RemoveContact(vector <Contact> &singleContact, int &loggedUserId)
{
    ViewAllContacts(singleContact, loggedUserId);
    system("cls");
    cout << ">>>USUWANIE WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    int contactNumberToRemove = 0;
    char userAccept;
    cout << "Podaj numer ID kontaktu, ktory chcesz usunac: ";
    cin >> contactNumberToRemove;
    if (((checkIfContactExists(singleContact, contactNumberToRemove)) == true) && (singleContact[contactNumberToRemove-1].userId == intToString(loggedUserId)))
    {
        for (auto index = 0; index != singleContact.size(); index ++ )
        {
            if (intToString(contactNumberToRemove) == singleContact[index].contactId)
            {
                cout << singleContact[index].contactName << " " << endl;
                cout << singleContact[index].contactLastName << " " << endl;
                cout << singleContact[index].contactPhoneNumber << " " << endl;
                cout << singleContact[index].contactEmail << " " << endl;
                cout << singleContact[index].contactAddress << " " << endl;

                cout << "Wcisnij 't' aby potwierdzic usuniecie wybranego adresata: ";
                cin >> userAccept;
                if (userAccept == 't')
                {
                    vector <string > tmp;
                    ifstream input("Kontakty.txt");
                    string deletedLine;
                    while(getline(input, deletedLine)) tmp.push_back(deletedLine);
                    input.close();
                    ofstream output("Kontakty.txt");
                    for( auto index = 0; index < tmp.size(); index ++)
                    {
                        if(index + 1 != contactNumberToRemove) output << tmp[index] << endl;
                    }
                    output.close();
                    cout << " Wybrany kontakt zostal usuniety!" << endl;
                    Sleep(2000);
                }
                else
                {
                    cout << "Wybrany kontakt nie zostal usuniety" << endl;
                    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
                    getch();
                }
            }
        }
    }
    else
    {
        cout << "Kontakt o takim numerze ID nie istnieje !" << endl;
        Sleep(2000);
    }
}

int main()
{
    int loggedUserId = 0;

    while (true)
    {
        vector <User> singleUser;
        if(fileExists("Uzytkownicy.txt") == true)  ImportAllUsers (singleUser);

        if (loggedUserId == 0)
        {
            system("cls");
            cout << "\t******************************************" << endl;
            cout << "\t>>>>>>>>>>> KSIAZKA ADRESOWA <<<<<<<<<<<<<" << endl;
            cout << "\t******************************************" << endl << endl;
            cout << "\t************ 1.REJESTRACJA ***************" << endl;
            cout << "\t************* 2.LOGOWANIE ****************" << endl;
            cout << "\t************** 3.WYJSCIE *****************" << endl;
            cout << endl;
            cout << "Prosze wybrac opcje ==> ";
            int userSelection;
            cin >> userSelection;

            switch (userSelection)
            {
            case 1:
            {
                RegisterNewUser(singleUser);
            }
            break;
            case 2:
            {
                if (singleUser.empty() == true)
                {
                    cout << "Brak zarejestrowanych uzytkownikow !";
                    Sleep(2000);
                }
                else loggedUserId = LoggTheUserIn (singleUser);
            }
            break;

            case 3:
            {
                cout << "Nastapi zamkniecie programu...";
                Sleep(1500);
                exit(0);
            }
            break;
            }
        }
        else
        {
            vector <Contact> singleContact;

            if(fileExists("Kontakty.txt"))
            {
                ImportContactsForLoggedUser(singleContact, loggedUserId);
            }
            system("cls");
            cout << "\t**********************************************" << endl;
            cout << "\t>>>>>>>>>>>>>>> MENU GLOWNE <<<<<<<<<<<<<" << endl;
            cout << "\t**********************************************" << endl << endl;
            cout << "\t************ 1.DODAJ NOWY KONTAKT ************" << endl;
            cout << "\t************ 2.WYSZUKAJ KONTAKT **************" << endl;
            cout << "\t******* 3.WYSWIETL WSZYSTKIE KONTAKTY ********" << endl;
            cout << "\t************ 4.EDYCJA KONTAKTU ***************" << endl;
            cout << "\t************* 5.USUN KONTAKT *****************" << endl;
            cout << "\t************* 6.ZMIANA HASLA *****************" << endl;
            cout << "\t************** 7.WYLOGUJ *********************" << endl;
            cout << endl;
            cout << "Prosze wybrac opcje ==> ";
            int userSelect;
            cin >> userSelect;


            switch (userSelect)
            {
            case 1:
                AddNewContact(singleContact, loggedUserId);
                break;

            case 2:
            {
                if (singleContact.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
                    getch();
                }
                else SearchForAContact (singleContact);
            }
            break;

            case 3:
            {
                if (singleContact.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
                    getch();
                }
                else ViewAllContacts (singleContact, loggedUserId);
            }
            break;

            case 4:
            {
                if (singleContact.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
                    getch();
                }
                else  ContactEdition(singleContact, loggedUserId);
            }
            break;

            case 5:
            {
                if (singleContact.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
                    getch();
                }
                else RemoveContact (singleContact, loggedUserId);
            }
            break;

            case 6:
                ChangeUserPassword(singleUser, loggedUserId);
                break;

            case 7:
            {
                loggedUserId = 0;
                cout << "Wylogowales sie.";
                Sleep(1500);
                break;
            }
            }
        }
    }
}
