#include "Cards.h"

// void randomizeListOfCardKeys(std::vector<std::string> & list)
// {
//   static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
//   std::shuffle(list.begin(), list.end(), mt);
// }

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

  // randomizeListOfCardKeys(list);

  return list;
}

std::unordered_map<std::string, int const> mapOfCards()
{
  // I believe the bracket style below has to be used because std::unordered_map::operater[] only has overloads for non-const type.
  std::unordered_map<std::string, int const> deck{
    {"Ace of Clubs", 11},
    {"Ace of Spades", 11},
    {"Ace of Diamonds", 11},
    {"Ace of Hearts", 11},
    {"King of Clubs", 10},
    {"King of Spades", 10},
    {"King of Diamonds", 10},
    {"King of Hearts", 10},
    {"Queen of Clubs", 10},
    {"Queen of Spades", 10},
    {"Queen of Diamonds", 10},
    {"Queen of Hearts", 10},
    {"Jack of Clubs", 10},
    {"Jack of Spades", 10},
    {"Jack of Diamonds", 10},
    {"Jack of Hearts", 10},
    {"Ten of Clubs", 10},
    {"Ten of Spades", 10},
    {"Ten of Diamonds", 10},
    {"Ten of Hearts", 10},
    {"Nine of Clubs", 9},
    {"Nine of Spades", 9},
    {"Nine of Diamonds", 9},
    {"Nine of Hearts", 9},
    {"Eight of Clubs", 8},
    {"Eight of Spades", 8},
    {"Eight of Diamonds", 8},
    {"Eight of Hearts", 8},
    {"Seven of Clubs", 7},
    {"Seven of Spades", 7},
    {"Seven of Diamonds", 7},
    {"Seven of Hearts", 7},
    {"Six of Clubs", 6},
    {"Six of Spades", 6},
    {"Six of Diamonds", 6},
    {"Six of Hearts", 6},
    {"Five of Clubs", 5},
    {"Five of Spades", 5},
    {"Five of Diamonds", 5},
    {"Five of Hearts", 5},
    {"Four of Clubs", 4},
    {"Four of Spades", 4},
    {"Four of Diamonds", 4},
    {"Four of Hearts", 4},
    {"Three of Clubs", 3},
    {"Three of Spades", 3},
    {"Three of Diamonds", 3},
    {"Three of Hearts", 3},
    {"Two of Clubs", 2},
    {"Two of Spades", 2},
    {"Two of Diamonds", 2},
    {"Two of Hearts", 2}
  };
  // 
  // If I were to use non-const mapped type, then the code below would work with different function declaration.
  //
  // std::unordered_map<std::string, int> deck;
  // deck["Ace of Clubs"] = 11;
  // deck["Ace of Spades"] = 11;
  // deck["Ace of Diamonds"] = 11;
  // deck["Ace of Hearts"] = 11;
  // deck["King of Clubs"] = 10;
  // deck["King of Spades"] = 10;
  // deck["King of Diamonds"] = 10;
  // deck["King of Hearts"] = 10;
  // deck["Queen of Clubs"] = 10;
  // deck["Queen of Spades"] = 10;
  // deck["Queen of Diamonds"] = 10;
  // deck["Queen of Hearts"] = 10;
  // deck["Jack of Clubs"] = 10;
  // deck["Jack of Spades"] = 10;
  // deck["Jack of Diamonds"] = 10;
  // deck["Jack of Hearts"] = 10;
  // deck["Ten of Clubs"] = 10;
  // deck["Ten of Spades"] = 10;
  // deck["Ten of Diamonds"] = 10;
  // deck["Ten of Hearts"] = 10;
  // deck["Nine of Clubs"] = 9;
  // deck["Nine of Spades"] = 9;
  // deck["Nine of Diamonds"] = 9;
  // deck["Nine of Hearts"] = 9;
  // deck["Eight of Clubs"] = 8;
  // deck["Eight of Spades"] = 8;
  // deck["Eight of Diamonds"] = 8;
  // deck["Eight of Hearts"] = 8;
  // deck["Seven of Clubs"] = 7;
  // deck["Seven of Spades"] = 7;
  // deck["Seven of Diamonds"] = 7;
  // deck["Seven of Hearts"] = 7;
  // deck["Six of Clubs"] = 6;
  // deck["Six of Spades"] = 6;
  // deck["Six of Diamonds"] = 6;
  // deck["Six of Hearts"] = 6;
  // deck["Five of Clubs"] = 5;
  // deck["Five of Spades"] = 5;
  // deck["Five of Diamonds"] = 5;
  // deck["Five of Hearts"] = 5;
  // deck["Four of Clubs"] = 4;
  // deck["Four of Spades"] = 4;
  // deck["Four of Diamonds"] = 4;
  // deck["Four of Hearts"] = 4;
  // deck["Three of Clubs"] = 3;
  // deck["Three of Spades"] = 3;
  // deck["Three of Diamonds"] = 3;
  // deck["Three of Hearts"] = 3;
  // deck["Two of Clubs"] = 2;
  // deck["Two of Spades"] = 2;
  // deck["Two of Diamonds"] = 2;
  // deck["Two of Hearts"] = 2;
  return deck;
}
