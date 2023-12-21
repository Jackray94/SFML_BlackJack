#ifndef DECK_H
#define DECK_H

#include "Deck.h"


std::string Deck::currentCardName() const{return listOfCardKeys[index];}


int Deck::currentCardValue(){return deckOfCards[listOfCardKeys[index]];}

void Deck::increaseIndex(){index++;}

void Deck::resetIndex(){index = 0;}

int Deck::getIndex() const {return index;}

void Deck::randomizeListOfCardKeys()
{
  static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
  std::shuffle(listOfCardKeys.begin(), listOfCardKeys.end(), mt);
}

#endif
