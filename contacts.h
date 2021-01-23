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
    public:
    string contactId;
    string userId;
    string contactName;
    string contactLastName;
    string contactPhoneNumber;
    string contactEmail;
    string contactAddress;

    public:
    Contact(string contactId, string userId, string contactName, string contactLastName, string contactPhoneNumber,
            string contactEmail , string contactAddress );

    void setContactId(int newId);
    void setUserId(string );
    void setContactName(string newName);
    void setContactLastName(string newLastName);
    void setContactPhoneNumer(string newPhoneNumber);
    void setContactEmail(string newEmail);
    void setContactAddress(string newAddress);

    string getContactId();
    string getUserId();
    string getContactName();
    string getContactLastName();
    string getContactPhoneNumber();
    string getContactEmail();
    string getContactAddress();
};

#endif
