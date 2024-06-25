/********************************************
  Project: TAGA
  File: parser.h
  Purporse: parser class
  Programmer: Egorov Timofey, TE1
              Pogrebitskiy Georgiy, GP4
*********************************************/

#ifndef __parser_h_
#define __parser_h_

#include <scanner/scanner.h>

/* main project namespace */
namespace taga
{
  /* structure describe one human */
  struct Person
  {
    friend class Scanner;

    string Name; /* only cyrillic and latin symbols, first letter is capital*/
    string PhoneNumber;   /* 12 symbols: first symbol - '+', second symbol - '7', the rest make up the number */

    /* 'Person' constructor */
    Person(string NewName, string NewNumber) :
      Name(NewName),
      PhoneNumber(NewNumber)
    {
    } /* end of 'Person' constructor */

    /* empty constructor */
    Person()
    {
    } /* end of empty constructor */

    /* default destructor */
    ~Person()
    {
    } /* end of default destructor */
  }; /*end of 'Person' structure*/

  /* one message from input file */
  struct Message
  {
    Person* Sender;   /* sender */
    Person* Addresee; /* addressee */
    string TextMessage;

    /* 'Message' constructor */
    Message(Person* NewSender = nullptr, Person* NewAdressee = nullptr, string Text = "") :
      Sender(NewSender), Addresee(NewAdressee), TextMessage(Text)
    {
    } /* end of 'Message' constructor */

    /* 'Message' destructor */
    ~Message()
    {
      delete Sender;
      delete Addresee;
    }
  }; /* end of 'Message' class */

  class Parser {
  public:
    vector<Message*> Messages; /* result of parsing */
    Scanner* Scan; /* pointer to scaner object */

    /* default constructor */
    Parser( Scanner* NewScan = nullptr ) : Messages(), Scan(NewScan)
    {
    } /* end of default 'Parser' constructor */

  private:
    /* Parse one message function */
    void ParseMessage( const string &Text );
  
  public:
    /* Parse message array function */
    void Parse( void );
  };
} /* end of 'taga' namespace */


#endif /* parser_h_ */