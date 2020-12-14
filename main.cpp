#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct User
{
    string userId;
    string userName;
    string userPassword;
};

struct Person
{
    string contactId;
    string userId;
    string name;
    string lastName;
    string phoneNumber;
    string eMail;
    string adress;
};

string intToString(int IdNumber)
{
    ostringstream ss;
    ss << IdNumber;
    return  ss.str();
}

bool checkIfContactExists(vector <Person> singlePerson, int contactNumberToBeChanged)
{
    vector <string> IdNumbersOnly;
    for(auto index = 0; index < singlePerson.size(); index ++)
    {
        IdNumbersOnly.push_back(singlePerson[index].contactId);
    }
    auto itr = find(IdNumbersOnly.begin(), IdNumbersOnly.end(), intToString(contactNumberToBeChanged));
    if (itr != IdNumbersOnly.end()) return true;
    else return false;
}

bool fileExists (const string& fileName)
{
    fstream DatabaseContact;
    DatabaseContact.open(fileName.c_str(), ios::in);
    if ( DatabaseContact.is_open() )
    {
        DatabaseContact.close();
        return true;
    }
    DatabaseContact.close();
    return false;
}

auto FindPositionInVector (vector <Person> singlePerson, int contactNumberToBeChanged)
{
    vector <string> IdNumbersOnly;
    for(auto index = 0; index < singlePerson.size(); index ++)
    {
        IdNumbersOnly.push_back(singlePerson[index].contactId);
    }

    for (auto index = 0; index < IdNumbersOnly.size(); index ++)
    {
        if (IdNumbersOnly[index] == intToString(contactNumberToBeChanged))

            return index;
    }
}

auto ReturnLastContactNumber (vector <Person> singlePerson)
{
    if (singlePerson.empty() == true )
        return 0;
    else
    {
        auto lastContactNumber = singlePerson.size() - 1;
        return atoi(singlePerson[lastContactNumber].contactId.c_str());
    }
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
        cout<< "Uzytkownik zostal dodany!" <<endl;
        Sleep(1500);
    }
    else
    {
        cout<< "Nie odnaleziono takiego pliku" <<endl;
        Sleep(1500);
    }
}

void RegisterNewUser(vector <User> &singleUser)
{
    system("cls");
    cout<< ">>>REJESTRACJA NOWEGO UZYTKOWNIKA<<<" <<endl;
    cout<< "************************************" <<endl;
    cout<< endl;

    ofstream DatabaseContact( "Uzytkownicy.txt" );
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

void ImportAllContacts (vector <Person> &singlePerson)
{
    Person individualPerson;
    string personalData;
    fstream DatabaseContact;
    DatabaseContact.open("Kontakty.txt", ios :: in);

    if (DatabaseContact.good() == true)
    {
        while(getline(DatabaseContact,personalData))
        {
            string individualPersonalData;
            auto singlePersonNumber = 1;

            for (auto index = 0; index < personalData.length(); index ++)
            {
                if (personalData[index] != '|')
                {
                    individualPersonalData += personalData[index];
                }
                else
                {
                    switch(singlePersonNumber)
                    {
                    case 1:
                        individualPerson.contactId = individualPersonalData;
                        break;
                    case 2:
                        individualPerson.name = individualPersonalData;
                        break;
                    case 3:
                        individualPerson.lastName = individualPersonalData;
                        break;
                    case 4:
                        individualPerson.phoneNumber = individualPersonalData;
                        break;
                    case 5:
                        individualPerson.eMail = individualPersonalData;
                        break;
                    case 6:
                        individualPerson.adress = individualPersonalData;
                        break;
                    }
                    individualPersonalData = "";
                    singlePersonNumber ++;
                }
            }
            singlePerson.push_back(individualPerson);
        }
    }
    DatabaseContact.close();
}

void ExportContactIntoFile (vector <Person> &singlePerson )
{
    fstream DatabaseContact;
    DatabaseContact.open("Kontakty.txt",ios :: out | ios :: app);
    if (DatabaseContact.good() == true)
    {
        for (auto index = 0; index < singlePerson.size(); index ++)
        {
            DatabaseContact << singlePerson[index].contactId + "|" + singlePerson[index].name + "|" + singlePerson[index].lastName
                           + "|" + singlePerson[index].phoneNumber + "|" + singlePerson[index].eMail
                           + "|" + singlePerson[index].adress + "|";
            DatabaseContact << endl;

        }
    DatabaseContact.close();
    }
    cout << "Dodano nowy kontakt" << endl;
    Sleep(1000);
}

void AddNewContact (vector<Person>& singlePerson)
{
    system("cls");
    cout << ">>>DODAJ NOWY KONTAKT<<<" << endl;
    cout << "************************" << endl;

    ofstream DatabaseContact( "Kontakty.txt" );
    Person individualPerson;
    string name, lastName, phoneNumber, eMail, adress;
    int contactNumber = ReturnLastContactNumber(singlePerson)+1;
    string IdNumber = intToString(contactNumber);
    cout << "Podaj imie: ";
    cin >> name;
    cout << "Podaj nazwisko: ";
    cin >> lastName;
    cout << "Podaj numer telefonu: ";
    cin >> phoneNumber;
    cout << "Podaj adres e-mail: ";
    cin >> eMail;
    cout << "Podaj adres: ";
    cin.ignore();
    getline(cin, adress);

    individualPerson.contactId = IdNumber;
    individualPerson.name = name;
    individualPerson.lastName = lastName;
    individualPerson.phoneNumber = phoneNumber;
    individualPerson.eMail = eMail;
    individualPerson.adress = adress;

    singlePerson.push_back(individualPerson);

    ExportContactIntoFile(singlePerson);
}

void SearchByName (vector <Person> & singlePerson, string nameToSearch)
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO IMIENIU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    cout << "Podaj imie: " << endl;
    cin >> nameToSearch;
    for (auto index = 0; index < singlePerson.size(); index ++)
    {
        if (singlePerson[index].name == nameToSearch)
        {
            cout << singlePerson[index].name << " " << singlePerson[index].lastName << " " << endl;
            cout << singlePerson[index].phoneNumber << " " << singlePerson[index].eMail << " " << endl;
            cout << singlePerson[index].adress << " " << endl;
        }
    }
    system("pause");
}

