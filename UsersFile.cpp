#include <iostream>
#include "Users.h"
#include "auxiliaryMethods.h"
#include "UsersFile.h"
#include <conio.h>
#include <stdio.h>

vector<User> UsersFile::ImportAllUsers()
{
    User individualUser;
    vector<User> Users;
    string personalUserData;
    int lineNumber = 1;
    ifstream usersFileName;
    usersFileName.open(getFileName().c_str(), ios::in);

    if (usersFileName.good() == true)
    {
        while(getline(usersFileName,personalUserData,'|'))
        {
            if (lineNumber == 1)
                individualUser.setId(auxiliaryMethods::stringToInt(personalUserData));
            else if (lineNumber == 2)
                individualUser.setName(personalUserData);
            else
                individualUser.setPassword(personalUserData);
            if (lineNumber == 3)
            {
                Users.push_back(individualUser);
                lineNumber = 0;
            }
            lineNumber ++;
        }
    }
    usersFileName.close();
    return Users;
}

void UsersFile::ExportNewUser(User singleUser)
{
    ofstream usersFileName;
    usersFileName.open(getFileName().c_str(), ios::out|ios::app);
    if (usersFileName.good() == true)
    {
            usersFileName << singleUser.getId() << "|";
            usersFileName << singleUser.getName() << "|";
            usersFileName << singleUser.getPassword() << "|";
            usersFileName <<endl;

        usersFileName.close();
        cout << endl;
        cout << auxiliaryMethods::PL("Dodano nowego użytkownika.") <<endl;
        Sleep(1500);
    }
    else
    {
        cout<< "Nie odnaleziono pliku!" <<endl;
        Sleep(1500);
    }
}
void UsersFile::ChangePasswordInFile(User loggedInUser)
{
    ifstream inputFile(getFileName().c_str());
    ofstream outputFile;
    outputFile.open("Uzytkownicy_tmp", ios::out | ios::app);

    string singleLine = "", subLine = "";
    if (inputFile.good() == true)
    {
        while(getline(inputFile, singleLine))
        {
            int index = 0;
            while(singleLine[index] != '|')
            {
                subLine += singleLine[index];
                index ++;
            }
            if (auxiliaryMethods::stringToInt(subLine) == loggedInUser.getId())
                {
                    outputFile << loggedInUser.getId() << "|";
                    outputFile << loggedInUser.getName() << "|";
                    outputFile << loggedInUser.getPassword() << "|" << endl;
                }
            else outputFile << singleLine << endl;
        }
        outputFile.close();
        inputFile.close();
        remove(getFileName().c_str());
        rename("Uzytkownicy_tmp", getFileName().c_str());
    }
    else
    {
        cout << "Program napotkal blad. Nie mozna otworzyc pliku.";
        outputFile.close();
        remove("Uzytkownicy_tmp.txt");
    }
}

