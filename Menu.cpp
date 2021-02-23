#include <iostream>
#include "Users.h"
#include "Contacts.h"
#include "ContactMenager.h"
#include "UserMenager.h"
#include "auxiliaryMethods.h"
#include "Menu.h"

using namespace std;

char MENU::displayUserMenu()
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
            char userFirstSelection = auxiliaryMethods::loadInput();
            return userFirstSelection;

}
char MENU::displayLoggedUserMenu()
{
            system("cls");
            cout << "\t**********************************************" << endl;
            cout << "\t>>>>>>>>>>>>>>> MENU GLOWNE <<<<<<<<<<<<<" << endl;
            cout << "\t**********************************************" << endl << endl;
            cout << "\t************ 1.DODAJ NOWY KONTAKT ************" << endl;
            cout << "\t************ 2.WYSZUKAJ KONTAKT PO IMIENIU **************" << endl;
            cout << "\t************ 3.WYSZUKAJ KONTAKT PO NAZWISKU **************" << endl;
            cout << "\t************ 4.WYSWIETL WSZYSTKIE KONTAKTY ********" << endl;
            cout << "\t************ 5.EDYCJA KONTAKTU ***************" << endl;
            cout << "\t************ 6.USUN KONTAKT *****************" << endl;
            cout << "\t************ 7.ZMIANA HASLA *****************" << endl;
            cout << "\t************ 8.WYLOGUJ *********************" << endl;
            cout << endl;
            cout << "Prosze wybrac opcje ==> ";
            char userSecondSelection = auxiliaryMethods::loadInput();
            return userSecondSelection;

}

bool MENU::CheckUserId()
{
    userMenager.CheckUserId();
}
int  MENU::LoggTheUserIn ()
{
    userMenager.LoggTheUserIn();
    if (userMenager.CheckUserId() == true)
        contactMenager = new ContactMenager(CONTACTS_FILE_NAME, userMenager.getLoggedInUserID());
}
void  MENU::RegisterNewUser()
{
    userMenager.RegisterNewUser();
}
void  MENU::ChangeUserPassword ()
{
    userMenager.ChangeUserPassword();
}
void  MENU::AddNewContact ()
{
    contactMenager->AddNewContact();
}
void  MENU::SearchByName ()
{
    contactMenager->SearchByName();
}
void  MENU::SearchByLastName ()
{
    contactMenager->SearchByLastName();
}
void  MENU::ViewAllContacts ()
{
    contactMenager->ViewAllContacts();
}
void  MENU::ContactEdition()
{
    contactMenager->ContactEdition();
}
void  MENU::RemoveContact()
{
    contactMenager->RemoveContact();
}
void MENU::LoggTheUserOut()
{
    userMenager.LoggTheUserOut();
    delete contactMenager;
    contactMenager = NULL;
}
