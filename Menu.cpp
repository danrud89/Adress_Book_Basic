#include <iostream>
#include "Users.h"
#include "Contacts.h"
#include "ContactMenager.h"
#include "UserMenager.h"
#include "auxiliaryMethods.h"
#include "Menu.h"

using namespace std;

void MENU::displayUserMenu()
{
            system("cls");
            cout << "\t******************************************" << endl;
            cout << auxiliaryMethods::PL("\t>>>>>>>>>>> KSIAZKA ADRESOWA <<<<<<<<<<<<<") << endl;
            cout << "\t******************************************" << endl << endl;
            cout << "\t************ 1.REJESTRACJA ***************" << endl;
            cout << "\t************* 2.LOGOWANIE ****************" << endl;
            cout << auxiliaryMethods::PL("\t************** 3.WYJSCIE *****************") << endl;
            cout << endl;
            cout << auxiliaryMethods::PL("Prosze wybrac opcje ==> ");

}
void MENU::displayLoggedUserMenu()
{
            system("cls");
            cout << "\t**********************************************" << endl;
            cout << auxiliaryMethods::PL("\t>>>>>>>>>>>>>>> MENU G£ÓWNE <<<<<<<<<<<<<") << endl;
            cout << "\t**********************************************" << endl << endl;
            cout << "\t************ 1.DODAJ NOWY KONTAKT ************" << endl;
            cout << "\t************ 2.WYSZUKAJ KONTAKT PO IMIENIU **************" << endl;
            cout << "\t************ 3.WYSZUKAJ KONTAKT PO NAZWISKU **************" << endl;
            cout << auxiliaryMethods::PL("\t******* 4.WYŒWIETL WSZYSTKIE KONTAKTY ********") << endl;
            cout << "\t************ 5.EDYCJA KONTAKTU ***************" << endl;
            cout << auxiliaryMethods::PL("\t************* 6.USUÑ KONTAKT *****************") << endl;
            cout << auxiliaryMethods::PL("\t************* 7.ZMIANA HAS£A *****************") << endl;
            cout << "\t************** 8.WYLOGUJ *********************" << endl;
            cout << endl;
            cout << auxiliaryMethods::PL("Proszê wybraæ opcjê ==> ");

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
