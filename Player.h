#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <string_view>
#include <string>

class Player
{
  public:
    Player(std::string_view givenName) : Score{0}, Name{givenName}, Hand{std::vector<std::string>()}, aceCount{0}, hasBust{false}, maxScore{21}, myTurn{false}{}

    int getScore(){return Score;}
    void pushCardToHand(std::string const & card){Hand.emplace_back(card);}
    int numberOfCardsInHand(){return static_cast<int>(Hand.size());}
    void updateScore(int val)
    {
      //keep track of newly drawn Aces. Once score exceeds 21 if player has Aces then their Aces can equal 1 instead of 11(score minus 10)
      if(val == 11){
        aceCount++;
      }
      Score += val;
      if(Score > maxScore){
        if(aceCount == 0){
          hasBust = true;
        }
        else{
          Score -= 10;
          aceCount--;
        }
      }
    }

    std::string toSFTextSetString()
    {
      // std::string_view update{Name + "has Cards:\n"};
      std::string update{Name + "has Cards:\n"};
      //The '/' shouldn't follow the last element
      for(std::size_t i = 0; i < Hand.size() - 1; ++i){
        update +=  Hand[i] + "/ ";
      }
      update += Hand[Hand.size()-1] + '\n';
      update += "Score is ";
      update += Score + '\n';
      if(hasBust == true){
        update += Name += " has Bust\n";
      }
      return update;
    }

    friend std::ostream& operator<<(std::ostream & out, Player const & p)
    {
      out << p.Name << " has cards:\n";
      for(std::size_t i = 0, e = p.Hand.size()-1; i != e; ++i){
        out <<  p.Hand[i] << "/ ";
      }
      out << p.Hand[p.Hand.size()-1] << '\n';
      out << "Score is " << p.Score << '\n';
      if(p.hasBust == true){
        out << p.Name << " has Bust\n";
      }
      return out;
    }

    bool hasBlackJack(){return Score == maxScore;}
    bool hasBust(){return Score > 21;}
    bool isTurn(){return myTurn;}
    void setTurn(bool x){myTurn = x;}
    std::string getName(){return Name;}

  private:
    int Score;
    std::string Name;
    std::vector<std::string> Hand;
    int aceCount;
    bool hasBust;
    int const maxScore;
    bool myTurn;
    
};

#endif
