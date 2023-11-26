#include "Cards.h"

std::vector<std::string> cardKeys()
{
  auto list = std::vector<std::string>  
  {
    "Ten of Clubs",  "Ten of Diamonds", "Ten of Hearts", "Ten of Spades",
    "Two of Clubs",  "Two of Diamonds", "Two of Hearts", "Two of Spades",
    "Three of Clubs",  "Three of Diamonds", "Three of Hearts", "Three of Spades",
    "Four of Clubs",  "Four of Diamonds", "Four of Hearts", "Four of Spades",
    "Five of Clubs",  "Five of Diamonds", "Five of Hearts", "Five of Spades",
    "Six of Clubs",  "Six of Diamonds", "Six of Hearts", "Six of Spades",
    "Seven of Clubs",  "Seven of Diamonds", "Seven of Hearts", "Seven of Spades",
    "Eight of Clubs",  "Eight of Diamonds", "Eight of Hearts", "Eight of Spades",
    "Nine of Clubs",  "Nine of Diamonds", "Nine of Hearts", "Nine of Spades",
    "Ace of Clubs",  "Ace of Diamonds", "Ace of Hearts", "Ace of Spades",
    "Jack of Clubs",  "Jack of Diamonds", "Jack of Hearts", "Jack of Spades",
    "King of Clubs",  "King of Diamonds", "King of Hearts", "King of Spades",
    "Queen of Clubs",  "Queen of Diamonds", "Queen of Hearts", "Queen of Spades"
  };
  return list;
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
