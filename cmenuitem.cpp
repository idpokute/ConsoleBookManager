/* 
   Len Isac
   cmenuitem.cpp
   Last update: November 22, 2013
   status: 8th commit.
*/

#include "cmenuitem.h"

namespace cio 
{
    // Initializes the CField with Row, Col, Width and 1 for Height
    // Initializes the Label with (Text, 0, 1 and Width-2) for (Str, Row, Col, and Len)
    CMenuItem::CMenuItem(bool Selected, const char* Format, const char* Text, int Row, int Col, int Width) : CField(Row, Col, Width, 1), Label(Text, 0, 1, (Width - 2))
    {        
        _selected = Selected; // Sets the attributes to corresponding arguments
        bio::strcpy(_format, Format);
          
        _data = _format; // Sets CFields::_data to the address of _format
        
        Label.frame(this); // Set Label's frame to this object.
    }

    // Passes CM to CField and Initializes the Label with CM 
    CMenuItem::CMenuItem(const CMenuItem &CM) : CField(CM), Label(CM.Label)
    {        
        _selected = CM._selected; // Sets the _selected to _selected of CM
                
        CField::_data = &_format; // Sets CFields::_data to the address of _format
                
        Label.frame(this); // Set Label's frame to this object.
    }

    void CMenuItem::draw(int fn) 
    {
        if (_selected == true) // If _selected is true, it surrounds the Label Text the _format[0] and _format[1]
        {
           
            console.display(&_format[0], absRow(), absCol());
            Label.draw(fn); // Draw label with fn.
            console.display(&_format[1], absRow(), absCol() + Label.width());
        }
        else // If _selected if false, it surrounds the Label with SPACEs (overwrites _format[0] and _format[1])
        {
            console.display(" ", absRow(), absCol());
            Label.draw(fn); // Draw label with fn.
            console.display(" ", absRow(), absCol() + Label.width());
        }

        console.setPos(absRow(), absCol()+1); // Positions the cursor at the first character of the Label
    }
        

    int CMenuItem::edit()
    {     
        draw(); // draw menuitem.

        int key = console.getKey(); // get key

        if (key == SPACE ||  key <= ' ' || key >= '~') // the key must be either SPACE or any non-printable character (all printable character are ignored) 
        {
            if (key == SPACE)
            {
                _selected = true; 
                draw(); // draw menu item again.
            }
        }
        return key;
    }

    bool CMenuItem::editable()const
    {
        return true;
    }

    void CMenuItem::set(const void* Selected)
    {
        _selected = !!Selected; // Sets _selected to where Selected is pointing to  (check how to conver const void* to bool.

    }

    bool CMenuItem::selected()const
    {
        return _selected;
    }

    void CMenuItem::selected(bool val)
    {
        _selected = val;
    }

    const char* CMenuItem::Text()const
    {
        return (char*)Label.data(); // Returns the text of Label         
    }

}

