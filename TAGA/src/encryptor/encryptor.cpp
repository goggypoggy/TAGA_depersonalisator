/********************************************
  Project: TAGA
  File: encryptor.cpp
  Purporse: encryption class function
  Programmer: Perfileva Alice, AP4
              Pogrebitskiy Georgiy, GP4
*********************************************/

#include <encryptor/encryptor.h>

/*** Inner functions ***/
/* Convert number into a 12-symbol number function */
string IntToNumber( unsigned long long X )
{
  string Number = to_string(X);

  int N = Number.length();
  string Zeroes = string(10 - min(10, N), '0');
  Number = Zeroes + Number;

  return Number;
}

string StylizeNumber( const string &Number )
{
  string result = "+7(";
  
  int i = 0;
  for (; i < 3; i++)
    result += Number[i];

  result += ")";

  for (; i < 6; i++)
    result += Number[i];

  result += "-";

  for (; i < 8; i++)
    result += Number[i];

  result += "-";

  for (; i < 10; i++)
    result += Number[i];

  return result;
}

/*** Class methods ***/
/* Converting our message function */
string taga::Encryptor::Convert( char type, const string &Object )
{
  static unsigned long long 
    NameInd = 0,
    PhoneInd = 0;

  string result;

  switch (type)
  {
  /* 'n' for names */
  case 'n':
    if (NameMap.find(Object) != NameMap.end())
      return NameMap[Object];
    result = IntToNumber(NameInd++);
    NameMap[Object] = result;
    return result;
  /* 'p' for phone numbers */
  case 'p':
    if (NumberMap.find(Object) != NumberMap.end())
      return NumberMap[Object];
    result = IntToNumber(PhoneInd++);
    NumberMap[Object] = result;
    return result;
  default:
    return "itemTypeError";
  }
} /* end of 'Convert' function */

/* Single message encryption function */
void taga::Encryptor::EncryptMessage( Message* Msg, ofstream &OutputFile )
{
  /* two pointers for convinience */
  Person 
    *Snd = Msg->Sender,
    *Adr = Msg->Addresee;

  string
    Sender = Convert('n', Snd->Name),
    Addressee = Convert('n', Adr->Name),
    PhoneS = Convert('p', Snd->PhoneNumber),
    PhoneA = Convert('p', Adr->PhoneNumber);

  OutputFile << "INFO: User " << Sender
    << " with phone number " << StylizeNumber(PhoneS)
    << " sent a message to user " << Addressee
    << " with phone number " << StylizeNumber(PhoneA)
    << "\nMessage: " << Msg->TextMessage << "~~~\n";
}

/* Full log encryption function */
void taga::Encryptor::Encrypt( const string &OutputFile, const string &MapFile )
{
  /* Encrypt the logs */
  ofstream OutStream(OutputFile);

  if (!OutStream.is_open())
    cout << "Could not open file " << OutputFile << endl << "Couldn't output encrypted log" << endl;

  for (auto *msg : Parsed->Messages)
    EncryptMessage(msg, OutStream);

  OutStream.close();

  /* Output encryption map */
  ofstream MapStream(MapFile);

  if (!MapStream.is_open())
    cout << "Could not open file " << MapFile << endl << "Couldn't output encryption map" << endl;

  MapStream << "--==<<{{ ENCRYPTION MAP }}>>==--";
  
  MapStream << endl << endl << "NAME MAP:" << endl;
  for (pair<string, string> it : NameMap)
    MapStream << endl << it.first << " ---> " << it.second;

  MapStream << endl << endl << "NUMBER MAP:" << endl;
  for (pair<string, string> it : NumberMap)
    MapStream << endl << StylizeNumber(it.first) << " ---> " << StylizeNumber(it.second);

  MapStream.close();
} /* end of 'Encrypt' function */
