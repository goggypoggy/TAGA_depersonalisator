/********************************************
  Project: TAGA
  File: parser.cpp
  Purporse: parser function
  Programmer: Egorov Timofey, TE1
              Pogrebitskiy Georgiy, GP4
*********************************************/

#include <parser/parser.h>

/*** Inner functions ***/
/* Find name and surname from fixed position in text function */
void FindName( int pos, const string &Text, string &Name )
{
  Name = "";

  while (Text[pos] != ' ') 
    Name += Text[pos++];

  Name += ' ';
  pos++;

  while (Text[pos] != ' ')
    Name += Text[pos++];
} /* end of 'FindName' function */
 
/* Find phone number in text string from fixed position function */
void FindNumber( int pos, const string &Text, string &Number )
{
  pos += 3;

  while (Text[pos] != ' ' && Text[pos] != '\n')
  {
    if (Text[pos] != '(' && Text[pos] != ')' && Text[pos] != '-')
      Number += Text[pos];
    pos++;
  }
} /* end of 'FindNumber' function */


/*** Class methods ***/
/* Parse one message function */
void taga::Parser::ParseMessage( const string &Text )
{
  Person* Sender = new Person();
  Person* Addresee = new Person();
  string TextMessage = "";

  int N = (int)Text.size();
  int textstart = 0;
  bool isSendersNumber = true;

  for (int i = 0; i < N; i++)
  {
    if (Text[i] == 'U'
      && ((i + 1) < N && Text[i + 1] == 's')
      && ((i + 2) < N && Text[i + 2] == 'e')
      && ((i + 3) < N && Text[i + 3] == 'r')
      )
    {
      string Name;
      FindName(i + 5, Text, Name);
      Sender->Name = Name;
    }

    if (Text[i] == 'u'
      && ((i + 1) < N && Text[i + 1] == 's')
      && ((i + 2) < N && Text[i + 2] == 'e')
      && ((i + 3) < N && Text[i + 3] == 'r')
      )
    {
      string Name;
      FindName(i + 5, Text, Name);
      Addresee->Name = Name;
    }

    if (Text[i] == '+'
      && ((i + 1) < N && Text[i + 1] == '7')
      && ((i + 2) < N && Text[i + 2] == '(')
      )
    {
      string Number;
      FindNumber(i, Text, Number);

      if (isSendersNumber)
      {
        isSendersNumber = false;
        Sender->PhoneNumber = Number;
      }
      else
        Addresee->PhoneNumber = Number;
    }

    if (Text[i] == 'g'
      && ((i + 1) < N && Text[i + 1] == 'e')
      && ((i + 2) < N && Text[i + 2] == ':')
      && ((i + 3) < N && Text[i + 3] == ' '))
    {
      textstart = i + 4;
      break;
    }
  }

  for (int i = textstart; i < N; i++)
    TextMessage += Text[i];

  Message* LocalMes = new Message(Sender, Addresee, TextMessage);
  Messages.push_back(LocalMes);
} /* end of 'ParseMessage' function */

/* Parse message array function */
void taga::Parser::Parse( void )
{
 for (int index = 0; index < (int)Scan->Messages.size(); index++)
   ParseMessage(Scan->Messages[index]);
} /* end of 'Parse' function */