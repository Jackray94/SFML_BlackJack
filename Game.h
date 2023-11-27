#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <bits/types/cookie_io_functions_t.h>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>

#include "imageFileHandle.h"
#include "Deck.h"
#include "Player.h"

class Game
{
  public:
    Game();
    void Run();

  private:
    void processEvents(int & countButtonToDrawClicks);
    void render();
    void loadFont();
    void handleButtonToDrawInput(int & countButtonToDrawClicks);
    void loadCardTexturesToMap();
    void updateSpritesFromTextureMapOfCards();
    void generateSprite(std::pair<const std::string, std::unique_ptr<sf::Texture>> & kv);
    void updatePositionOfCardSprites();

    // void updateGameLogic(sf::Clock & dialogueClock, sf::Time & dialogueDelay, sf::Time & diaglogueRate, int & countButtonToDrawClicks);
    void updateGameLogic();
    void initButtonToHit();
    void initButtonToStay();
    void initDialogueBox();
    void updateDialogueBox();
    void initDealerName();
    void initPlayerName();
    void drawCard(Player & p);
    void initDealerNamePlate();
    void initPlayer1NamePlate();
    void initPlayer2NamePlate();
    void initPlayer3NamePlate();

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
    // float const centerLeft;
    // float const centerRight;
    sf::RenderWindow mWindow;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> mapOfCardTextures;
    std::vector<std::string> listOfFileNames;
    std::vector<sf::Sprite> cardsAsSprites;
    sf::Font mFont;
    sf::Text mText;
    //////////////////////////
    float const slotScaleFactor;
    // float const cardScale;
    float const slotXDeltaFactor;
    // float const cardXDelta;
    float const slotYDeltaFactor;
    // float const cardYDelta;
    /////////////////////////////

    sf::Text dealerNamePlate;
    sf::Text player1NamePlate;
    sf::Text player2NamePlate;
    sf::Text player3NamePlate;
    sf::Text mDialogueBox;
    sf::Text ButtonToHit;
    sf::Text ButtonToStay;
    bool hitPressed;
    bool stayPressed;
    enum class State{init, dealerFirstCardReveal, dealFirstCardsToPlayers, promptPlayerMoves};
    State currentState;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time TimePerFrame;
    sf::Clock dialogueClock;
    sf::Time dialogueDelay;
    sf::Time diaglogueRate;
    Deck Deck;
    //eventually will receive list of players from user and store each player object inside a vector
    Player dealer{"Dealer"};
    Player p1{"Jim"};
    Player p2{"Bobby"};
    Player p3{"Anthony"};
    
    std::vector<int> dealerSprites;
    std::vector<int> player1Sprites;
    std::vector<int> player2Sprites;
    std::vector<int> player3Sprites;
};

#endif
