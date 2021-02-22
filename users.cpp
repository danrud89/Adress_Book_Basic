#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "users.h"
#include "auxiliaryMethods.h"

using namespace std;

void User::setId(unsigned int newId)
{
    userId = newId;
}
void User::setName(string newName)
{
    userName = newName;
}
void User::setPassword(string newPassword)
{
    userPassword = newPassword;
}
unsigned int User::getId() const
{
    return userId;
}
string User::getName() const
{
    return userName;
}
string User::getPassword() const
{
    return userPassword;
}
