//Assignment #1
//Written by: Thana Annis
//Last Modified: 10/7/13
//console.cpp

#include"console.h"
#include"bconsole.h"



namespace cio
{
    bool Console::_insertMode = true;
    int Console::_tabsize = 5;
    Console console;

    //display incoming string
    void Console::display(const char* str, int row, int col, int fieldLen, int curPosition)
    {
        int i=0;
        setPos(row, col);

        if(fieldLen)  //limited number of chars
        { 
            for(i; i < fieldLen && str[i]; i++) //print string until string ends
            {
                putChar(str[i]);
            }
            for(i;i < fieldLen; i++)//if string was shorter than fieldLen, pad with spaces
            {
                putChar(' ');
            }
        }
        else  // print the whole thing
        {
            for(i; str[i]; i++)
            {
                putChar(str[i]);
            }
        }
        if(curPosition >= 0)
        {
            setPos(row, col + curPosition);
        }
        else
        {
            setPos(row, col + bio::strlen(str));
        }
    }

    //recieve user input and act accordingly
    //return the key pressed to exit the function
    int Console::edit(char* str, int row, int col, int fieldLen, int maxStrLen,
        int* strOffset, int* curPosition, bool InTextEditor, bool ReadOnly, bool& insertMode)
    {
        bool done = false;
        int key;

        int backupStrOffset = *strOffset;
        int backupCurPosition = *curPosition;

        //initial corrections
        if(!strOffset)
        {
            int tempOffset = 0;
            strOffset = &tempOffset;
        }
        else if(*strOffset > (int)bio::strlen(str))
            *strOffset = (int)bio::strlen(str);

        if(!curPosition)
        {
            int tempCurPos = 0;
            curPosition = &tempCurPos;
        }
        else if(*curPosition > fieldLen)
            *curPosition = *strOffset + fieldLen - 1;
        else if(*curPosition > REM_STRING)
            *curPosition = REM_STRING;


        //backup values
        char* backupStr = new char[maxStrLen];
        bio::strcpy(backupStr, str);

        while(!done)
        {
            if(*strOffset != backupStrOffset && InTextEditor)
            {
                done = true;
                return 0;
            }

            display(&str[*strOffset], row, col, fieldLen, *curPosition);
            key = getKey();

            switch(key)
            {
            case LEFT:
                if(*curPosition > 0)
                    *curPosition -= 1;
                else if(*curPosition == 0 && *strOffset > 0)
                    *strOffset -= 1;
                else
                    alarm();
                break;
            case RIGHT: 
                if(*curPosition < fieldLen - 1)
                {
                    if(STR_POSITION == maxStrLen)
                        alarm();
                    else if(STR_POSITION >= (int)bio::strlen(str))
                        alarm();
                    else
                        *curPosition += 1;
                }
                else
                {
                    if(STR_POSITION == maxStrLen)
                        alarm();
                    if(STR_POSITION >= (int)bio::strlen(str))
                        alarm();
                    else
                        *strOffset += 1;
                }
                break;
            case END:	//moves cursor to the right of the last character in the string			  
                if(REM_STRING > fieldLen - 1)
                {
                    *strOffset = bio::strlen(str) - fieldLen + 1;
                    *curPosition = bio::strlen(str) - *strOffset;
                }
                else
                    *curPosition = bio::strlen(str) - *strOffset;
                break;
            case HOME: *curPosition = *strOffset = 0; break;
            case ENTER: done = true; break;
            case PGDN: done = true; break;
            case PGUP: done = true; break;
            case UP: done = true; break;
            case DOWN: done = true; break;
            case F(1): done = true; break;
            case F(2): done = true; break;
            case F(3): done = true; break;
            case F(4): done = true; break;
            case F(5): done = true; break;
            case F(6): done = true; break;
            case F(7): done = true; break;
            case F(8): done = true; break;
            case F(9): done = true; break;
            case F(10): done = true; break;
            case F(11): done = true; break;
            case F(12): done = true; break;
            case ESCAPE: //if intexteditor mode erase any changes made
                if(!InTextEditor)
                {
                    bio::strcpy(str, backupStr); 
                    display(&str[*strOffset], row, col, fieldLen, *curPosition);
                    *curPosition = backupCurPosition;
                    *strOffset = backupStrOffset;
                }
                done = true;
                break;
            }	//end of readonly switch

            if(!ReadOnly)
            {
                switch(key)
                {
                case DEL: 
                    for(int i = STR_POSITION; str[i]; i++)
                        str[i] = str[i + 1];
                    if(STR_POSITION == bio::strlen(str))
                        alarm();
                    break;
                case BACKSPACE:
                    if(STR_POSITION > 0)
                    {
                        for(int ix = STR_POSITION - 1; str[ix]; ix++)
                        {
                            str[ix] = str[ix+1];
                        }
                        if(*curPosition > 0)
                        {
                            (*curPosition)--;
                        }
                        else if(*strOffset > 0)
                        {
                            *strOffset = (*strOffset) - 1;
                        }
                    }
                    else
                        alarm();
                    break;
                case INSERT: insertMode = !insertMode; break;
                default:
                    if(key >= ' ' && key <= '~')
                    {
                        if(insertMode)
                        {
                            //put char to left of cursor and move each character one to the right
                            if((int)bio::strlen(str) < maxStrLen)
                            {
                                for(int i = bio::strlen(str); i >= *curPosition + *strOffset; i--)
                                {
                                    str[i + 1] = str[i];								
                                }
                                if(*curPosition < fieldLen - 1) //if cursor is not at the end move to the right
                                {
                                    str[*strOffset + (*curPosition)++] = key;
                                }
                                else
                                {
                                    str[(*strOffset)++ + *curPosition] = key;
                                }
                            }
                            else
                                alarm();
                        }
                        else
                        { // override
                            if(STR_POSITION <= maxStrLen)
                            {
                                if(str[STR_POSITION] == 0) //if at null byte, move it one to the right
                                {	
                                    str[STR_POSITION + 1] = 0;
                                }
                                if(*curPosition < fieldLen - 1) //if cursor is not at the end move to the right
                                {
                                    str[*strOffset + (*curPosition)++] = key;
                                }
                                else
                                {
                                    str[(*strOffset)++ + *curPosition] = key;
                                }
                            }
                            else
                                alarm();
                        }
                    }
                    break; 
                }//end switch
            }//end !readonly
            if(InTextEditor && !ReadOnly && key == TAB)
            {

                if((int)bio::strlen(str) + _tabsize < maxStrLen && *curPosition + _tabsize < fieldLen)
                {
                    for(int i = (int)bio::strlen(str); i >= STR_POSITION; i--) //move the string to the right
                    {
                        str[i + _tabsize] = str[i];
                    }
                    for(int i = STR_POSITION; i < STR_POSITION + _tabsize; i++) //insert spaces where string was
                    {
                        str[i] = ' ';
                    }
                    *curPosition += _tabsize;
                }
                else 
                    break;
            }
            else if(!InTextEditor && key == TAB)
                done = true;

        }//end !done
        if(!backupStr)
            delete [] backupStr;
        return key;
    }

    //prompt user for keystroke and store in ch
    //return cn for cascading purposes
    Console& operator>>(Console& cn, int& ch)
    {
        ch = cn.getKey();
        return cn;
    }

    //print ch to screen
    //return cn for cascading purposes
    Console& operator<<(Console& cn, char ch)
    {
        cn.putChar(ch);
        return cn;
    }

    //print str to screen
    //return cn for cascading purposes
    Console& operator<<(Console& cn, const char* str)
    {
        for(int i = 0; str[i]; i++)
            cn.putChar(str[i]);
        return cn;
    }

}//end namespace cio