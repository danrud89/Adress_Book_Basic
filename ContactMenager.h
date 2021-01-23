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

using namespace std;

class ContactMenager
{
    public:
        vector <Contact> singleContact;
        bool checkIfContactExists(vector <Contact> singleContact, int contactNumberToBeChanged);
        int FindPositionInVector (vector <Contact> singleContact, int contactNumberToBeChanged);
        int ReturnLastContactNumber (vector <Contact> singleContact);
        void ImportAllContacts (vector <Contact> &singleContact);
        void ImportContactsForLoggedUser (vector <Contact> &singleContact, int &loggedUserId);
        void ExportContactIntoFile (vector <Contact> &singleContactForExport );
        void AddNewContact (vector<Contact>& singleContact, int &loggedUserId);
        void SearchByName (vector <Contact> & singleContact, string nameToSearch);
        void SearchByLastName (vector <Contact> & singleContact, string lastNameToSearch);
        void SearchForAContact (vector <Contact> &singleContact);
        void ViewAllContacts (vector <Contact> &singleContact, int &loggedUserId);
        void updateDatabaseContactFile(vector <Contact> &singleContact);
        void ContactEdition(vector <Contact> &singleContact, int &loggedUserId);
        void RemoveContact(vector <Contact> &singleContact, int &loggedUserId);
};

#endif
