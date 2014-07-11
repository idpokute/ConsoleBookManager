/*
cbookdb.h
 
Sehui Park

Last Modified: December, 2nd, 2013

status: working

*/

#ifndef __PSH_CBOOKDB_H__
#define __PSH_CBOOKDB_H__

#include <iostream>
#include "cfilecontroller.h"
using namespace std;

struct Book
{
    char name[71];
    char author[71];
    char publisher[71];
    char releaseDate[11];
    unsigned long isbn;
    unsigned long rating;

    void display() {
        cout<<name<<" "<<author<<" "<<publisher<<" "<<releaseDate<<" "<<isbn<<" "<<rating<<endl;
    }
};

//----------------------------------------------------------------------------------------
// Desc: BookDatabase Controller
// Watch the cpp file, there are more description.
//---------------------------------------------------------------------------------------
class CBookDB {
    CFileController file;

public:
    CBookDB(const char* _fname);
    virtual ~CBookDB();

    Book GetBook();                                     // Get the bookdata 
    bool CursorNext();                                  // Change cursor position                                  
    bool CursorPrev();
    bool CursorLast();
    bool CursorFirst();
    bool CursorIndex( unsigned int _idx );
    void AddLastEmptyRecord();                         
    bool OverWriteRecord( unsigned int _idx, Book& _src );  // Save Book data at the indexed Book Slot, 
                                                            // when index is less 0, index is first
                                                            // when index is grater than number of total book, index is last
};

#endif