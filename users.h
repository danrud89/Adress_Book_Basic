#ifndef USERS_H
#define USERS_H
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

class User
{
    unsigned int userId;
    string userName;
    string userPassword;

    public:
    User(unsigned int userId = 0, string userName = "", string userPassword = "");
    void setId(unsigned int newId);
    void setName(string newName);
    void setPassword(string newPassword);

    unsigned int getId() const;
    string getName()const;
    string getPassword()const;
};

#endif
