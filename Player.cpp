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


int Player::numberOfCardsInHand() const
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


std::ostream& operator<<(std::ostream & out, Player const & p)
{
  out << p.Name << " has cards:\n";
  for(std::size_t i = 0, e = p.Hand.size()-1; i != e; ++i){
    out <<  p.Hand[i] << "/ ";
  }
  out << p.Hand[p.Hand.size()-1] << '\n';
  out << "Score is " << p.Score << '\n';
  if(p.hasBust() == true){
    out << p.Name << " has Bust\n";
  }
  return out;
}

bool Player::hasEarlyBlackJack() const{return Score == maxScore;}

bool Player::hasBust() const {return Score > 21;}

bool const & Player::isTurn() const {return myTurn;}

bool Player::requiredToHit() const {return Score < 17;}

void Player::setTurn(bool x){myTurn = x;}

std::string const & Player::getName() const{return Name;}

bool Player::checkedEarlyBlackJack() const {return (flagIfEarlyBlackJackHasBeenChecked == true);}

void Player::updateEarlyBlackJackCheck(bool status) {flagIfEarlyBlackJackHasBeenChecked = status;}
