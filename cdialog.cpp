/*

cdialog.cpp

Fadi Tawfig

Last Modified: November 22, 2013

status: complete

*/

#include "cio.h"

namespace cio
{

//CDialog Constructor will initialize all of a CDialog object's data members including it's parent CFrame members
CDialog::CDialog(CFrame* Container,
                 int Row, int Col,
                 int Width, int Height, 
                 bool Bordered, 
                 const char* border) :
                 CFrame(Row, Col, Width, Height, Bordered, border, Container)
{
    //Set all of CDialog's attributes to their default values
    _fnum = 0;
    _curidx = 0;
    _fldSize = C_INITIAL_NO_FIELDS;
    _editable = false;
    //Allocate memory for _dyn and _fld arrays
    _dyn = new bool [_fldSize];
    _fld = new CField* [_fldSize];
    //Set all field pointers to NULL
    unsigned int i = 0;
    while(i < _fldSize)
    {
        _fld[i] = 0;
        i++;
    }
    //Set all dynamic flags to false
    i = 0;
    while(i < _fldSize)
    {
        _dyn[i] = false;
        i++;
    }
}

//CDialog Destructor will delete any dynamically allocated fields pointed to in the _fld array and then delete 
//the _fld and _dyn arrays
CDialog::~CDialog()
{
    int i = 0;
    //Delete any dynamically allocated fields in the Dialog
    for(i = 0; i < _fnum; i++)
    {
        if(_dyn[i])
        {
            delete _fld[i];
        }
    }
    //Delete _fld and _dyn arrays
    delete [] _fld;
    delete [] _dyn;
}

//draw() will display the Dialog and any fields in the dialog
void CDialog::draw(int fn)
{
    int i = 0;
    //If fn is C_FULL_FRAME call parent draw
    if(fn == C_FULL_FRAME)
    {
        CFrame::draw();
    }
    //If fn is 0 or C_FULL_FRAME draw all the fields in the dialog
    if(fn == 0 || fn == C_FULL_FRAME)
    {
        for(i = 0; i < _fnum; i++)
        {
            _fld[i]->draw(fn);            
        }
    }
    //If fn is a positive integer > 0 then draw only field number fn
    else if(fn > 0)
    {
        _fld[fn-1]->draw(fn);          
    }
}

//edit() will call the edit function for editable fields in the dialog
int CDialog::edit(int fn)
{
    int key = 0;
    int i = 0;
    //If this object is not editable then display the dialog and wait 
    //for a key to be pushed and return that key
    if(!editable())
    {
        draw();                        
        key = console.getKey();
    }
    else
    {
        //If fn is less than or equal to 0 call draw with fn as argument
        if(fn <= 0)
        {
            draw(fn);
            fn = 1;
        }
        //Set current index to desired field
        else
        {
            _curidx = fn - 1; 
        }
        //done flag will toggle true and terminate the loop when the user wants to exit the function
        bool done = false;
        //up flag will keep track of the direction the user is currently scrolling
        bool up = false;
        while(!done)
        { 
            //If the current field isn't editable go to the next one if scrolling down and the previous one if scrolling up
            if(!_fld[_curidx]->editable())
            {
                if(_curidx == _fnum - 1 && !up)
                {
                    _curidx = 0;
                }
                else if(_curidx == 0 && up)
                {
                    _curidx = _fnum - 1;
                }
                else
                {
                    up ? _curidx-- : _curidx++;
                }
            }
            //If the current field is editable call it's edit function and set key to the key that was used to exit editing
             else
             { 
                 key = _fld[_curidx]->edit();
                 //If the key used to exit the edit function is ENTER, TAB or DOWN or if the field is read only, go to next field
                 if(key == ENTER || key == TAB || key == DOWN)
                 {
                     up = false;
                     //If _curidx is the last field pushing enter, tab or down will go to the first field
                     if(_curidx == _fnum - 1)
                     {
                         _curidx = 0;
                     }
                     else
                     {
                         _curidx++;
                     }
                 }
                 //If the UP key is used to exit the edit function, go to previous field
                 else if(key == UP)
                 {
                     up = true;
                     //If _curidx is the first field pushing up will go to the last field
                     if(_curidx == 0)
                     { 
                         _curidx = _fnum - 1;
                     }
                     else
                     {
                         _curidx--;
                     }
                 }
                 //Any other key will exit the function
                 else
                 {
                     done = true;
                 }
            }
        }
    }
    return key;
}

//add() by pointer will add a new field to the dialog and expand the size of the _fld and _dyn arrays if necessary
int CDialog::add(CField* field, bool dynamic)
{
    //check if _fnum has reached _fldSize
    if(_fnum == _fldSize)
    {
        int i = 0;
        bool* tempDyn = new bool[_fnum];
        CField** tempFld = new CField*[_fnum];
        //Expand _fldSize by C_DIALOG_EXPANSION_SIZE(ciogh.h)
        _fldSize += C_DIALOG_EXPANSION_SIZE;
        //Copy values in _fld and _dyn to temporary pointers
        for(i = 0; i < _fnum; i++)
        {
            tempFld[i] = _fld[i];
            tempDyn[i] = _dyn[i];
        }
        //Delete old _fld and _dyn
        delete [] _fld;
        delete [] _dyn;
        //Reallocate memory of _fld and _dyn with expanded size
        _fld = new CField*[_fldSize];
        _dyn = new bool[_fldSize];
        //Copy values from temporary arrays to _fld and _dyn
        for(i = 0; i < _fnum; i++)
        {
            _fld[i] = tempFld[i];
            _dyn[i] = tempDyn[i];
        }
        //Delete temporary arrays
        delete [] tempFld;
        delete [] tempDyn;
    }
    //Add new field
    _fld[_fnum] = field;
    _dyn[_fnum] = dynamic;
    //Increment _fnum
    _fnum++;
    //Set container of new field to this CDialog object
    field->container(this);                       
    //Return index of newly added field
    return _fnum - 1;
}

//add() by reference will call the first add function and pass it the address of the incoming field
int CDialog::add(CField& field, bool dynamic)
{
    //Call add() by pointer and return index of newly added field
    return add(&field, dynamic);
}

//Insertion by pointer will call add by pointer and pass it the incoming field pointer
CDialog& CDialog::operator<<(CField* field)
{
    //Call add() by pointer
    add(field);
    return *this;
}

//Insertion by reference will call add by reference and pass it the reference to the incoming field
CDialog& CDialog::operator<<(CField& field)
{
    //Call add() by reference
    add(field);
    return *this;
}

//editable() will check if any fields in the dialog are editable and return true if there at least one 
//editable field and false if there are none. It will also set dialog's _editable data member accordingly
bool CDialog::editable()
{
    //Check if any of the fields in this dialog are editable             
    int i = 0;
    _editable = false;
    for(i; i < _fnum; i++)
    {
        if(_fld[i]->editable())
        {
            _editable = true;
        }
    }
    return _editable;
}

//fieldNum() returns the amount of fields in this dialog
int CDialog::fieldNum()const
{
    return _fnum;
}

//curIndex() returns the index of the field currently being edited
int CDialog::curIndex()const
{
    return _curidx;
}

//Index operator returns a field at the specified index
CField& CDialog::operator[](unsigned int index)
{
    return *_fld[index];
}

//curField() returns a reference to the field currently being edited
CField& CDialog::curField()
{
    return *_fld[_curidx];
}

}
