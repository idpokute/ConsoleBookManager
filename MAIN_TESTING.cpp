/*
FADI TAWFIG

RELEASE 1.0 FEATURE TESTING

LAST MODIFIED: 01/12/2013

*/

#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>
#include "cio.h"
#include "library.h"

using namespace cio;

//Global insert mode
bool insertMode = true;
//Global library object
library l;

bool isDigit(char ch);
bool validISBN(const char* isbn, CDialog& owner);
void addBook();
void viewBooks();

int main(int argc, char* argv){
	char name[71] = "";
	char author[71] = "";
	char publisher[71] = "";
	char release[11] = "";
	char record[4] = "";
	char indexNum[3] = "1";
	CDialog screen;
	//MAIN WINDOW
	CDialog d(&screen, 2, 2, 50, 20, true, "+-+|+-+|");
	d<< new CLabel("FADI'S 1.0 TESTING", 1, 1)
	 << new CLabel("F6 - MOVE", 1, 40);
	int addButton = d.add(new CButton("ADD A BOOK", 15, 2, true));
	int viewButton = d.add(new CButton("VIEW BOOKS", 15, 34, true));
	//ADD BOOK WINDOW
	CDialog add(&d, 4, 4, 50, 15, true, "+-+|+-+|");
	add
	<< new CLabel("ADD A BOOK:", 1, 1)
	<< new CLabel("Book Name:", 3, 4)
	<< new CLineEdit(name, 3, 20, 25, 71, &insertMode, false)
	<< new CLabel("Author Name:", 4, 4)
	<< new CLineEdit(author, 4, 20, 25, 71, &insertMode, false)
	<< new CLabel("Publisher:", 5, 4)
    << new CLineEdit(publisher, 5, 20, 25, 71, &insertMode, false)
	<< new CLabel("Release Date:", 6, 4)
	<< new CLineEdit(release, 6, 20, 25, 71, &insertMode, false);
	int saveButton = add.add(new CButton("Save + Exit", 10, 2, true));
	add.add(new CButton("Cancel", 10, 38, true));
	//VIEW BOOKS WINDOW
	int bookIndex = 0;
	CDialog view(&d, 4, 4, 50, 15, true, "+-+|+-+|");
	view
	<< new CLabel("BOOKS:", 1, 1)
	<< new CLabel("ESCAPE - EXIT", 1, 22)
	<< new CLabel("TITLE:", 2, 3)
	<< new CLabel("AUTHOR:", 4, 3)
	<< new CLabel("PUBLISHER:", 6, 3)
	<< new CLabel("RELEASE DATE:", 8, 3);
	CLabel n("", 2, 18);
    CLabel a("", 4, 18);
	CLabel p("", 6, 18);
    CLabel r("", 8, 18);
	view << n << a << p << r;
	int index = view.add(new CLabel(indexNum, 1, 46, 3)); 
	view.add(new CLabel("#", 1, 45)); 
	int nextButton = view.add(new CButton("NEXT", 11, 40, true));
	int prevButton = view.add(new CButton("PREVIOUS", 11, 2, true));
	int recordNum = view.add(new CValEdit(record, 11, 20, 5, 3, &insertMode, validISBN, NO_HELPFUNC, true));
    int goToRecord = view.add(new CButton("GO", 11, 25, true));
	//MAIN LOOP
	screen.draw();
	bool done = false;
	bool vis = false;
	int key = 0;
	do
	{
		d.draw();
		key = d.edit();
	    switch(key){
		    case C_BUTTON_HIT:
				//Add button hit
				if(d.curIndex() == addButton)
				{
				    add.draw();
				    do
					{
					    add.draw();
					    key = add.edit(1);
				        switch(key){
					    case C_BUTTON_HIT:
							if(add.curIndex() == saveButton)
							{
						        l.addBook(new book(name, author, publisher, release));
							}
							bio::strcpy(name, "");
							bio::strcpy(author, "");
							bio::strcpy(publisher, "");
							bio::strcpy(release, "");
						    done = true;
						    break;
					    }
				    }
				    while(!done);
				    done = false;
				    add.hide();
				}
				//View button hit
				if(d.curIndex() == viewButton && l.bookCount())
				{
					do{
						l.browse(bookIndex, &n, &a, &p, &r);
						view[index].set(_itoa(bookIndex + 1, indexNum, 10));
						view.draw();
					    key = view.edit();
					    switch(key){
					    case C_BUTTON_HIT:
							//Next
					    	if(view.curIndex() == nextButton && l.validIndex(bookIndex + 1))
							{
							    bookIndex++;
							}
							//Previous
							else if(view.curIndex() == prevButton && bookIndex > 0)
							{
								bookIndex--;
							}
							//Go to record
							else if(view.curIndex() == goToRecord){
								//If number record number entered is valid, go to that record
							    if(l.validIndex(atoi((const char*)view[recordNum].data()) - 1)){
							        bookIndex = atoi((const char*)view[recordNum].data()) - 1;
								}
							}
					    	break;
						case ESCAPE:
							done = true;
							break;
					    }
					}
					while(!done);
					done = false;
					view.hide();
				}
				break;
			//Move the window with F6
		    case F(6):
				d.move();
				break;
			//Exit the program
			case ESCAPE:
				done = true;
				break;
		}
	}
	while(!done);
}

//Returns true if the character passed is a number
bool isDigit(char ch){
    return ch>='0' && ch<='9';
}

//Validates that input is a number
bool validISBN(const char* isbn, CDialog& owner){
    int i = 0;
	for(i; isbn[i]; i++){
	    if(!isDigit(isbn[i])){
		    return false;
		}
	}
	return true;
}

//***** FEATURES TO IMPLEMENT: *****
//***** MANDATORY: *****

/* - BROWSE OPENED DATA FILE -
	- Go to next record
	- Go to previous record
	- Go to last record
	- Go to record by number
*/

/* - EDIT THE RECORD -
	- Save the edited record
	- Cancel editing a record without saving
	- Make sure edit information is not lost (save unsaved data on exit without prompt)
*/

/* - ADD A RECORD -
	- Create an empty record and save it at the end of the file
	- Cancel editing a record without 
*/

//***** OPTIONAL: *****