#include <iostream>
#include "users.h"
#include "contacts.h"
#include "ContactMenager.h"
#include "UserMenager.h"
#include "auxiliaryMethods.h"

using namespace std;

int main()
{
    int loggedUserId = 0;

    while (true)
    {
        vector <User> singleUser;
        if(auxiliaryMethods::fileExists("Uzytkownicy.txt") == true)
        {
            UserMenager import;
            import.ImportAllUsers(singleUser);
        }

        if (loggedUserId == 0)
        {
            system("cls");
            cout << "\t******************************************" << endl;
            cout << auxiliaryMethods::PL("\t>>>>>>>>>>> KSI��KA ADRESOWA <<<<<<<<<<<<<") << endl;
            cout << "\t******************************************" << endl << endl;
            cout << "\t************ 1.REJESTRACJA ***************" << endl;
            cout << "\t************* 2.LOGOWANIE ****************" << endl;
            cout << auxiliaryMethods::PL("\t************** 3.WYJ�CIE *****************") << endl;
            cout << endl;
            cout << auxiliaryMethods::PL("Prosz� wybra� opcj� ==> ");
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
                    cout << auxiliaryMethods::PL("Brak zarejestrowanych u�ytkownik�w !");
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
                cout << auxiliaryMethods::PL("Nast�pi zamkni�cie programu...");
                Sleep(1500);
                exit(0);
            }
            break;
            }
        }
        else
        {
            vector <Contact> singleContact;

            if(auxiliaryMethods::fileExists("Kontakty.txt") == true)
            {
                ContactMenager import;
                import.ImportContactsForLoggedUser(singleContact, loggedUserId);
            }
            system("cls");
            cout << "\t**********************************************" << endl;
            cout << auxiliaryMethods::PL("\t>>>>>>>>>>>>>>> MENU G��WNE <<<<<<<<<<<<<") << endl;
            cout << "\t**********************************************" << endl << endl;
            cout << "\t************ 1.DODAJ NOWY KONTAKT ************" << endl;
            cout << "\t************ 2.WYSZUKAJ KONTAKT **************" << endl;
            cout << auxiliaryMethods::PL("\t******* 3.WY�WIETL WSZYSTKIE KONTAKTY ********") << endl;
            cout << "\t************ 4.EDYCJA KONTAKTU ***************" << endl;
            cout << auxiliaryMethods::PL("\t************* 5.USU� KONTAKT *****************") << endl;
            cout << auxiliaryMethods::PL("\t************* 6.ZMIANA HAS�A *****************") << endl;
            cout << "\t************** 7.WYLOGUJ *********************" << endl;
            cout << endl;
            cout << auxiliaryMethods::PL("Prosz� wybra� opcj� ==> ");
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
                    cout << auxiliaryMethods::PL("Ksi��ka adresowa jest pusta. Dodaj nowy kontakt") << endl;
                    cout << auxiliaryMethods::PL("Wci�nij dowolny klawisz aby kontynuowa�...");
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
                    cout << auxiliaryMethods::PL("Ksi��ka adresowa jest pusta. Dodaj nowy kontakt") << endl;
                    cout << auxiliaryMethods::PL("Wci�nij dowolny klawisz aby kontynuowa�...");
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
                    cout << auxiliaryMethods::PL("Ksi��ka adresowa jest pusta. Dodaj nowy kontakt") << endl;
                    cout << auxiliaryMethods::PL("Wci�nij dowolny klawisz aby kontynuowa�...");
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
                    cout << auxiliaryMethods::PL("Ksi��ka adresowa jest pusta. Dodaj nowy kontakt") << endl;
                    cout << auxiliaryMethods::PL("Wci�nij dowolny klawisz aby kontynuowa�...");
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
                cout << auxiliaryMethods::PL("Wylogowa�e� si�.");
                Sleep(1500);
                break;
            }
            }
        }
    }
}
