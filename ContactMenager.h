#ifndef CONTACTMENAGER_H
#define CONTACTMENAGER_H
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <conio.h>
#include "Contacts.h"
#include "DatabaseFile.h"
#include "ContactsFile.h"
#include "Users.h"
#include "UsersFile.h"

using namespace std;

class ContactMenager
{
    const int LOGGED_USER_ID;
    ContactsFile contactsFile;
    vector <Contact> singleContact;
    Contact GetPersonalContactData();
    void ShowContact(Contact contact);

    public:
        ContactMenager(string contactsFileName, int loggedUserId )
        : contactsFile(contactsFileName), LOGGED_USER_ID(loggedUserId)
        {
            singleContact = contactsFile.ImportContactsForLoggedUser(LOGGED_USER_ID);
        };
        void AddNewContact();
        void SearchByName();
        void SearchByLastName();
        void ViewAllContacts();
        void ContactEdition();
        void RemoveContact();
};

#endif
