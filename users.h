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

    User(string id, string name, string password);
};

#endif
