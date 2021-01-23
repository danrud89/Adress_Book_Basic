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

string auxiliaryMethods::intToString(int IdNumber)
{
    ostringstream ss;
    ss << IdNumber;
    return  ss.str();
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
