/*
 
cvaledit.cpp
 
Sehui Park

Last Modified: November, 21th, 2013

status: done

*/
#include "cvaledit.h"
#include"bconsole.h"

namespace cio{
    //----------------------------------------------------------------------------------------------
    // Constructor
    // Desc : 
    //----------------------------------------------------------------------------------------------
    CValEdit::CValEdit(char* Str, int Row, int Col, int Width,
                        int Maxdatalen, bool* Insertmode,
                        bool (*Validate)(const char* , CDialog&), 
                        void (*Help)(MessageStatus, CDialog&),
                        bool Bordered,
                        const char* Border)
                    :CLineEdit( Str, Row, Col, Width, Maxdatalen, Insertmode, Bordered, Border ), _validate(Validate), _help(Help)
    {

    }

    //----------------------------------------------------------------------------------------------
    // Constructor
    // Desc : 
    //----------------------------------------------------------------------------------------------
    CValEdit::CValEdit(int Row, int Col, int Width,
                        int Maxdatalen, bool* Insertmode,
                        bool (*Validate)(const char* , CDialog&), 
                        void (*Help)(MessageStatus, CDialog&),
                        bool Bordered,
                        const char* Border)
                    :CLineEdit( Row, Col, Width, Maxdatalen, Insertmode, Bordered, Border ), _validate(Validate), _help(Help)
    {

    }

    //----------------------------------------------------------------------------------------------
    // edit
    // Desc : 
    //----------------------------------------------------------------------------------------------
    int CValEdit::edit()
    {
        int key;

        if( container() == '\0' ) {
            key = CLineEdit::edit();
        }
        else {
            // 1. Help Function exists.
            if( _help != NO_HELPFUNC ){
                _help(MessageStatus::SetMessage, *container());
            }
            
            bool isValid = false;
           
            // 2. Call ClineEdit.            
            key= CLineEdit::edit();

            // 3. Validate Function exists, and key is navigation key
            if( (_validate != NO_VALDFUNC) ) {
                do {
                    if(key == ESCAPE || key==F(1) ) {
                        return key;
                    }
                    else if(key == UP || key == DOWN || key == TAB || key == ENTER) {
                        isValid = _validate((char*)CField::data(), *container());
                        if( isValid )
                            isValid = true;
                        else 
                            key = CLineEdit::edit();
                    }
                }while( !isValid );
            }
    
            // 4. clear helpfunc MSG
            if( _help != NO_HELPFUNC ) {
                _help(MessageStatus::ClearMessage, *container() );
            }
        }            
        return key;
    }
}

