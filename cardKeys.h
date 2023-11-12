#ifndef CARDKEYS_H
#define CARDKEYS_H

#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>

#define numCardsInDeck 52

enum class cardKeys
{
  ten_Of_Clubs,
  ten_Of_Diamonds,
  ten_Of_Hearts,
  ten_Of_Spades,
  two_Of_Clubs,
  two_Of_Diamonds,
  two_Of_Hearts,
  two_Of_Spades,
  three_Of_Clubs,
  three_Of_Diamonds,
  three_Of_Hearts,
  three_Of_Spades,
  four_Of_Clubs,
  four_Of_Diamonds,
  four_Of_Hearts,
  four_Of_Spades,
  five_Of_Clubs,
  five_Of_Diamonds,
  five_Of_Hearts,
  five_Of_Spades,
  six_Of_Clubs,
  six_Of_Diamonds,
  six_Of_Hearts,
  six_Of_Spades,
  seven_Of_Clubs,
  seven_Of_Diamonds,
  seven_Of_Hearts,
  seven_Of_Spades,
  eight_Of_Clubs,
  eight_Of_Diamonds,
  eight_Of_Hearts,
  eight_Of_Spades,
  nine_Of_Clubs,
  nine_Of_Diamonds,
  nine_Of_Hearts,
  nine_Of_Spades,
  ace_Of_Clubs,
  ace_Of_Diamonds,
  ace_Of_Hearts,
  ace_Of_Spades,
  jack_Of_Clubs,
  jack_Of_Diamonds,
  jack_Of_Hearts,
  jack_Of_Spades,
  king_Of_Clubs,
  king_Of_Diamonds,
  king_Of_Hearts,
  king_Of_Spades,
  queen_Of_Clubs,
  queen_Of_Diamonds,
  queen_Of_Hearts,
  queen_Of_Spades
};

std::vector<cardKeys> randomizedCardsAsKeys();

#endif
