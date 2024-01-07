#include "Deck.h"
#include "imageFileHandle.h"

Deck::Deck()
  : cards{}, stringCardKeys{ListOfFilesInDirectory()}
{
}

void Deck::loadMapWithCardData()
{
  int cardCount = 0;
  for(auto const & texture : stringCardKeys){
    loadMapWithCardPNGTextures(cardCount);
    auto successfulPairFromInsertion = deckOfCards.insert(std::make_pair(stringCardKeys[cardCount], std::move(ptr))); 
    Deck.increaseIndex();
    if(!successfulPairFromInsertion.second){
      std::cerr << "Failed to insert " << stringCardKeys[cardCount] << '\n';
      exit(1);
    }
    cardCount++;
  }
  Deck.resetIndex();
}

void Deck::loadMapWithCardPNGTextures(std::string const & key)
{
  for(auto const & texture : stringCardKeys){
    auto ptr = std::make_unique<sf::Texture>();
    if(!ptr->loadFromFile(stringCardKeys[IDX])){
      std::cerr << "Failed to open " << stringCardKeys[IDX] << '\n';
      exit(1);
    }
  }
}

void Deck::loadMapWithCardScore()
{
  switch()
}

/*#include "Deck.h"

Deck::Deck()
  : deckOfCards{mapOfCards()}, listOfCardKeys{cardKeys()}, index{0}
{
}

// Vector has no issue, unlike Unordered_map, with operator[] and const elements. This is because std::vector::operator[] has overloads to handle const, unlike std::unordered_map::operator[].
//
// The point made above is good-to-know but not relevent bceause vector listOfCardKeys doesn't have const elements in this example.

// Since I can't return by const reference, I believe it is preferred to even still avoid returning by const value. This is because you want to allow for RVO (return value optimization) copy elision - never return by const value because you can screw up copy elision (meaning using const can prevent move semantics (copy elision)) 
std::string Deck::currentCardName() const{return listOfCardKeys[index];}


int Deck::currentCardValue() const
{
  //I can't use std::unordered_map::operater[] with const. Also I control the setup which ensures there will not be a need to check if past-the-end iterator is returned (i.e. key not found).
  auto found = deckOfCards.find(listOfCardKeys[index]);
  return found->second;
}

void Deck::increaseIndex() {index++;}

void Deck::resetIndex() {index = 0;}

int const & Deck::getIndex() const {return index;}

void Deck::randomizeListOfCardKeys()
{
  static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
  std::shuffle(listOfCardKeys.begin(), listOfCardKeys.end(), mt);
}
*/
