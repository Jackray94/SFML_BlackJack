#include "Cards.h"
#include <unordered_map>
#include <algorithm>

class Deck
{
  public:
    Deck()
      : deckOfCards{mapOfCards()}, listOfCardKeys{cardKeys()}, index{0}
    {
    }
    std::string currentCardName(){return listOfCardKeys[index];}
    int currentCardValue(){return deckOfCards[listOfCardKeys[index]];}
    void increaseIndex(){index++;}
    void resetIndex(){index = 0;}
    int getIndex(){return index;}
    void randomizeListOfCardKeys()
    {
      static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
      std::shuffle(listOfCardKeys.begin(), listOfCardKeys.end(), mt);
    }
    
  private:
    std::unordered_map<std::string, int> deckOfCards;
    std::vector<std::string> listOfCardKeys;
    int index;
};

