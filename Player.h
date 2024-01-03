#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <string_view>
#include <string>

class Player
{
  public:
    Player(std::string_view givenName);

    [[nodiscard]] int const & getScore() const;
    // int getScore(){return Score;}

    void pushCardToHand(std::string const & card);
    // void pushCardToHand(std::string const & card){Hand.emplace_back(card);}

    [[nodiscard]] int numberOfCardsInHand() const;
    // int numberOfCardsInHand(){return static_cast<int>(Hand.size());}

    void updateScore(int val);

    friend std::ostream& operator<<(std::ostream & out, Player const & p);

    [[nodiscard]] bool hasEarlyBlackJack() const;

    [[nodiscard]] bool hasBust() const;

    [[nodiscard]] bool const & isTurn() const;

    [[nodiscard]] bool requiredToHit() const;

    void setTurn(bool x);

    [[nodiscard]] std::string const & getName() const;

    bool checkedEarlyBlackJack() const;

    void updateEarlyBlackJackCheck(bool status);

  private:
    int Score;
    std::string const Name;
    std::vector<std::string> Hand;
    int aceCount;
    bool Bust;
    int const maxScore;
    bool myTurn;
    bool flagIfEarlyBlackJackHasBeenChecked;
};

#endif
