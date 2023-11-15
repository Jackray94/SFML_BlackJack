#include "Cards.h"
#include <unordered_map>

class Deck
{
  public:
    Deck()
      : deckOfCards{mapOfCards()}, randomListOfCardKeys{randomizedCardKeys()}, index{0}
    {
    }
    std::string currentCardName(){return randomListOfCardKeys[index];}
    int currentCardValue(){return deckOfCards[randomListOfCardKeys[index]];}
    void increaseIndex(){index++;}
    
  private:
    std::unordered_map<std::string, int> deckOfCards;
    std::vector<std::string> randomListOfCardKeys;
    int index;
};

