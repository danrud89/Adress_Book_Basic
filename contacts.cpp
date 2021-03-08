#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Contacts.h"
#include "auxiliaryMethods.h"
#include <ctype.h>

using namespace std;

void Contact::setContactId(unsigned int newId)
{
    if(newId > 0)
    contactId = newId;
}
void Contact::setUserId(unsigned int newUId )
{
    if(newUId > 0)
    userId = newUId;
}
void Contact::setContactName(string newName)
{
    contactName = newName;
}
void Contact::setContactLastName(string newLastName)
{
    contactLastName = newLastName;
}
void Contact::setContactPhoneNumber(string newPhoneNumber)
{
    contactPhoneNumber = newPhoneNumber;
}
void Contact::setContactEmail(string newEmail)
{
    contactEmail = newEmail;
}
void Contact::setContactAddress(string newAddress)
{
    contactAddress = newAddress;
}

unsigned int Contact::getContactId() const
{
    return contactId;
}
unsigned int Contact::getUserId() const
{
    return userId;
}
string Contact::getContactName() const
{
    return contactName;
}
string Contact::getContactLastName() const
{
    return contactLastName;
}
string Contact::getContactPhoneNumber() const
{
    return contactPhoneNumber;
}
string Contact::getContactEmail() const
{
    return contactEmail;
}
string Contact::getContactAddress() const
{
    return contactAddress;
}

