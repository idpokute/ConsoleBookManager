/*
ccheckmark.cpp
Thana Annis
Last Modified: November 22, 2013
status: complete
*/

#ifndef __TA_CCHECKMARK_H__
#define __TA_CCHECKMARK_H__

#include "cio.h"
using namespace cio;

class CCheckMark : public CField
{
    bool _flag; //holds status of Checkbox (0: unchecked or 1: checked ) is pointed by _data pointer
    bool _radio; //dictates the behavior of the Checkbox as a radio-button or a check-mark. 
    char _format[4]; //holds the characters, the Checkbox is drawn with (i.e. "[X]", "(O)", "<*>", etc...). 
    CLabel _Label; //holds the Label attached to the this Checkbox
public:
    CCheckMark(bool checked,const char* format, const char* text,
        int row, int col, int width, bool isRadio = false);
    CCheckMark(const CCheckMark& C);
    void draw(int fn = C_NO_FRAME) ;
    int edit();
    bool editable()const;
    void set(const void* flag);
    bool checked()const;
    void checked(bool val);
    bool radio(); 
    void radio(bool isRadio);
    operator bool(); 
    operator char*(); 
    bool operator=(bool flag);
};

#endif