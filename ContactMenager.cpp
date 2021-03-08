#include <iostream>
#include "ContactMenager.h"
#include "auxiliaryMethods.h"

using namespace std;

void ContactMenager::AddNewContact()
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
    cout << auxiliaryMethods::PL("Wcisnij dowolny klawisz aby kontynuowac...");
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
    cout << auxiliaryMethods::PL("Wcisnij dowolny klawisz aby kontynuowac...");
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
    cout << auxiliaryMethods::PL("Wcisnij dowolny klawisz aby kontynuowac...");
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
    bool checkIfContactExists = false;
    system("cls");
    cout << ">>>EDYCJA WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    if (!singleContact.empty())
    {
        int contactNumberToBeChanged = 0;
        cout << auxiliaryMethods::PL("Podaj ID kontaktu, który chcesz edytowac: ") << endl;
        cin >> contactNumberToBeChanged;
        for(auto itr = singleContact.begin(); itr != singleContact.end(); itr ++ )
        {
            if(itr -> getContactId() == contactNumberToBeChanged)
            {
                checkIfContactExists = true;
                ShowContact(*itr);
                cout << endl;
                cout << "Wybierz dane do zmiany: " << endl;
                cout << "1. Numer telefonu" << endl;
                cout << "2. Adres e-mail" << endl;
                cout << "3. Adres zamieszkania" << endl;
                char userChoice = auxiliaryMethods::loadInput();
                switch(userChoice)
                {
                case '1':
                    while (true)
                    {
                        string newPhoneNumber = "";
                        cout << "Podaj nowy numer telefonu: ";
                        newPhoneNumber = auxiliaryMethods::loadInputLine();
                        if (auxiliaryMethods::isPhoneNumberValid(newPhoneNumber) == true)
                        {
                            itr -> setContactPhoneNumber(newPhoneNumber);
                            break;
                        }
                        else cout << "Podales niewlasciwy numer telefonu. Sproboj jeszcze raz." << endl;
                    }
                break;

                case '2':
                    while (true)
                    {
                        string newEmail = "";
                        cout << "Podaj nowy adres e-mail: ";
                        newEmail = auxiliaryMethods::loadInputLine();
                        if (auxiliaryMethods::isPhoneNumberValid(newEmail) == true)
                        {
                            itr -> setContactEmail(newEmail);
                            break;
                        }
                        else cout << "Podales niewlasciwy numer telefonu. Sproboj jeszcze raz." << endl;
                    }
                break;

                case '3':
                    cout << "Podaj nowy adres (ulica, kod pocztowy, miasto): ";
                    itr -> setContactAddress(auxiliaryMethods::loadInputLine());
                break;
                }
                contactsFile.UpdateDatabaseContactFile(*itr);
                break;
            }
        }
        if (checkIfContactExists == false)
            cout << "Kontakt o podanym ID nie istnieje." << endl;
    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
    getch();
}

void ContactMenager::RemoveContact()
{
    int contactNumberToRemove = 0;
    bool checkIfContactExists = false;
    system("cls");
    cout << ">>>USUWANIE WYBRANEGO KONTAKTU<<<" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    if (!singleContact.empty())
    {
        cout << auxiliaryMethods::PL("Podaj numer ID kontaktu, który chcesz usunac: ");
        cin >> contactNumberToRemove;
        for (auto itr = singleContact.begin(); itr != singleContact.end(); ++ itr)
        {
            if (itr -> getContactId() == contactNumberToRemove)
            {
                checkIfContactExists = true;
                ShowContact(*itr);
                cout << "Wcisnij 't' aby potwierdzic usuniecie wybranego adresata: ";
                char userAccept = auxiliaryMethods::loadInput();

                if (userAccept == 't' || 'T')
                {
                    singleContact.erase(itr);
                    contactsFile.RemoveContactFromFile(contactNumberToRemove);
                    break;
                }
                else
                    cout << "Wybrany kontakt nie zostal usuniety" << endl;
                    break;
            }
        }
        if (checkIfContactExists == false)
            cout << "Kontakt o podanym ID nie istnieje" << endl;
    }
    else cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
    getch();
}
