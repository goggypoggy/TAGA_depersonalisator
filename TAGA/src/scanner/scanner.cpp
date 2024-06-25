/********************************************
  Project: TAGA
  File: scanner.cpp
  Purporse: scanner class function
  Programmer: Egorov Timofey, TE1
              Pogrebitskiy Georgiy, GP4
*********************************************/

#include <scanner/scanner.h>

/*** Class methods ***/
/* Read text from a file function */
void taga::Scanner::CreateText( const string &FileName )
{
  ifstream F(FileName);

  if (!F.is_open())
  {
    cout << "Couldn't open " << FileName << endl << "Can't get logs" << endl;
    return;
  }

  stringstream ss;
  ss << F.rdbuf();
  Text = ss.str();
} /* end of 'CreateText' function */

/* Parse text into individual message sequence function */
void taga::Scanner::TextToMessages( void )
{
  int N = Text.size();
  string mes;
  int current_pos = 0;

  while (current_pos < N)
  {
    if (Text[current_pos] == '~' && Text[current_pos + 1] == '~' && Text[current_pos + 2] == '~')
    {
      Messages.push_back(mes);
      mes = "";
      current_pos += 3;
    }
    else
      mes += Text[current_pos];
    current_pos++;
  }
} /* end of 'TextToMessages' function*/