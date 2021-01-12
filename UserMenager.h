#ifndef USERMENAGER_H
#define USERMENAGER_H
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

class UserMenager
{
    public:
        vector <User> singleUser;
        int LoggTheUserIn (vector <User> &singleUser);
        string intToString(int IdNumber);
        bool fileExists (const string& fileName);
        void ImportAllUsers(vector <User> &singleUser);
        void RegisterNewUser(vector <User> &singleUser);
        void ExportNewUser (vector<User>& singleUser);
        void ChangeUserPassword (vector<User> &singleUser, int &loggedUserId);
};

#endif
