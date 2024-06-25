/********************************************
  Project: TAGA
  File: main.cpp
  Purporse: log generator
  Programmer: Pogrebitskiy Georgiy, GP4
              Anna Marysheva
*********************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

struct Person
{
  string Name; /* only cyrillic and latin symbols, first letter is capital*/
  string PhoneNumber;   /* 12 symbols: first symbol - '+', second symbol - '7', the rest make up the number */
  vector<int> Relationships;

  /* 'Person' constructor */
  Person(
    const string &NewName = "", const string &NewNumber = "",
    const vector<int> &RelationShips = {}
  ) :
    Name(NewName),
    PhoneNumber(NewNumber),
    Relationships()
  {
  } /* end of 'Person' constructor */
};

string GenName( void )
{
  static vector <string> names = {
    "София", "Иван", "Глеб", "Ева", "Андрей", "Николай", "Мария", "Данил", "Иван",
    "Павел", "Артемий", "Дмитрий", "Дмиртий", "Арсений", "Тимофей", "Демьян", "Роман", "Анна", "Алиса", "Яна",
    "Тимур", "Прохор", "Александр", "Фома"
  };

  static vector <string> surnames = {
    "Юсупова", "Шумаков", "Чурагулов", "Ченцов", "Ходакова", "Хлопотных", "Хам", "Фрицлер", "Урядников", 
    "Тонких", "Страдин", "Степанов", "Смирнов", "Егоров", "Савков", "Семенов", "Русинов", "Романова", "Погребицкий", "Пальчикова",
    "Красный", "Белый", "Черных", "Иванов", "Прусаков", "Шостакович", "Менделеев"
  };

  string name = names[rand() % names.size()];
  string surname = surnames[rand() % surnames.size()];

  return name + ' ' + surname;
}

string GenNumber( void ) 
{
  vector <string> numeral = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

  string number = "+7(";
  for (int i = 0; i < 3; i++)
    number += numeral[rand() % 10];

  number += ")";
  for (int i = 0; i < 3; i++)
    number += numeral[rand() % 10];

  number += "-";
  for (int i = 0; i < 2; i++)
    number += numeral[rand() % 10];

  number += "-";
  for (int i = 0; i < 2; i++)
    number += numeral[rand() % 10];

  return number;
}

vector<Person *> network;

void GenNtwrk( int peopleCount )
{
  for (int i = 0; i < peopleCount; i++)
  {
    if (network[i] != nullptr)
      delete network[i];
    network[i] = new Person(GenName(), GenNumber());
  }

  for (int i = 0; i < peopleCount; i++)
    for (int j = i + 1; j < peopleCount; j++)
    {
      int chance = rand();
      if (chance <= 12000)
      {
        network[i]->Relationships.push_back(j);
        network[j]->Relationships.push_back(i);
      }
    }
}

string GenMsg( void )
{
  vector<string> words = {"this", "is", "a", "real", "conversation", "not", "just", "gibberish", "word", "how", "are", "foo", "bongos",
    "pineapple", "robot", "juice", "random", "school", "&^@@#%", "fuzzy"
  };

  string result = "";

  for (int i = 0; i < 12; i++)
  {
    string word = words[rand() % words.size()];
    if (i == 0)
      word[i] -= 32;
    result += word + (i == 11 ? "." : " ");
  }

  return result;
}

int main( void )
{
  int 
    pplCount = 700,
    interactions = 10000000;

  for (int i = 0; i < pplCount; i++)
    network.push_back(nullptr);
  
  srand((unsigned int)time(nullptr));

  GenNtwrk(pplCount);

  string FileName = "test5.txt";

  ofstream OutStream(FileName);

  if (!OutStream.is_open())
  {
    cout << "Couldn't create log file";
    getchar();
    return 0;
  }

  for (int i = 0; i < interactions; i++)
  {
    Person *Sender = network[rand() % network.size()];
    Person *Adressee = network[ Sender->Relationships[rand() % Sender->Relationships.size()] ];

    OutStream << "INFO: User " << Sender->Name
      << " with phone number " << Sender->PhoneNumber
      << " sent a message to user " << Adressee->Name
      << " with phone number " << Adressee->PhoneNumber
      << "\nMessage: " << GenMsg() << "\n~~~\n";
  }

  cout << "Generated log with " << interactions << " messages into " << FileName;
  getchar();

  return 0;
}