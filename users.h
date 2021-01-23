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
    public:
    string userId;
    string userName;
    string userPassword;

public:
    User(string userId, string userName, string userPassword);
    void setId(int newId);
    void setName(string newName);
    void setPassword(string newPassword);

    string getId();
    string getName();
    string getPassword();
};

#endif
