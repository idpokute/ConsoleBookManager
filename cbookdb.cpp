/*
cbookdb.cpp
 
Sehui Park

Last Modified: December, 2nd, 2013

status: working

*/
#include "cbookdb.h"
#include "cfilecontroller.h"

//----------------------------------------------------------------------------------------------
// Constructor
// Desc : 
//----------------------------------------------------------------------------------------------
CBookDB::CBookDB(const char* _fname) {
    file.Open(_fname);
}

//----------------------------------------------------------------------------------------------
// destructor
// Desc : 
//----------------------------------------------------------------------------------------------
CBookDB::~CBookDB() {
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Get book data which cursor is located
//        Cursor doesn't move after reading data
//----------------------------------------------------------------------------------------------
Book CBookDB::GetBook() {
    Book ret;
    int prev = file.CurPosition();      // save the data cursor
    file.Get(&ret, sizeof(Book));
    file.Position( prev );              // load the data cursor
    return ret;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Change cursor to next book data
//----------------------------------------------------------------------------------------------
bool CBookDB::CursorNext() {
    int prev = file.CurPosition();
    file.Position( file.CurPosition() + sizeof(Book) );

    if( file.IsEnd() ){
        file.Position(prev);
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Change cursor to prev book data
//----------------------------------------------------------------------------------------------
bool CBookDB::CursorPrev() {
    if( !file.Position(file.CurPosition() - sizeof(Book)) ){
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Change cursor to last
//----------------------------------------------------------------------------------------------
bool CBookDB::CursorLast() {
    file.Position(0, ios_base::end);
    CursorPrev();
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Change cursor to first
//----------------------------------------------------------------------------------------------
bool CBookDB::CursorFirst() {
    file.Position(0, ios_base::beg);
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Change cursor by index. If 
//        index is less than 0 or grater than number of total book, it doesn't change cursor
//----------------------------------------------------------------------------------------------
bool CBookDB::CursorIndex( unsigned int _idx ) {

    file.Position( sizeof(Book)* _idx );

    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Add empty Record 
//        Cursor doesn't change
//----------------------------------------------------------------------------------------------
void CBookDB::AddLastEmptyRecord() {
    Book tmp;
    strcpy(tmp.author, "");
    strcpy(tmp.name, "");
    strcpy(tmp.publisher, "");
    strcpy(tmp.releaseDate, "");
    tmp.isbn = 0;
    tmp.rating = 0;
        
    int pos = (int)file.CurPosition();
    file.Position(0, ios_base::end);        
    file.Set(&tmp, sizeof(Book));           // add data at the end
    file.Position(pos);                     // go back to original pos
}

//----------------------------------------------------------------------------------------------
// 
// Desc : overwrite 
//        after overwritting, cursor doesn't change
//----------------------------------------------------------------------------------------------
bool CBookDB::OverWriteRecord( unsigned int _idx, Book& _src ) {
    CursorFirst();
    for( unsigned int i=0; i< _idx; i++ ){
        CursorNext();
    }
    int pos = (int)file.CurPosition();
    file.Set( &_src, sizeof(Book) );
    file.Position(pos);                         // go back to original pos
    return true;
}