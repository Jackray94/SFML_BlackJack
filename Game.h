#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string_view>
#include <memory>
#include <algorithm>

#include "imageFileHandle.h"
#include "Deck.h"
#include "Player.h"

class Game
{
  public:
    Game();
    void Run();

  private:
    void processEvents();
    void render();
    void loadFont();
    void updateSpritesFromTextureMapOfCards();
    void updatePositionOfCardSprites();
    void updateGameLogic();
    void initButtonToHit();
    void initButtonToStay();
    void initDialogueBox();
    void updateDialogueBox();
    void initDealerNamePlate();
    void initPlayer1NamePlate();
    void updatePlayerBustToNamePlate();
    void initPlayer2NamePlate();
    void initPlayer3NamePlate();
    void initTextBoxes();
    void setupDeck();
    void drawCardsAndUpdateDeck(bj::Player & p);
    void updatePlayerEarlyBlackJackToNamePlate();

    struct Coordinate
    {
      float left;
      float right;
    };

  private:
    unsigned int const taskBarOffset;
    unsigned int const screenWidth;
    unsigned int const screenHeight;
    Coordinate centerPosition;
    Coordinate dialogueBoxPosition;
    Coordinate buttonToHitPosition;
    Coordinate buttonToStayPosition;
    Coordinate dealerNamePlatePosition;
    Coordinate player1NamePlatePosition;
    Coordinate player2NamePlatePosition;
    Coordinate player3NamePlatePosition;
    Coordinate dealerCardPlacement;
    Coordinate player1CardPlacement;
    Coordinate player2CardPlacement;
    Coordinate player3CardPlacement;
    sf::RenderWindow mWindow;
    std::vector<sf::Sprite> cardsAsSprites;
    sf::Font mFont;
    sf::Text dealerNamePlate;
    sf::Text player1NamePlate;
    sf::Text player2NamePlate;
    sf::Text player3NamePlate;
    sf::Text mDialogueBox;
    sf::Text ButtonToHit;
    sf::Text ButtonToStay;
    bool hitPressed;
    bool stayPressed;
    enum class State{init, dealerFirstCardReveal, dealFirstCardsToPlayers, evaluateEarlyBlackJack, promptPlayerMoves, dealerFinalTurn};
    State currentState;
    float const slotScaleFactor;
    float const slotXDeltaFactor;
    float const slotYDeltaFactor;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time TimePerFrame;
    sf::Clock dialogueClock;
    sf::Time dialogueDelay;
    sf::Time diaglogueRate;

    bj::Deck Deck;
    bj::Player dealer{"Laylah"};
    bj::Player p1{"Toby"};
    bj::Player p2{"Lofi"};
    bj::Player p3{"Cricket"};

    std::vector<int> dealerSprites;
    std::vector<int> player1Sprites;
    std::vector<int> player2Sprites;
    std::vector<int> player3Sprites;

    int const winningScore;
};

#endif
