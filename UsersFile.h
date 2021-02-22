#ifndef USERSFILE_H
#define USERSFILE_H
#include "Users.h"
#include "auxiliaryMethods.h"
#include "DatabaseFile.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <conio.h>

using namespace std;

class UsersFile : public DatabaseFile
{
    public:
        UsersFile(string filename) : DatabaseFile(filename) {};
        vector<User> ImportAllUsers();
        void ExportNewUser (User user);
        void ChangePasswordInFile(User user);
};

#endif
