/*
cfilecontroller.cpp
 
Sehui Park

Last Modified: December, 2nd, 2013

status: working

*/
#include "cfilecontroller.h"
#include <iostream>
using namespace std;

//----------------------------------------------------------------------------------------------
// Constructor
// Desc : 
//----------------------------------------------------------------------------------------------
CFileController::CFileController() : size(0){
}

//----------------------------------------------------------------------------------------------
// Destructor 
// Desc : 
//----------------------------------------------------------------------------------------------
CFileController::~CFileController(){
    file.close();
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Open Binary file with read/write options.
//        Calculate file size, then set cursor at the beginning of file
//----------------------------------------------------------------------------------------------
bool CFileController::Open(const char* _fname) {
    file.open(_fname, ios::binary | ios::out | ios::in );
    if( !file.is_open() ){
        return false;
    }

    file.seekg(0, ios_base::end);
    size = file.tellg();                // Calculate file byte size 
    file.seekg(0, ios_base::beg);       // Set cursor at the beginning of file (default)

    return true;
}

//----------------------------------------------------------------------------------------------
// change cursor position
// Desc : If the wanted cursor is not at the valid position (beg to end), cursor don't move.
//----------------------------------------------------------------------------------------------
bool CFileController::Position( int _n, ios_base::seekdir _dir) {
    streamoff prev = CurPosition();
    file.seekg( _n, _dir );
    streamoff current = CurPosition();

    // Remind it!
    // Cursor can be at the end of File!!
    if( current < 0 || current > size ) {
        file.seekg( prev, ios_base::beg );
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : Get current cursor position.
//----------------------------------------------------------------------------------------------
streamoff CFileController::CurPosition() {
    return file.tellg();
}

//----------------------------------------------------------------------------------------------
// Read data function from binary file
// Desc : read data from file. If the program tries to access invalid location in memory, don't read.
//        After Get method, Cursor moves at the end of reading data
//---------------------------------------------------------------------------------------------- 
bool CFileController::Get(void* _dst, unsigned int _size){
    // When the program tries to access wrong memory location, return false.
    if( file.tellg() < 0 || (int)file.tellg() + _size > size){
        //cout<<"20131201-Sehui: Access violation"<<endl;
        return false;
    }
    file.read((char*)_dst, _size);
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : write src data to file. If the cursor is not at the valid position, don't write data.
//        After Set method, Cursor moves at the end of writing data
//----------------------------------------------------------------------------------------------
bool CFileController::Set(void* _src, unsigned int _size) {
    // When the program tries to access wrong memory location, return false.
    if( file.tellg() < 0 || (int)file.tellg() > size){
        //cout<<"20131202-Sehui: Access violation"<<endl;
        return false;
    }

    file.write((const char*)_src, _size);       // write src data
    streamoff cursor = file.tellg();            // save the cursor which is after the written data
    file.seekg(0, ios_base::end);               // Calculate file size again.
    size = file.tellg();
    //Position( (int)cursor );                    // load the cursor position
    return true;
}

//----------------------------------------------------------------------------------------------
// 
// Desc : is the cursor at the end of file?
//----------------------------------------------------------------------------------------------
bool CFileController::IsEnd() {
    if( CurPosition() >= size )
        return true;
    return false;
}