void SearchByLastName (vector <Person> & singlePerson, string lastNameToSearch)
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO NAZWISKU<<<" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    cout << "Podaj nazwisko: " << endl;
    cin >> lastNameToSearch;
    for (auto index = 0; index < singlePerson.size(); index ++)
    {
        if (singlePerson[index].lastName == lastNameToSearch)
        {
            cout << singlePerson[index].name << " " << singlePerson[index].lastName << " " << endl;
            cout << singlePerson[index].phoneNumber << " " << singlePerson[index].eMail << " " << endl;
            cout << singlePerson[index].adress << " " << endl;
        }
    }
    system("pause");
}

void SearchForAContact (vector <Person> &singlePerson)
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
            {
                SearchByName (singlePerson, nameToSearch);
                break;
            }

            case 2:
            {
                SearchByLastName (singlePerson, lastNameToSearch);
                break;
            }

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

void ViewAllContacts (vector <Person> &singlePerson)
{
    system("cls");
    cout << ">>>LISTA WSZYSTKICH KONTAKTOW<<<" << endl;
    cout << "********************************" << endl;

    for (auto index = 0; index < singlePerson.size(); index ++)
    {
        cout << singlePerson[index].contactId << endl;
        cout << singlePerson[index].name << " " << singlePerson[index].lastName << " " << endl;
        cout << singlePerson[index].phoneNumber << " " << singlePerson[index].eMail << " " << endl;
        cout << singlePerson[index].adress << " " << endl;
    }
    system("pause");
}

