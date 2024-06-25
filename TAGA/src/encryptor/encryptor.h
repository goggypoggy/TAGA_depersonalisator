/********************************************
  Project: TAGA
  File: encryptor.h
  Purporse: scanner class
  Programmer: Perfileva Alice, AP4
              Pogrebitskiy Georgiy, GP4
*********************************************/

#ifndef __encryption_h_
#define __encryption_h_

#include <parser/parser.h>

/* main project namespace */
namespace taga
{
  /* encryptor class */
  class Encryptor
  {
  public:
    Parser* Parsed; /* pointer to parser object */
    map<string, string>
      NameMap,  /* Map of masked names */
      NumberMap; /* Map of masked phone numbers */

    /* encryption constructor */
    Encryptor( Parser* NewParser = nullptr ) :
      Parsed(NewParser)
    {
    } /* end of 'encryption' constructor */
  
  private:
    string Convert( char type, const string &Object );
    void EncryptMessage( Message* Msg, ofstream &OutputFile );

  public:
    void Encrypt( const string &OutputFile, const string &MapFile );
  }; /* end of 'Encryption' class*/
} /* end of 'taga' namespace */
#endif /*__encryption_h_ */
