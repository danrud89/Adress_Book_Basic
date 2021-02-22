#include <iostream>
#include "ContactMenager.h"
#include "auxiliaryMethods.h"

using namespace std;

void ContactMenager::AddNewContact ()
{
    system("cls");
    cout << ">>>DODAJ NOWY KONTAKT<<<" << endl;
    cout << "************************" << endl;

    Contact contact;
    contact = GetPersonalContactData();
    singleContact.push_back(contact);
    contactsFile.ExportContactIntoFile(contact);
}

void ContactMenager::SearchByName()
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO IMIENIU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    if(!singleContact.empty())
    {
        string nameToSearch;
        cout << auxiliaryMethods::PL("Podaj imie: ");
        cin >> nameToSearch;
        for (vector<Contact>::const_iterator itr = singleContact.begin(); itr != singleContact.end(); ++ itr)
        {
            if (nameToSearch == itr -> getContactName())
            {
                ShowContact(*itr);
            }
            else if (itr -> getContactName() != nameToSearch && itr == singleContact.end())
            {
                cout<<"W ksiazce adresowej nie ma uzytkownika o imieniu: " << nameToSearch << endl;
            }
        }
    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt." << endl;
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}

void ContactMenager::SearchByLastName ()
{
    system("cls");
    cout << ">>>WYSZUKAJ KONTAKT PO NAZWISKU<<<" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    if (!singleContact.empty())
    {
        string lastNameToSearch;
        cout << "Podaj nazwisko: ";
        cin >> lastNameToSearch;
        for (vector<Contact>::const_iterator itr = singleContact.begin(); itr != singleContact.end(); ++ itr )
        {
            if (itr -> getContactLastName() == lastNameToSearch)
            {
                ShowContact(*itr);
            }
            else if (itr -> getContactLastName() != lastNameToSearch && itr == singleContact.end())
            {
                cout<<"W ksiazce adresowej nie ma uzytkownika o nazwisku: " << lastNameToSearch << endl;
            }
        }
    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();

}
void ContactMenager::ShowContact(Contact contact)
{
    cout << contact.getContactId() << endl;
    cout << contact.getContactName() << " " << contact.getContactLastName() << " " << endl;
    cout << contact.getContactPhoneNumber() << " " << endl;
    cout << contact.getContactEmail() << " " << endl;
    cout << contact.getContactAddress() << " " << endl;
}

void ContactMenager::ViewAllContacts ()
{
    system("cls");
    cout << auxiliaryMethods::PL(">>>LISTA WSZYSTKICH KONTAKTÓW<<<") << endl;
    cout << "********************************" << endl;

    if (!singleContact.empty())
    {
        for (vector<Contact>::const_iterator itr = singleContact.begin(); itr != singleContact.end(); ++ itr)
        {
            ShowContact(*itr);
        }
    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}

Contact ContactMenager::GetPersonalContactData()
{
    Contact contact;
    string contactName, contactLastName, contactPhoneNumber, contactEmail, contactAddress;
    contact.setContactId(contactsFile.getLastContactID()+1);
    contact.setUserId(LOGGED_USER_ID);

    cout << auxiliaryMethods::PL("Podaj imie: ");
    contactName = auxiliaryMethods::loadInputLine();
    contact.setContactName(contactName);

    cout << "Podaj nazwisko: ";
    contactLastName = auxiliaryMethods::loadInputLine();
    contact.setContactLastName(contactLastName);

    cout << "Podaj numer telefonu: ";
    while (true)
    {
        contactPhoneNumber = auxiliaryMethods::loadInputLine();
        if (auxiliaryMethods::isPhoneNumberValid(contactPhoneNumber))
        {
            contact.setContactPhoneNumber(contactPhoneNumber);
            break;
        }
        else
        {
            cout << "Podales niewlasciwy numer telefonu. Sprobuj jeszcze raz: ";
        }
    }
    cout << "Podaj adres e-mail: ";
    while (true)
    {
       contactEmail = auxiliaryMethods::loadInputLine();
        if (auxiliaryMethods::isEmailValid(contactEmail))
        {
            contact.setContactEmail(contactEmail);
            break;
        }
        else
        {
            cout << "Podales niewlasciwy adres e-mail. Sprobuj jeszcze raz: ";
        }
    }
    cout << "Podaj adres (ulica, kod pocztowy, miasto): ";
    contactAddress = auxiliaryMethods::loadInputLine();
    contact.setContactAddress(contactAddress);

    return contact;
}

void ContactMenager::ContactEdition()
{
    system("cls");
    cout << ">>>EDYCJA WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    if (!singleContact.empty())
    {
        int contactNumberToBeChanged = 0;
        cout << auxiliaryMethods::PL("Podaj ID kontaktu, który chcesz edytowaæ: ") << endl;
        cin >> contactNumberToBeChanged;
        for(auto itr = singleContact.begin(); itr != singleContact.end(); ++ itr )
        {
            if(itr -> getContactId() == contactNumberToBeChanged)
            {
                ShowContact(*itr);
                cout << endl;
                cout << "Wybierz dane do zmiany: " << endl;
                cout << "1. Numer telefonu" << endl;
                cout << "2. Adres e-mail" << endl;
                cout << "3. Adres zamieszkania" << endl;
                cout << endl;

                int userChoice = 0;
                userChoice = auxiliaryMethods::loadInput();
                switch(userChoice)
                {
                case '1':
                {
                    cout << "Podaj nowy numer telefonu: ";
                    itr -> setContactPhoneNumber(auxiliaryMethods::loadInputLine());
                }
                break;
                case '2':
                {
                    cout << "Podaj nowy adres e-mail: ";
                    itr -> setContactEmail(auxiliaryMethods::loadInputLine());
                }
                break;
                case '3':
                {
                    cout << "Podaj nowy adres zamieszkania: ";
                    itr -> setContactAddress(auxiliaryMethods::loadInputLine());
                }
                break;
                }
                contactsFile.updateDatabaseContactFile(*itr);
                break;
            }
            else if(itr -> getContactId() != contactNumberToBeChanged && itr == singleContact.end())
            {
                cout<< "Kontakt o takim numerze ID nie istnieje !" <<endl;
                Sleep(2000);
            }
        }

    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}

void ContactMenager::RemoveContact()
{
    int contactNumberToRemove = 0;
    system("cls");
    cout << ">>>USUWANIE WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    bool contactExistance = false;
    if (!singleContact.empty())
    {
        cout << auxiliaryMethods::PL("Podaj numer ID kontaktu, który chcesz usun¹æ: ");
        cin >> contactNumberToRemove;
        for (auto itr = singleContact.begin(); itr != singleContact.end(); ++ itr)
        {
            if (itr -> getContactId() == contactNumberToRemove)
            {
                contactExistance = true;
                ShowContact(*itr);
                cout << auxiliaryMethods::PL("Wciœnij 't' aby potwierdziæ usuniêcie wybranego adresata: ");
                char userAccept = auxiliaryMethods::loadInput();

                if (userAccept == 't')
                {
                    singleContact.erase(itr);
                    contactsFile.RemoveContactFromFile(contactNumberToRemove);
                }
                else
                    cout << auxiliaryMethods::PL("Wybrany kontakt nie zosta³ usuniêty") << endl;
                    break;
            }
            else if (itr -> getContactId() != contactNumberToRemove && itr == singleContact.end())
            {
                cout<< "Kontakt o takim numerze ID nie istnieje !" <<endl;
                Sleep(2000);
            }
        }
    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
    cout << auxiliaryMethods::PL("Wciœnij dowolny klawisz aby kontynuowaæ...");
    getch();
}
