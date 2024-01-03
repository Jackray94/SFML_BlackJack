#include "Cards.h"
#include <unordered_map>
#include <algorithm>

class Deck
{
  public:
    Deck();

    // I think returning by value (vs. const value) is best here so RVO copy elision is not prevented. 
    [[nodiscard]] std::string currentCardName() const;

    // I think returning by value (vs. const value) is best here so RVO copy elision is not prevented. 
    [[nodiscard]] int currentCardValue() const;

    void increaseIndex();

    void resetIndex();

    // I believe returning by const reference is best whereever possible, to avoid copies.
    [[nodiscard]] int const & getIndex() const;

    // void randomizeListOfCardKeys();
    
  private:
    // I believe the move ctor will be called when creating deckOfCards.
    std::unordered_map<std::string, int const> deckOfCards;

    // I believe the move ctor will be called here as well.
    std::vector<std::string> listOfCardKeys;
    int index;
};

