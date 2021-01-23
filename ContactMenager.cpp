#include <iostream>
#include "contacts.h"
#include "users.h"
#include "ContactMenager.h"
#include "auxiliaryMethods.h"

using namespace std;

Contact::Contact(string contactId, string userId, string contactName, string contactLastName,
                 string contactPhoneNumber, string contactEmail , string contactAddress)
{
    this -> contactId = contactId;
    this -> userId = userId;
    this -> contactName = contactName;
    this -> contactLastName = contactLastName;
    this -> contactPhoneNumber = contactPhoneNumber;
    this -> contactEmail = contactEmail;
    this -> contactAddress = contactAddress;
}

bool ContactMenager::checkIfContactExists(vector <Contact> singleContact, int contactNumberToBeChanged)
{
    vector <string> IdNumbersOnly;
    for(auto index = 0; index < singleContact.size(); index ++)
    {
        IdNumbersOnly.push_back(singleContact[index].contactId);
    }
    auto itr = find(IdNumbersOnly.begin(), IdNumbersOnly.end(), auxiliaryMethods::intToString(contactNumberToBeChanged));
    if (itr != IdNumbersOnly.end()) return true;
    else return false;
}

int ContactMenager::FindPositionInVector (vector <Contact> singleContact, int contactNumberToBeChanged)
{
    vector <string> IdNumbersOnly;
    for(auto index = 0; index < singleContact.size(); index ++)
    {
        IdNumbersOnly.push_back(singleContact[index].contactId);
    }

    for (auto index = 0; index < IdNumbersOnly.size(); index ++)
    {
        if (IdNumbersOnly[index] == auxiliaryMethods::intToString(contactNumberToBeChanged))
            return index;
    }
}

void ContactMenager::ImportAllContacts (vector <Contact> &singleContact)
{
    vector <string> individualContact;
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
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 2:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 3:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 4:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 5:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 6:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 7:
                        individualContact.push_back(individualPersonalData);
                        break;
                    }
                    individualPersonalData = "";
                    singleContactNumber ++;
                }
            }
            singleContact.push_back(Contact(individualContact[0], individualContact[1],
                                            individualContact[2], individualContact[3],
                                            individualContact[4], individualContact[5],
                                            individualContact[6]));
            individualContact.clear();
        }
    }
    DatabaseContact.close();
}

int ContactMenager::ReturnLastContactNumber (vector <Contact> singleContact)
{
    ContactMenager import;
    import.ImportAllContacts(singleContact);
    if (singleContact.empty() == true )
        return 0;
    else
    {
        auto lastContactNumber = singleContact.size() - 1;
        return atoi(singleContact[lastContactNumber].contactId.c_str());
    }
}

void ContactMenager::ImportContactsForLoggedUser (vector <Contact> &singleContact, int &loggedUserId)
{
    vector <string> individualContact;
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
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 2:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 3:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 4:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 5:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 6:
                        individualContact.push_back(individualPersonalData);
                        break;
                    case 7:
                        individualContact.push_back(individualPersonalData);
                        break;
                    }
                    individualPersonalData = "";
                    singleContactNumber ++;
                }
            }
            if (individualContact[1] == auxiliaryMethods::intToString(loggedUserId))
            {
                singleContact.push_back(Contact(individualContact[0], individualContact[1],
                                                individualContact[2], individualContact[3],
                                                individualContact[4], individualContact[5],
                                                individualContact[6]));
                individualContact.clear();
            }
            else continue;
        }
    }
    DatabaseContact.close();
}

void ContactMenager::ExportContactIntoFile (vector <Contact> &singleContactForExport )
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

void ContactMenager::AddNewContact (vector<Contact>& singleContact, int &loggedUserId)
{
    system("cls");
    cout << ">>>DODAJ NOWY KONTAKT<<<" << endl;
    cout << "************************" << endl;

    if(auxiliaryMethods::fileExists("Kontakty.txt") == false) ofstream DatabaseContact( "Kontakty.txt" );
    else
    {
        vector<Contact> singleContactForExport;
        string contactName, contactLastName, contactPhoneNumber, contactEmail, contactAddress;
        ContactMenager lastNumber;
        int contactNumber = lastNumber.ReturnLastContactNumber(singleContact)+1;
        string contactId = auxiliaryMethods::intToString(contactNumber);
        string userId = auxiliaryMethods::intToString(loggedUserId);
        cout << auxiliaryMethods::PL("Podaj imiê: ");
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

        singleContactForExport.push_back(Contact(contactId, userId, contactName, contactLastName, contactPhoneNumber,
                                                 contactEmail, contactAddress));

        ContactMenager exportContact;
        exportContact.ExportContactIntoFile(singleContactForExport);
        singleContactForExport.clear();
    }
}

void ContactMenager::SearchByName (vector <Contact> & singleContact, string nameToSearch)
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO IMIENIU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    cout << auxiliaryMethods::PL("Podaj imiê: ");
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
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}

