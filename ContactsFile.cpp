#include <iostream>
#include "Contacts.h"
#include "ContactMenager.h"
#include "auxiliaryMethods.h"
#include "ContactsFile.h"

using namespace std;

vector<Contact> ContactsFile::ImportContactsForLoggedUser (int loggedUserId)
{
    Contact singleContact;
    vector<Contact> contacts;
    string personalData = "";
    string lastContactPersonalData = "";
    fstream contactsFile;
    contactsFile.open(getFileName().c_str(), ios :: in);

    if (contactsFile.good() == true)
    {
        while(getline(contactsFile, personalData))
        {
            if (CheckUserId(personalData) == loggedUserId)
            {
                singleContact = getSingleContactPersonalData(personalData, lastContactId);
                contacts.push_back(singleContact);
            }
            lastContactPersonalData = personalData;
        }
    contactsFile.close();
    }
    if (lastContactPersonalData != "")
    {
        lastContactId = setLastContactID(lastContactPersonalData);
    }
    return contacts;
}

Contact ContactsFile::getSingleContactPersonalData(string personalData, int lastContactId)
{
    Contact singleContact;
    string individualPersonalData = "";
    unsigned int singleContactNumber = 1;

    for (auto index = 0; index < personalData.length(); index ++)
    {
        if (personalData[index] != '|')
        {
            individualPersonalData += personalData[index];
        }
        else
        {
            switch(singleContactNumber)
            {
            case 1:
                singleContact.setContactId(auxiliaryMethods::stringToInt(individualPersonalData));
                break;
            case 2:
                singleContact.setUserId(auxiliaryMethods::stringToInt(individualPersonalData));
                break;
            case 3:
                singleContact.setContactName(individualPersonalData);
                break;
            case 4:
                singleContact.setContactLastName(individualPersonalData);
                break;
            case 5:
                singleContact.setContactPhoneNumber(individualPersonalData);
                break;
            case 6:
                singleContact.setContactEmail(individualPersonalData);
                break;
            case 7:
                singleContact.setContactAddress(individualPersonalData);
                break;
            }
            individualPersonalData = "";
            singleContactNumber ++;
        }
    }
    return singleContact;
}
void ContactsFile::ExportContactIntoFile (Contact contactForExport)
{
    fstream contactsFile;
    contactsFile.open(getFileName().c_str(),ios :: out | ios :: app);
    if (contactsFile.good() == true)
    {
            contactsFile << auxiliaryMethods::intToString(contactForExport.getContactId()) << "|";
            contactsFile << auxiliaryMethods::intToString(contactForExport.getUserId()) << "|";
            contactsFile << contactForExport.getContactName() << "|";
            contactsFile << contactForExport.getContactLastName() << "|";
            contactsFile << contactForExport.getContactPhoneNumber() << "|";
            contactsFile << contactForExport.getContactEmail() << "|";
            contactsFile << contactForExport.getContactAddress() << "|" << endl;

        contactsFile.close();
        lastContactId ++;
    }
    cout << "Dodano nowy kontakt" << endl;
    Sleep(1000);
}

void ContactsFile::UpdateDatabaseContactFile(Contact singleContactToEdit)
{
    string singleLine = "", subLine;
    ifstream inputFile(getFileName().c_str());
    ofstream outputFile;
    outputFile.open("Kontakty_tmp.txt", ios::out | ios::app);

    if(inputFile.good() == true)
    {
        while (getline(inputFile, singleLine))
        {
            subLine = "";
            int index = 0;
            while(singleLine[index] != '|')
            {
                subLine += singleLine[index];
                index ++;
            }
            if (auxiliaryMethods::stringToInt(subLine) == singleContactToEdit.getContactId())
            {
                outputFile<<singleContactToEdit.getContactId() << "|";
                outputFile<<singleContactToEdit.getUserId() << "|";
                outputFile<<singleContactToEdit.getContactName() << "|";
                outputFile<<singleContactToEdit.getContactLastName() << "|";
                outputFile<<singleContactToEdit.getContactPhoneNumber() << "|";
                outputFile<<singleContactToEdit.getContactEmail() << "|";
                outputFile<<singleContactToEdit.getContactAddress() << "|" << endl;
            }
            else outputFile << singleLine << endl;
        }
        outputFile.close();
        inputFile.close();
        remove(getFileName().c_str());
        rename("Kontakty_tmp.txt", getFileName().c_str());
        cout<<"Kontakt edytowany pomyslnie.";
    }
    else
    {
        cout<<"Nie mozna otworzyc pliku.";
        outputFile.close();
        remove("Kontakty_tmp.txt");
    }
}

void ContactsFile::RemoveContactFromFile(int contactIdToBeDeleted)
{
    ifstream inputFile(getFileName().c_str());
    ofstream outputFile;
    outputFile.open("Kontakty_tmp.txt", ios::out | ios::app);
    string singleLine = "";
    string subLine;

    if(inputFile.good() == true)
    {
        while (getline(inputFile, singleLine))
        {
            subLine = "";
            int index = 0;
            while(singleLine[index] != '|')
            {
                subLine += singleLine[index];
                index ++;
            }
            if(auxiliaryMethods::stringToInt(subLine) == contactIdToBeDeleted)
            continue;
            else
            {
                outputFile << singleLine << endl;
                lastContactId = auxiliaryMethods::stringToInt(subLine);
            }
        }
        outputFile.close();
        inputFile.close();
        remove(getFileName().c_str());
        rename("Kontakty_tmp.txt", getFileName().c_str());
        cout << "Wybrany kontakt zostal usuniety." << endl;
    }
    else
    {
        cout<<"Nie mozna otworzyc pliku.";
        outputFile.close();
        remove("Kontakty_tmp.txt");
    }
}

int ContactsFile::getLastContactID() const
{
    return lastContactId;
}

int ContactsFile::setLastContactID(string databaseLine)
{
    int currentLastContactId = auxiliaryMethods::extractIdNumber(databaseLine, 1);
    lastContactId = currentLastContactId;
    return lastContactId;
}

int ContactsFile::CheckUserId(string databaseLine)
{
    int userId = auxiliaryMethods::extractIdNumber(databaseLine, 2);
    return userId;
}
