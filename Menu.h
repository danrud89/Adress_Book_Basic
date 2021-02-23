#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <conio.h>
#include "Users.h"
#include "Contacts.h"
#include "ContactMenager.h"
#include "UserMenager.h"
#include "auxiliaryMethods.h"
#include "DatabaseFile.h"
#include "ContactsFile.h"
#include "UsersFile.h"

using namespace std;

class MENU
{
    UserMenager userMenager;
    ContactMenager *contactMenager;
    const string CONTACTS_FILE_NAME;

    public:
        MENU(string usersFileName, string contactsFileName)
        : userMenager(usersFileName), CONTACTS_FILE_NAME(contactsFileName)
        {
            contactMenager = NULL;
        }
        ~MENU()
        {
            delete contactMenager;
            contactMenager = NULL;
        }
        char displayUserMenu();
        char displayLoggedUserMenu();
        bool CheckUserId();
        int LoggTheUserIn ();
        void RegisterNewUser();
        void ChangeUserPassword ();
        void AddNewContact ();
        void SearchByName ();
        void SearchByLastName ();
        void ViewAllContacts ();
        void ContactEdition();
        void RemoveContact();
        void LoggTheUserOut();

};

#endif
