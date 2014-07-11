/*
 
cvaledit.h
 
Sehui Park

Last Modified: November, 21th, 2013

status: done

*/
#ifndef __PSH_CVALEDIT_H__
#define __PSH_CVALEDIT_H__

#include "clineedit.h"
 
namespace cio{
    class CValEdit: public CLineEdit{
        void (*_help)(MessageStatus, CDialog&);
        bool (*_validate)(const char*, CDialog&);

    public:
        CValEdit(char* Str, int Row, int Col, int Width,
                    int Maxdatalen, bool* Insertmode,
                    bool (*Validate)(const char* , CDialog&) = NO_VALDFUNC, 
                    void (*Help)(MessageStatus, CDialog&) = NO_HELPFUNC,
                    bool Bordered = false,
                    const char* Border=C_BORDER_CHARS);
        CValEdit(int Row, int Col, int Width,
                    int Maxdatalen, bool* Insertmode,
                    bool (*Validate)(const char* , CDialog&) = NO_VALDFUNC, 
                    void (*Help)(MessageStatus, CDialog&) = NO_HELPFUNC,
                    bool Bordered = false,
                    const char* Border=C_BORDER_CHARS);
        int edit();
    };
}
#endif