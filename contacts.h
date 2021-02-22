#ifndef CONTACTS_H
#define CONTACTS_H
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <conio.h>

using namespace std;

class Contact
{
    unsigned int contactId;
    unsigned int userId;
    string contactName;
    string contactLastName;
    string contactPhoneNumber;
    string contactEmail;
    string contactAddress;

    vector <Contact> singleContact;

    public:
    Contact(unsigned int contactId = 0, unsigned int userId = 0, string contactName = "", string contactLastName = "",
                 string contactPhoneNumber = "", string contactEmail = "" , string contactAddress = "")
{
    this -> contactId = contactId;
    this -> userId = userId;
    this -> contactName = contactName;
    this -> contactLastName = contactLastName;
    this -> contactPhoneNumber = contactPhoneNumber;
    this -> contactEmail = contactEmail;
    this -> contactAddress = contactAddress;
};

        void setContactId(unsigned int newId);
        void setUserId(unsigned int newUid );
        void setContactName(string newName);
        void setContactLastName(string newLastName);
        void setContactPhoneNumber(string newPhoneNumber);
        void setContactEmail(string newEmail);
        void setContactAddress(string newAddress);

        unsigned int getContactId()const;
        unsigned int getUserId()const;
        string getContactName()const;
        string getContactLastName()const;
        string getContactPhoneNumber()const;
        string getContactEmail()const;
        string getContactAddress()const;

};
#endif
