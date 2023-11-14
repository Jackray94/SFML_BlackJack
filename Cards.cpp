#include "Cards.h"

std::vector<std::string> randomizedCardKeys()
{
  auto list = std::vector<std::string>  
  {
    "Ace of Clubs", "Ace of Spades", "Ace of Diamonds", "Ace of Hearts", 
    "King of Clubs", "King of Spades", "King of Diamonds", "King of Hearts", 
    "Queen of Clubs", "Queen of Spades", "Queen of Diamonds", "Queen of Hearts", 
    "Jack of Clubs", "Jack of Spades", "Jack of Diamonds", "Jack of Hearts", 
    "Ten of Clubs", "Ten of Spades", "Ten of Diamonds", "Ten of Hearts", 
    "Nine of Clubs", "Nine of Spades", "Nine of Diamonds", "Nine of Hearts", 
    "Eight of Clubs", "Eight of Spades", "Eight of Diamonds", "Eight of Hearts", 
    "Seven of Clubs", "Seven of Spades", "Seven of Diamonds", "Seven of Hearts", 
    "Six of Clubs", "Six of Spades", "Six of Diamonds", "Six of Hearts", 
    "Five of Clubs", "Five of Spades", "Five of Diamonds", "Five of Hearts", 
    "Four of Clubs", "Four of Spades", "Four of Diamonds", "Four of Hearts", 
    "Three of Clubs", "Three of Spades", "Three of Diamonds", "Three of Hearts", 
    "Two of Clubs", "Two of Spades", "Two of Diamonds", "Two of Hearts" 
  };
  random(list);
  return list;
}


void random(std::vector<std::string> & deck)
{
  static std::mt19937 mt = std::mt19937(static_cast<std::mt19937::result_type>(std::time(nullptr)));
  std::shuffle(deck.begin(), deck.end(), mt);
}

std::unordered_map<std::string, int> mapOfCards()
{
  std::unordered_map<std::string, int> deck;
  deck["Ace of Clubs"] = 11;
  deck["Ace of Spades"] = 11;
  deck["Ace of Diamonds"] = 11;
  deck["Ace of Hearts"] = 11;
  deck["King of Clubs"] = 10;
  deck["King of Spades"] = 10;
  deck["King of Diamonds"] = 10;
  deck["King of Hearts"] = 10;
  deck["Queen of Clubs"] = 10;
  deck["Queen of Spades"] = 10;
  deck["Queen of Diamonds"] = 10;
  deck["Queen of Hearts"] = 10;
  deck["Jack of Clubs"] = 10;
  deck["Jack of Spades"] = 10;
  deck["Jack of Diamonds"] = 10;
  deck["Jack of Hearts"] = 10;
  deck["Ten of Clubs"] = 10;
  deck["Ten of Spades"] = 10;
  deck["Ten of Diamonds"] = 10;
  deck["Ten of Hearts"] = 10;
  deck["Nine of Clubs"] = 9;
  deck["Nine of Spades"] = 9;
  deck["Nine of Diamonds"] = 9;
  deck["Nine of Hearts"] = 9;
  deck["Eight of Clubs"] = 8;
  deck["Eight of Spades"] = 8;
  deck["Eight of Diamonds"] = 8;
  deck["Eight of Hearts"] = 8;
  deck["Seven of Clubs"] = 7;
  deck["Seven of Spades"] = 7;
  deck["Seven of Diamonds"] = 7;
  deck["Seven of Hearts"] = 7;
  deck["Six of Clubs"] = 6;
  deck["Six of Spades"] = 6;
  deck["Six of Diamonds"] = 6;
  deck["Six of Hearts"] = 6;
  deck["Five of Clubs"] = 5;
  deck["Five of Spades"] = 5;
  deck["Five of Diamonds"] = 5;
  deck["Five of Hearts"] = 5;
  deck["Four of Clubs"] = 4;
  deck["Four of Spades"] = 4;
  deck["Four of Diamonds"] = 4;
  deck["Four of Hearts"] = 4;
  deck["Three of Clubs"] = 3;
  deck["Three of Spades"] = 3;
  deck["Three of Diamonds"] = 3;
  deck["Three of Hearts"] = 3;
  deck["Two of Clubs"] = 2;
  deck["Two of Spades"] = 2;
  deck["Two of Diamonds"] = 2;
  deck["Two of Hearts"] = 2;
  return deck;
}
