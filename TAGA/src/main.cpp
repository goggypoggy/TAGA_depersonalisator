/********************************************
  Project: TAGA
  File: main.cpp
  Purporse: default main file
  Programmer: Egorov Timofey, TE1
              Perfileva Alice, AP4
              Pogrebitskiy Georgiy, GP4
*********************************************/

#include <encryptor/encryptor.h>

int main() {
  string 
    InputFile = "input_sample.txt",
    OutputFile = "output.txt",
    MapFile = "map.txt";

  cout << "Input log file name: ";
  cin >> InputFile;

  OutputFile = InputFile + ".encrypted.txt";
  MapFile = InputFile + ".cryptmap.txt";

  taga::Scanner* Scan = new taga::Scanner();
 
  Scan->CreateText(InputFile);
  Scan->TextToMessages();

  taga::Parser* Messages = new taga::Parser(Scan);

  Messages->Parse();

  taga::Encryptor* Encryption = new taga::Encryptor(Messages);

  Encryption->Encrypt(OutputFile, MapFile);

  cout << "Encrypted " << InputFile << " into " << OutputFile << endl;
  cout << "Encryption map stored in " << MapFile << endl;

  getchar();
  getchar();
}