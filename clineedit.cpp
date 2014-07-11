#include <string.h>
#include "clineedit.h"
#include "console.h"

namespace cio {

    //----------------------------------------------------------------------------------------------
    // Constructor
    // 
    //----------------------------------------------------------------------------------------------
    CLineEdit::CLineEdit(char* Str, int Row, int Col, int Width, int Maxdatalen, 
                            bool* Insertmode, 
                            bool Bordered, 
                            const char* Border) 
                        :CField( Row, Col, Width, Bordered ? 3 : 1, Str, Bordered, Border),
                        _maxdatalen(Maxdatalen), _insertmode(Insertmode)
     {
         _dyn = false;
        _curpos = 0;
        _offset = 0;
     }
    
    //----------------------------------------------------------------------------------------------
    // Constructor
    // 
    //----------------------------------------------------------------------------------------------
    CLineEdit::CLineEdit(int Row, int Col, int Width,int Maxdatalen, 
                            bool* Insertmode, 
                            bool Bordered,
                            const char* Border)
                        :CField( Row, Col, Width, Bordered ? 3 : 1, '\0', Bordered, Border),
                        _maxdatalen(Maxdatalen), _insertmode(Insertmode)
    {
        _dyn = true;
        char* strBuff = new char [Maxdatalen+1];

        for(int i=0; i<Maxdatalen; i++ )
        {
            strBuff[i] = ' ';
        }
        strBuff[0] = '\0';

        _data = strBuff;
        _curpos = 0;
        _offset = 0;
    }

    //----------------------------------------------------------------------------------------------
    // Destructor
    // 
    //----------------------------------------------------------------------------------------------
    CLineEdit::~CLineEdit()
    {
        if(_dyn) {
            delete [] _data;
            _data = '\0';
        }
    }

    //----------------------------------------------------------------------------------------------
    // Draw 
    // 
    //----------------------------------------------------------------------------------------------
    void CLineEdit::draw(int Refresh) 
    {
        CFrame::draw(Refresh);


        int row = absRow() + (visible() ? 1 : 0);
        int col = absCol() + (visible() ? 1 : 0);
        int len = width() + (visible() ? -2 : 0);

        console.display((char*)_data+_offset, row, col, len, _curpos); 
    }

    //----------------------------------------------------------------------------------------------
    // edit
    // 
    //----------------------------------------------------------------------------------------------
    int CLineEdit::edit()
    {
        int row = absRow() + (visible() ? 1 : 0);
        int col = absCol() + (visible() ? 1 : 0);
        int len = width() + (visible() ? -2 : 0);

        return console.edit( (char*)_data, row, col, len, _maxdatalen, &_offset, &_curpos );//, true, false, *_insertmode);
    }

    //----------------------------------------------------------------------------------------------
    //
    // Desc : Ver0.3 - always return true
    //----------------------------------------------------------------------------------------------
    bool CLineEdit::editable()const
    {
        return true;
    }
 
    //----------------------------------------------------------------------------------------------
    //
    // Desc : Ver0.3 - Copies the characters pointed by Str into the memory pointed by 
    //                 Field's _data up to _maxdatalen characters.
    //----------------------------------------------------------------------------------------------
    void  CLineEdit::set(const void* Str)
    {
        memcpy( _data, Str, _maxdatalen );
    }
};