void updateDatabaseContactFile(vector <Person> &singlePerson)
{
  fstream DatabaseContact;
        DatabaseContact.open("Kontakty.txt",ios::out);
        if (DatabaseContact.good() == true)
        {
            for(auto index = 0; index < singlePerson.size(); index ++)
            {
                DatabaseContact << singlePerson[index].contactId + "|" + singlePerson[index].name + "|" + singlePerson[index].lastName
                             + "|" + singlePerson[index].phoneNumber + "|" + singlePerson[index].eMail
                             + "|" + singlePerson[index].adress + "|";
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

void ContactEdition(vector <Person> &singlePerson)
{
    system("cls");
    cout << ">>>EDYCJA WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*******************************" << endl;
    cout << endl;

    string newPhoneNumber, newEmail, newAdress;
    int userChoice = 0;
    int contactNumberToBeChanged = 0;
    cout<< "Podaj numer kontaktu, ktory chcesz edytowac: ";
    cin>> contactNumberToBeChanged;
    int positionInVector = FindPositionInVector(singlePerson, contactNumberToBeChanged);
    if ((checkIfContactExists(singlePerson, contactNumberToBeChanged) == true ))
    {
        for(auto index = 0; index < singlePerson.size(); index ++)
        {
            if (singlePerson[index].contactId == intToString(contactNumberToBeChanged))
            {
                cout << singlePerson[index].name << " " << singlePerson[index].lastName << " " << endl;
                cout << singlePerson[index].phoneNumber << " " << singlePerson[index].eMail << " " << endl;
                cout << singlePerson[index].adress << " " << endl;
            }
        }
        cout << "Wybierz dane do zmiany: " << endl;
        cout << "1. Numer telefonu" << endl;
        cout << "2. Adres e-mail" << endl;
        cout << "3. Adres zamieszkania" << endl;
        cout << "4. Powrot do Menu Glownego" << endl;
        cin >> userChoice;
        switch(userChoice)
        {
        case 1:
        {
            cout << "Podaj nowy numer telefonu: ";
            cin.ignore();
            getline(cin, newPhoneNumber);
            singlePerson[positionInVector].phoneNumber = newPhoneNumber;
        }
        break;

        case 2:
        {
            cout << "Podaj nowy adres mailowy: ";
            cin >> newEmail;
            singlePerson[positionInVector].eMail = newEmail;
        }
        break;

        case 3:
        {
            cout << "Podaj nowy adres zamieszkania: ";
            cin.ignore();
            getline(cin, newAdress);
            singlePerson[positionInVector].adress = newAdress;
        }
        break;

        case 4:
            break;
        }
        updateDatabaseContactFile(singlePerson);
    }
    else
    {
        cout<< "Kontakt o takim numerze ID nie istnieje !" <<endl;
        Sleep(2000);
    }
}

void RemoveContact(vector <Person> &singlePerson)
{
    system("cls");
    cout << ">>>USUWANIE WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    int contactNumberToRemove = 0;
    char userAccept;
    cout << "Podaj numer ID kontaktu, ktory chcesz usunac: ";
    cin >> contactNumberToRemove;
    if ((checkIfContactExists(singlePerson, contactNumberToRemove)) == true)
    {
        for (auto index = 0; index != singlePerson.size(); index ++ )
        {
            if (intToString(contactNumberToRemove) == singlePerson[index].contactId)
            {
                cout << singlePerson[index].name << " " << endl;
                cout << singlePerson[index].lastName << " " << endl;
                cout << singlePerson[index].phoneNumber << " " << endl;
                cout << singlePerson[index].eMail << " " << endl;
                cout << singlePerson[index].adress << " " << endl;

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
                    system("pause");
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
        if(fileExists("U¿ytkownicy.txt"))
        {
            //ImportAllUsers (singleUser);
        }

        if (loggedUserId == 0)
        {
            system("cls");
            cout << "\t**********************************************" << endl;
            cout << "\t>>>>>>>>>>> KSIAZKA ADRESOWA <<<<<<<<<<<<<" << endl;
            cout << "\t**********************************************" << endl << endl;
            cout << "\t************ 1.REJESTRACJA ************" << endl;
            cout << "\t************* 2.LOGOWANIE **************" << endl;
            cout << "\t************** 3.WYJSCIE ********" << endl;
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
                //LoggTheUserIn (singleUser)
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

            vector <Person> singlePerson;

            if(fileExists("Kontakty.txt"))
            {
                ImportAllContacts(singlePerson);
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
            cout << "\t************** 6.ZAKONCZ *********************" << endl;
            cout << endl;
            cout << "Prosze wybrac opcje ==> ";
            int userSelect;
            cin >> userSelect;


            switch (userSelect)
            {
            case 1:
            {
                AddNewContact(singlePerson);
            }
            break;
            case 2:
            {
                if (singlePerson.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    system("pause");
                }
                else SearchForAContact (singlePerson);
            }
            break;

            case 3:
            {
                if (singlePerson.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    system("pause");
                }
                else ViewAllContacts (singlePerson);
            }
            break;

            case 4:
            {
                if (singlePerson.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    system("pause");
                }
                else  ContactEdition(singlePerson);
            }
            break;

            case 5:
            {
                if (singlePerson.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    system("pause");
                }
                else RemoveContact (singlePerson);
            }
            break;

            case 6:
            {
                cout << "Nastapi zamkniecie programu...";
                Sleep(1500);
                return 0;
            }
            }
        }
    }
}
