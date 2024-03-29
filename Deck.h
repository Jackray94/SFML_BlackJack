#ifndef DECK_H
#define DECK_H

#include "Cards.h"
#include "imageFileHandle.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <random>

namespace bj{

using MapSCards = std::unordered_map<std::string, Cards>;

class Deck
{
  public:
    Deck();

    void loadMapWithCardData();

    void randomizeListOfCardKeys();

    [[nodiscard]] MapSCards::const_iterator foundCard();

    // I think returning by value (vs. const value) is best here so RVO copy elision is not prevented. 
    [[nodiscard]] std::string currentCardName() const;

    // I think returning by value (vs. const value) is best here so RVO copy elision is not prevented. 
    [[nodiscard]] int currentCardValue() const;

    void increaseIndex();

    void resetIndex();

    // I believe returning by const reference is best whereever possible, to avoid copies but copying simple type is trivial. 
    [[nodiscard]] int getIndex() const;

  private:
    [[nodiscard]] std::unique_ptr<sf::Texture> loadMapWithCardPNGTextures(std::string const & key);
    [[nodiscard]] int loadMapWithCardScore(std::string const & key);

    std::vector<std::string> stringCardKeys;
    MapSCards deckOfCards;
    int index;
};

} //namespace bj


#endif
