/********************************************
  Project: TAGA
  File: scanner.h
  Purporse: scanner class
  Programmer: Egorov Timofey, TE1
              Pogrebitskiy Georgiy, GP4
*********************************************/

#ifndef __scanner_h_
#define __scanner_h_

using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

/* main project namespace */
namespace taga 
{
  /* scanner class */
  class Scanner 
  {
  public:
    string Text;
    vector<string> Messages;

    /* scanner constructor with text file */
    Scanner() : Text(), Messages()
    {
    } /* end of 'scanner' constructor */
    
    /* Read text from a file function */
    void CreateText( const string &FileName );

    /* Parse text into individual message sequence function */
    void TextToMessages( void );
  }; /* end of 'Scanner' class */
} /* end of 'taga' namespace */

#endif /*__scanner_h_ */
