#ifndef DATABASEFILE_H
#define DATABASEFILE_H

#include "Users.h"
#include "auxiliaryMethods.h"
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

class DatabaseFile
{
    private:
        const string DATA_FILENAME;
    public:
        DatabaseFile (string filename): DATA_FILENAME (filename) {};
        string getFileName();
};

#endif
