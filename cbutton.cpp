/*

cbutton.cpp

Fadi Tawfig

Last Modified: November 22, 2013

status: complete

*/

#include "cio.h"

namespace cio
{
    //CButton constructor
    CButton::CButton(const char* str, int row, int col, 
                     bool bordered, const char* border) : 
    CField(row, col,
    bordered ? bio::strlen(str) + 4 : bio::strlen(str) + 2,
    bordered ? 3 : 1, (void*)str, bordered, border)
    {
        //Allocate enough memory to hold contents of str and point _data to it
        _data = new char[bio::strlen(str) + 1];
        //Copy contents of str to _data
        bio::strcpy(_data, str);
    }
    
    //CButton destructor
    CButton::~CButton()
    {
        //Delete memory pointed to by _data
        if(_data)
        {
            delete [] _data;
        }
    }

    //CButton draw()
    void CButton::draw(int fn)
    {
        //Call CFrame's draw
        CFrame::draw(fn);
        //Display text at absRow() and absCol() if not bordered or absRow() + 1 and absCol() + 2 if bordered
        console.display((char*)_data, absRow() +  visible(), absCol() + (visible() ? 2 : 0));
    }

    //CButton edit()
    int CButton::edit()
    {
        //Draw the button surrounded by square brackets
        draw();
        console.display("[", absRow() + visible(), absCol() + (visible() ? 1 : -1));
        console.display("]", absRow() + visible(), absCol() + bio::strlen(_data) + (visible() ? 2 : 0));
        //Place the cursor under the first character of button's text
        console.setPos(absRow() +  visible(), absCol() + (visible() ? 2 : 0));
        //Wait for user entry
        int key = console.getKey();
        //Remove square brackets button is deselected.
        console.display(" ", absRow() + visible(), absCol() + (visible() ? 1 : -1));
        console.display(" ", absRow() + visible(), absCol() + bio::strlen(_data) + (visible() ? 2 : 0));
        //If user inputs ENTER or SPACE keys, return C_BUTTON_HIT, otherwise return entered key.
        if(key == SPACE || key == ENTER){
            return C_BUTTON_HIT;
        }
        else{
            return key;
        }
    }

    //CButton edtiable()
    bool CButton::editable()const
    {
        //Always returns true
        return true;
    }

    //CButton set()
    void CButton::set(const void* str)
    {
        //Deallocate memory pointed to by _data
        if(_data)
        {
            delete [] _data;
        }
        //Allocate enough memory to hold contents of str and point to it with _data
        _data = new char[bio::strlen(str) + 1];
        //Copy contents of str to _data
        bio::strcpy(_data, str);
    }
}
