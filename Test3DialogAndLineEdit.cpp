// Console Input Output Library Tester program for CDialog and CLineEdit
// Test3DialogAndLineEdit.cpp
//
// Fardad Soleimanloo, Chris Szalwinski
// Oct 18 2012
// Version 0.91

#include "cio.h"
#include <cstdio>

using namespace std;
using namespace cio;

int main(){
  bool done = false;
  int key = 0;
  int i = 0;
  bool insert = true;
  char str[81] = "I want to edit this thing!";
  CDialog Screen;
  for(int k=1;k<console.getRows();k+=2){
    for(int m=0;m<console.getCols()-10;m+=10){
      Screen<<new CLabel((i=!i)?"Hello": "Hi",k, m, 9);
    }
  }
  Screen<<new CLabel("Dialog and Line Editor Tester      ", 0, 0);

  CDialog D(&Screen, 5, 10, 50, 15, true, "+-+|+-+|");
  CLabel L("Enter some text down here:",6, 4);
  Screen.draw();
  D.add(new CLabel("Testing Label and Line edit",1, 12));
  D << new CLabel("Name: ", 4, 3)
    << new CLineEdit(4,9,20,40,&insert)
    << new CLabel("Surname: ", 5, 3)
    << new CLineEdit(5,12,20,50,&insert)<< L
    << new CLineEdit(str,7,4,40,80, &insert, true);
  int mesIndx = D.add(new CLabel(10, 5, 40));
  D << new CLabel("Press ESC or F2 to exit, press F6 to Move", 2, 3);
  D[mesIndx].set("Setting the message to see what happens");
  D.draw();
  while(!done){
    key = D.edit(mesIndx+ 1);
    i++;
    sprintf((char*)D[mesIndx].data(), "LOOP No: %d", i);    
    switch(key){
    case ESCAPE:
    case F(2):
      done = true;
      break;
    case F(3):
      D[mesIndx].set("Setting the message to something more than 40 characters to see what happens");
      break;
    case F(6):
      D.move();
      break;
    }
  }
  console.clear();
  console.display("First Lineedit data:", 8, 1);
  console.display((char*)D[2].data(), 9, 0);
  console.display("Second Lineedit data:", 10, 1);
  console.display((char*)D[4].data(), 11, 0);
  console.display("Third Linedit data:", 14, 1);
  console.display((char*)D[6].data(), 15, 0);
  console.pause();
  return 0;
}