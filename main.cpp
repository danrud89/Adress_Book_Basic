#include <iostream>
#include "users.h"
#include "contacts.h"
#include "ContactMenager.h"
#include "UserMenager.h"


using namespace std;

int main()
{
    int loggedUserId = 0;

    while (true)
    {
        vector <User> singleUser;
        if(fileExists("Uzytkownicy.txt") == true)
        {
            UserMenager import;
            import.ImportAllUsers(singleUser);
        }

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
                UserMenager registration;
                registration.RegisterNewUser(singleUser);
            }
            break;
            case 2:
            {
                if (singleUser.empty() == true)
                {
                    cout << "Brak zarejestrowanych uzytkownikow !";
                    Sleep(2000);
                }
                else
                {
                    UserMenager login;
                    loggedUserId = login.LoggTheUserIn(singleUser);
                }

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

            if(fileExists("Kontakty.txt") == true)
            {
                ContactMenager import;
                import.ImportContactsForLoggedUser(singleContact, loggedUserId);
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
                {
                    ContactMenager adding;
                    adding.AddNewContact(singleContact, loggedUserId);
                }
                break;

            case 2:
            {
                if (singleContact.empty() == true)
                {
                    cout << "Ksiazka adresowa jest pusta. Dodaj nowy kontakt" << endl;
                    cout << "Wcisnij dowolny klawisz aby kontynuowac...";
                    getch();
                }
                else
                {
                    ContactMenager searching;
                    searching.SearchForAContact (singleContact);
                }
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
                else
                {
                    ContactMenager display;
                    display.ViewAllContacts (singleContact, loggedUserId);
                }
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
                else
                {
                    ContactMenager editing;
                    editing.ContactEdition(singleContact, loggedUserId);
                }
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
                else
                {
                    ContactMenager deleting;
                    deleting.RemoveContact (singleContact, loggedUserId);
                }
            }
            break;

            case 6:
                {
                    UserMenager changePassword;
                    changePassword.ChangeUserPassword(singleUser, loggedUserId);
                }
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