void ContactMenager::SearchByLastName (vector <Contact> & singleContact, string lastNameToSearch)
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
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}

void ContactMenager::SearchForAContact (vector <Contact> &singleContact)
{
    string nameToSearch, lastNameToSearch;
    int userSelect;

    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT<<<" << endl;
    cout << "**********************" << endl;
    cout << endl;
    cout << "1. >>Wyszukaj po imieniu<<" << endl;
    cout << "2. >>Wyszukaj po nazwisku<<" << endl;
    cout << auxiliaryMethods::PL("3. >>Powrót do Menu G³ównego<<") << endl;
    cout << endl;
    cout << auxiliaryMethods::PL("Proszê wybraæ opcjê: ") << endl;
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
        cout << auxiliaryMethods::PL("Poda³eœ niew³aœciw¹ cyfrê. Spróbuj jeszcze raz.") << endl;
        Sleep(1500);
    }
}

void ContactMenager::ViewAllContacts (vector <Contact> &singleContact, int &loggedUserId)
{
    system("cls");
    cout << auxiliaryMethods::PL(">>>LISTA WSZYSTKICH KONTAKTÓW<<<") << endl;
    cout << "********************************" << endl;

    for (auto index = 0; index < singleContact.size(); index ++)
    {
        if (singleContact[index].userId == auxiliaryMethods::intToString(loggedUserId))
        {
         cout << singleContact[index].contactId << endl;
         cout << singleContact[index].contactName << " " << singleContact[index].contactLastName << " " << endl;
         cout << singleContact[index].contactPhoneNumber << " " << singleContact[index].contactEmail << " " << endl;
         cout << singleContact[index].contactAddress << " " << endl;
        }
    }
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}

void ContactMenager::updateDatabaseContactFile(vector <Contact> &singleContact)
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
        cout << auxiliaryMethods::PL("Kontakt zosta³ zmieniony!") << endl;
        Sleep(1500);
    }
    else
    {
        cout << auxiliaryMethods::PL("Nie uda³o siê zmieniæ kontaktu!") << endl;
        Sleep(1500);
    }
}

void ContactMenager::ContactEdition(vector <Contact> &singleContact, int &loggedUserId)
{
    singleContact.clear();
    ContactMenager import;
    import.ImportAllContacts(singleContact);
    ViewAllContacts(singleContact,loggedUserId);
    cout << endl;
    string newPhoneNumber, newEmail, newAdress;
    int contactNumberToBeChanged = 0;
    cout << auxiliaryMethods::PL("Podaj numer kontaktu, który chcesz edytowaæ: ") << endl;
    cin >> contactNumberToBeChanged;
    ContactMenager getPosition;
    ContactMenager existance;
    int positionInVector = getPosition.FindPositionInVector(singleContact, contactNumberToBeChanged);
    if ((existance.checkIfContactExists(singleContact, contactNumberToBeChanged) == true ) && (singleContact[positionInVector].userId == auxiliaryMethods::intToString(loggedUserId)))
    {
        for(auto index = 0; index < singleContact.size(); index ++)
        {
            if (singleContact[index].contactId == auxiliaryMethods::intToString(contactNumberToBeChanged))
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
            cout << "Podaj nowy adres e-mail: ";
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
        ContactMenager update;
        update.updateDatabaseContactFile(singleContact);
    }
    else
    {
        cout<< "Kontakt o takim numerze ID nie istnieje !" <<endl;
        Sleep(2000);
    }
}

void ContactMenager::RemoveContact(vector <Contact> &singleContact, int &loggedUserId)
{
    ViewAllContacts(singleContact, loggedUserId);
    system("cls");
    cout << ">>>USUWANIE WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    int contactNumberToRemove = 0;
    char userAccept;
    cout << auxiliaryMethods::PL("Podaj numer ID kontaktu, który chcesz usun¹æ: ");
    cin >> contactNumberToRemove;
    ContactMenager existance;
    if (((existance.checkIfContactExists(singleContact, contactNumberToRemove)) == true) && (singleContact[contactNumberToRemove-1].userId == auxiliaryMethods::intToString(loggedUserId)))
    {
        for (auto index = 0; index != singleContact.size(); index ++ )
        {
            if (auxiliaryMethods::intToString(contactNumberToRemove) == singleContact[index].contactId)
            {
                cout << singleContact[index].contactName << " " << endl;
                cout << singleContact[index].contactLastName << " " << endl;
                cout << singleContact[index].contactPhoneNumber << " " << endl;
                cout << singleContact[index].contactEmail << " " << endl;
                cout << singleContact[index].contactAddress << " " << endl;

                cout << auxiliaryMethods::PL("Wciœnij 't' aby potwierdziæ usuniêcie wybranego adresata: ");
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
                    cout << auxiliaryMethods::PL("Wybrany kontakt zosta³ usuniêty!") << endl;
                    Sleep(2000);
                }
                else
                {
                    cout << auxiliaryMethods::PL("Wybrany kontakt nie zosta³ usuniêty") << endl;
                    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
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
