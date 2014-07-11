/*

cbutton.h

Fadi Tawfig

Last Modified: November 18, 2013

status: tentatively complete

*/

#ifndef __FT_CBUTTON_H__
#define __FT_CBUTTON_H__

#include "cio.h"

namespace cio
{
    class CButton : public CField
    {
    public:
        CButton(const char* str, int row, int col, bool bordered = true,
                const char* border = C_BORDER_CHARS);
        virtual ~CButton();
        void draw(int fn = C_FULL_FRAME);
        int edit();
        bool editable()const;
        void set(const void* str);
    };
}
#endif
