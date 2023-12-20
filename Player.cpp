#ifndef PLAYER_H
#define PLAYER_H

#include "Player.h"

Player::Player(std::string_view givenName)
  :
    Score{0}, Name{givenName}, Hand{std::vector<std::string>()}, aceCount{0}, Bust{false}, maxScore{21}, myTurn{false}, flagIfEarlyBlackJackHasBeenChecked{false}
{
}

int Player::getScore() const
{
  return Score;
}

void Player::pushCardToHand(std::string const & card)
{
  Hand.emplace_back(card);
}


int Player::numberOfCardsInHand()
{
  return static_cast<int>(Hand.size());
}

void Player::updateScore(int val)
{
  //keep track of newly drawn Aces. Once score exceeds 21 if player has Aces then their Aces can equal 1 instead of 11 (subtract 10 from score)
  if(val == 11){
    aceCount++;
  }

  Score += val;

  if(Score > maxScore){
    if(aceCount > 0){
      aceCount--;
      Score -= 10;
    }
    else{
      Bust = true;
    }
  }
}













#endif
