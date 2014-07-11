/* 
clabel.cpp
Len Isac
Last modified: November 21st, 2013
status: complete.
*/

#include "clabel.h"

using namespace cio;

// Constructors
CLabel::CLabel(const char *Str, int Row, int Col, int Len) : CField (Row, Col) 
{    
    // len is zero, allocate memory to store the string pointed to by Str and copies Str into _data
    if (Len == 0 ) 
    {       
        _data = new char[bio::strlen(Str) + 1];
        bio::strcpy(_data, Str);      
        //((char*)_data)[bio::strlen(Str)] = '\0';
        width(bio::strlen(Str));
    }

    // if Len > 0, allocate enough memory to store Len chars, and copy Len characters of Str.
    if (Len > 0) 
    {
        _data = new char[Len];
        bio::strncpy(_data, Str, Len);
        width(Len);
    }

}
CLabel::CLabel(int Row, int Col, int Len) : CField (Row, Col)
{ // allocate Len chars of memory for _data and set it to an empty string.
    _data = new char[Len];
    bio::strcpy(_data, "");
    width(Len);
}
// Copy Constructor
CLabel::CLabel(const CLabel& L)  : CField (L.row(),L.col()) 
{
    _data = new char[bio::strlen(L._data)];
    bio::strcpy(_data, L._data);
}

// Destructor
CLabel::~CLabel() 
{
    if ((char*)_data)
    {
        delete [] _data;
    }
}


// Methods
void CLabel::draw(int fn) 
{ // Makes direct call to console.display()
    console.display((char*)_data, absRow(), absCol(), width());
}

int CLabel::edit() 
{ // Calls draw() and returns 0
    draw();
    return 0;
}

bool CLabel::editable()const 
{
    return false;
}

void CLabel::set(const void* str) 
{
    int w = width(); // temporary integer for width to call width method just once within this scope/method.

    if (w > 0) 
    { 
        bio::strncpy(_data, str, w);
    }

    if (w == 0) 
    {
        if (_data)
        {
            delete [] _data;
        }
        _data = new char[bio::strlen(str) + 1];
        bio::strcpy(_data, str);
    }
}
