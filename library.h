//library.h

#ifndef _FT_LIBRARY_H
#define _FT_LIBRARY_H

#include "cio.h"
#define DEFAULT_LIB_SIZE 50

using namespace cio;

struct book
{
	book(char* name, char* author, char* publisher, char* release, unsigned long isbn = 0, unsigned long rating = 0);
    char _name[71];
    char _author[71];
	char _publisher[71];
	char _releaseDate[11];
	unsigned long _isbn;
	unsigned long _rating;
};

//LIBRARY CLASS
class library
{
    private:
		int _bookNum;
		int _libSize;
	    book** _books;
    public:
		library();
		void addBook(book* b);
		void removeBook(book* b);
		void browse(int index, CLabel* n, CLabel* a, CLabel* p, CLabel* r);
		bool validIndex(int index);
		int bookCount();
		~library();
};

#endif
