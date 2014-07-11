#include "library.h"

//Book constructor will set all members to incoming values
book::book(char* name, char* author, char* publisher, char* release, unsigned long isbn, unsigned long rating)
{
    bio::strcpy(_name, name);
	bio::strcpy(_author, author);
	bio::strcpy(_publisher, publisher);
	bio::strcpy(_releaseDate, release);
	_isbn = isbn;
	_rating = rating;
}

//Construct a new library with default size
library::library()
{
	_libSize = DEFAULT_LIB_SIZE;
	_bookNum = 0;
    _books = new book*[DEFAULT_LIB_SIZE];
	int i = 0;
	for(i; i < _libSize; i++){
	    _books[i] = (book*)0;
	}
}

//library destructor
library::~library()
{
	int i = 0;
	for(i; i < _bookNum; i++)
	{
	    delete _books[i];
	}
    if(_books)
	{
	    delete [] _books;
	}
}

//Add a book to the library, if library is full, expand size then add
void library::addBook(book* b)
{
	//Expand libSize
	if(_bookNum == _libSize)
	{
		int i = 0;
		book** tempLib = new book*[_bookNum];
		for(i; i < _bookNum; i++)
		{
		    tempLib[i] = _books[i];
		}
		delete [] _books;
	    _libSize += 50;
		_books = new book*[_libSize];
		for(i = 0; i < _bookNum; i++)
		{
		    _books[i] = tempLib[i];
		}
	}
	//Add book
    _books[_bookNum] = b;
	_bookNum++;
}

//This function will set the CLabels provided to the values of the book referred to by index
void library::browse(int index, CLabel* n, CLabel* a, CLabel* p, CLabel* r)
{
    n->set(_books[index]->_name);
	a->set(_books[index]->_author);
	p->set(_books[index]->_publisher);
	r->set(_books[index]->_releaseDate);
}

//This function will ensure that the index provided refers to a book in the library
bool library::validIndex(int index)
{
    if(index > _bookNum - 1)
	{
        return false;
	}
	else if(index < 0){
		return false;
	}
	return true;
}

//Return amount of books in the library
int library::bookCount()
{
    return _bookNum;
}

//Remove a book from the library
void library::removeBook(book* b){

}



