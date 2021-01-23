#ifndef AUXILIARYMETHODS_H
#define AUXILIARYMETHODS_H
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

class auxiliaryMethods
{
    public :
    static string intToString(int IdNumber);
    static bool fileExists (const string& fileName);
    static string PL (string mark);

};

#endif
