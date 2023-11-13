#include "cardKeys.h"
/*
* function just returns a vector of enums that identify PNG images of cards. To use this function the PNGs must have their file paths/names loaded into sf::Texture objects in the order they read from in the directory. In otherwords, whatever the order of the files in the diretory is then the enums need to be typed out in that order. EEach enum is pushed into a vector that is returned for use in the program.
*/
std::vector<cardKeys> cardsAsKeys()
{
  auto listOfCards = std::vector<cardKeys>();
  for(int i = 0; i < numCardsInDeck; i++){
    listOfCards.push_back(static_cast<cardKeys>(i));
  }
  return listOfCards;
}
