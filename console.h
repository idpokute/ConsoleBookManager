//Assignment #1
//Written by: Thana Annis
//Last Modified: 10/18/13
//console.h

#ifndef __TA_CONSOLE_H__
#define __TA_CONSOLE_H__
#include"bconsole.h"

class BConsole{};

#define STR_POSITION (*curPosition + *strOffset) 
#define REM_STRING ((int)bio::strlen(str) - *strOffset)

namespace cio
{
    class Console : public bio::BConsole
    {
        static bool _insertMode;
    public:
        static int _tabsize; //amount of spaces to insert on tab press
        void display(const char*, int, int, int fieldLen=0, int curPosition = -1);
        int edit(char*, int, int, int, int, int* strOffset=(int*)0, int* curPosition=(int*)0,  
            bool InTextEditor = false, bool ReadOnly = false, bool& insertMode=_insertMode );
    };

    extern Console console;

    Console& operator>>(Console& cn, int& ch);
    Console& operator<<(Console& cn, char ch);
    Console& operator<<(Console& cn, const char* str);
}//end namespace cio

#endif