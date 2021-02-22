#include <iostream>
#include "auxiliaryMethods.h"

using namespace std;

bool auxiliaryMethods::fileExists (const string& fileName)
{
    fstream Database;
    Database.open(fileName.c_str(), ios::in);
    if ( Database.is_open() )
    {
        Database.close();
        return true;
    }
    Database.close();
    return false;
}

string auxiliaryMethods::loadInputLine()
{
    string loadedLine = {};
    getline(cin, loadedLine);
    return loadedLine;
}

string auxiliaryMethods::intToString(int IdNumber)
{
    ostringstream ss;
    ss << IdNumber;
    return  ss.str();
}

int auxiliaryMethods::stringToInt(string number)
{
    int intNumber;
    istringstream ss(number);
    ss >> intNumber;
    return intNumber;
}

char auxiliaryMethods::loadInput()
{
    string input = "";
    char mark  = {0};
    cin.sync();

    while (true)
    {
        getline(cin, input);

        if (input.length() == 1)
        {
            mark = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return mark;
}

string auxiliaryMethods::PL (string singleMark)
{
    for( auto index = 0; index < singleMark.length(); index ++ ) {
        switch( singleMark[ index ] ) {
        case 'π':
            singleMark[ index ] = static_cast < char >( 165 );
            break;

        case 'Ê':
            singleMark[ index ] = static_cast < char >( 134 );
            break;

        case 'Í':
            singleMark[ index ] = static_cast < char >( 169 );
            break;

        case '≥':
            singleMark[ index ] = static_cast < char >( 136 );
            break;

        case 'Ò':
            singleMark[ index ] = static_cast < char >( 228 );
            break;

        case 'Û':
            singleMark[ index ] = static_cast < char >( 162 );
            break;

        case 'ú':
            singleMark[ index ] = static_cast < char >( 152 );
            break;

        case 'ü':
            singleMark[ index ] = static_cast < char >( 171 );
            break;

        case 'ø':
            singleMark[ index ] = static_cast < char >( 190 );
            break;

        case '•':
            singleMark[ index ] = static_cast < char >( 164 );
            break;

        case '∆':
            singleMark[ index ] = static_cast < char >( 143 );
            break;

        case ' ':
            singleMark[ index ] = static_cast < char >( 168 );
            break;

        case '£':
            singleMark[ index ] = static_cast < char >( 157 );
            break;

        case '—':
            singleMark[ index ] = static_cast < char >( 227 );
            break;

        case '”':
            singleMark[ index ] = static_cast < char >( 224 );
            break;

        case 'å':
            singleMark[ index ] = static_cast < char >( 151 );
            break;

        case 'è':
            singleMark[ index ] = static_cast < char >( 141 );
            break;

        case 'Ø':
            singleMark[ index ] = static_cast < char >( 189 );
            break;
        }
    }
    return singleMark;
}

int auxiliaryMethods::extractIdNumber(string databaseLine, int linePosition)
{
    string stringDigit = "";
    int intDigit = 0;

    unsigned int index = 1;
    unsigned int casePosition = 0;
    while(index <= linePosition)
    {
        if (databaseLine[casePosition] == '|')
        {
            index ++; casePosition ++;
        }
        else if (databaseLine[casePosition] != '|' && linePosition == index )
        {
                stringDigit += databaseLine[casePosition];
                casePosition ++;
        }
        else
                casePosition++;
    }
    intDigit = stringToInt(stringDigit);
    return intDigit;
}

bool auxiliaryMethods::isEmailValid (string eMail)
{
    if (eMail.find("@") != string::npos) return true;

    else return false;
}

bool auxiliaryMethods::isPhoneNumberValid(string phoneNumber)
{
    for (int index = 0; index < phoneNumber.length(); index ++)
    {
        if (!isdigit(phoneNumber[index])) return false;
        else return true;
    }
}
