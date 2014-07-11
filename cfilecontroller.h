/*
cfilecontroller.h
 
Sehui Park

Last Modified: December, 2nd, 2013

status: working

*/
#ifndef __PSH_CFILECONTROLLER_H__
#define __PSH_CFILECONTROLLER_H__

#include <fstream>
using namespace std;

//----------------------------------------------------------------------------------------
// Desc: Basic File Controller class
// Watch the cpp file, there are more description.
//----------------------------------------------------------------------------------------
class CFileController{
    fstream         file;                       
    streamoff       size;                       // file size

public:
    CFileController();
    virtual ~CFileController();

    bool Open(const char* _fname);                                  // This is necessary (should be in the constructor, but later)
    bool Position( int _n, ios_base::seekdir _dir = ios::beg);      // set the cursor 
    streamoff CurPosition();                                        // get current cursor pos
    bool Get(void* _dst, unsigned int _size);                       // read binary data : Cursor moves after this func
    bool Set(void* _src, unsigned int _size);                       // write binary data: Cursor moves after this func
    bool IsEnd();
};


#endif