/*
ccheckmark.cpp
Thana Annis
Last Modified: November 22, 2013
status: complete
*/

#include "ccheckmark.h"

//Constructor - Calls CField constructor and initiates _Label with the incoming parameters
CCheckMark::CCheckMark(bool checked,const char* format, const char* text, int row, int col, int width, bool isRadio) 
    : CField(row, col, width, 1), _Label(text, 0, 4, (width - 4))
{
    // Set the frame of _Label to its owner (Checkmark i.e. 'this'); 
    _Label.frame((CFrame*)this);

    _flag = checked;
    _radio = isRadio;
    bio::strcpy(_format, format);
    _data = &_flag;
}

//Copy Constructor
CCheckMark::CCheckMark(const CCheckMark& c) 
    : CField(c), _Label(c._Label)
{
    _flag = c._flag;
    _radio = c._radio;
    bio::strcpy(_format, c._format);
    _data = &_flag;
}

//Draws the checkmark field, changing the checkmark based on which flags are true.
//Repositions cursor on top of the checkmark
void CCheckMark::draw(int fn) 
{
    if(!_flag)//not checked add space
        _format[1] = ' ';
    else if(!_radio)//checked and not radio add X
        _format[1] = 'X';
    else if(_radio)//checked and radio add O
        _format[1] = 'O';

    console.display(_format, absRow(), absCol());

    _Label.draw();

    //sets cursor at the checkmark
    console.setPos(absRow(), absCol() + 1);
}

//Edits the checkmark field based on user input, calls draw, returns key pressed
int CCheckMark::edit()
{
    int key = 0;
    bool done = false;

    draw();

    while(!done)
    {
        key = console.getKey();
        if(key == SPACE)
        {
            if(_radio)
                _flag = true;
            else
                _flag = !_flag;
            draw();
            done = true;
        }
        else if(key == UP || key == DOWN || key <= ' ' ||key >= '~')
            done = true;
    }
    return key;
}

//Always return true
bool CCheckMark::editable() const
{
    return true;
}

//Set _flag by recieving a const void*
void CCheckMark::set(const void* flag)
{
    _flag = *(bool*)flag;
}

//Get _flag 
bool CCheckMark::checked() const
{
    return _flag;
}

//Set _flag by receiving a bool
void CCheckMark::checked(bool val)
{
    _flag = val;
}

//Get _radio
bool CCheckMark::radio()
{
    return _radio;
}

//Set _radio
void CCheckMark::radio(bool isRadio)
{
    _radio = isRadio;
}

//Overload the bool cast to return the value of _flag
CCheckMark::operator bool()
{
    return _flag;
}

//Overload the char* cast to return the value of _Label.data()
CCheckMark::operator char*()
{
    return (char*)_Label.data();
}

//Overload the operator= and set the _flag to flag 
bool CCheckMark::operator=(bool flag)
{
    _flag = flag;
    return _flag;
}
