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

    Contact(string id, string uid, string name, string surname, string phone,
            string email , string address );
};

#endif
