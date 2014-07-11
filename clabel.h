/* 
clabel.h
Len Isac
Last modified: November 1st, 2013
status: complete.
*/

#ifndef __LI_CLABEL_H__
#define __LI_CLABEL_H__

#include "cfield.h"
#include "console.h"

class Console;

namespace cio
{
    class CLabel :  public CField
    {
        // for length of the field:
        //  Use void CFrame::width(int) to store length, and int CFrame::width() to retrieve the length

    public:
        CLabel(const CLabel& L);
        CLabel(const char *Str, int Row, int Col, int Len = 0);
        CLabel(int Row, int Col, int Len);
        ~CLabel();
        void draw(int fn=C_NO_FRAME);
        int edit();
        bool editable()const;
        void set(const void* str);
    };

}
#endif