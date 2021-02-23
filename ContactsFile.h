#ifndef CONTACTSFILE_H
#define CONTACTSFILE_H
#include "Contacts.h"
#include "auxiliaryMethods.h"
#include "DatabaseFile.h"
#include "ContactMenager.h"
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

class ContactsFile : public DatabaseFile
{
    int lastContactId;
    Contact getSingleContactPersonalData(string personalData, int lastContactId);
    public:
        ContactsFile(string contactsFileName): DatabaseFile(contactsFileName)
        {
          lastContactId = 0;
        };
        vector<Contact> ImportContactsForLoggedUser (int loggedUserId);

        void ExportContactIntoFile (Contact singleContactForExport );
        void updateDatabaseContactFile(Contact singleContact);
        int ReturnLastContactNumber (Contact singleContactToEdit);
        void RemoveContactFromFile(int contactIdToDeleted);
        int setLastContactID(string dataLine);
        int getLastContactID();
        int CheckUserId(string dataLine);
};

#endif
