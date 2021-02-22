#include <iostream>
#include "Menu.h"

using namespace std;

int main()
{
    MENU MainMenu("Uzytkownicy.txt", "Kontakty.txt");

    while (true)
    {
        if (MainMenu.CheckUserId() == false)
        {
            MainMenu.displayUserMenu();
            char userFirstSelection = auxiliaryMethods::loadInput();

            switch (userFirstSelection)
            {
            case '1':
            {
                MainMenu.RegisterNewUser();
            }
            break;
            case '2':
            {
                    MainMenu.LoggTheUserIn();
            }
            break;

            case '3':
            {
                cout << auxiliaryMethods::PL("Nast¹pi zamkniêcie programu...");
                Sleep(1500);
                exit(0);
            }
            break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
        else
        {
            MainMenu.displayLoggedUserMenu();

            char userSecondSelection = auxiliaryMethods::loadInput();

            switch (userSecondSelection)
            {
            case '1':
            {
                MainMenu.AddNewContact();
            }
            break;

            case '2':
            {
                MainMenu.SearchByName();
            }
            break;

             case '3':
            {
                MainMenu.SearchByLastName();
            }
            break;
            case '4':
            {
                    MainMenu.ViewAllContacts ();
            }
            break;
            case '5':
            {
                    MainMenu.ContactEdition();
            }
            break;
            case '6':
            {
                    MainMenu.RemoveContact ();
            }
            break;
            case '7':
            {
                MainMenu.ChangeUserPassword();
            }
            break;
            case '8':
            {
                MainMenu.CheckUserId() == false;
                cout << auxiliaryMethods::PL("Wylogowa3eo sie.");
                Sleep(1500);
                break;
            }
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
    }
}
