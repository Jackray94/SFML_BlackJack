#include "Cards.h"
#include <unordered_map>

class Deck
{
  public:
    Deck()
      : deckOfCards{mapOfCards()}, listOfCardKeys{randomizedCardKeys()}, index{0}
    {
    }
    std::string currentCardName(){return listOfCardKeys[index];}
    int currentCardValue(){return deckOfCards[listOfCardKeys[index]];}
    void increaseIndex(){index++;}
    
  private:
    std::unordered_map<std::string, int> deckOfCards;
    std::vector<std::string> listOfCardKeys;
    int index;
};

