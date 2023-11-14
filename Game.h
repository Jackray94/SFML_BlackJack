#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>

#include "imageFileHandle.h"
#include "cardKeys.h"
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
    void buttonToDrawCard();
    void handleButtonToDrawInput(int & countButtonToDrawClicks);
    void loadCardTexturesToMap();
    void updateSpritesFromTextureMapOfCards(cardKeys const & cardKey);
    void generateSprite(std::pair<const cardKeys, std::unique_ptr<sf::Texture>> & kv);
    void updatePositionOfCardSprites(int & countButtonToDrawClicks);
    void randomizeListOfCardKeys();

    void updateGameLogic();

  private:
    sf::RenderWindow mWindow;
    std::vector<cardKeys> listOfCardKeys;
    std::vector<std::string> listOfFileNames;
    std::vector<sf::Sprite> cardsAsSprites;
    sf::Font mFont;
    sf::Text mText;
    float const slotScaleFactor;
    float const slotXDeltaFactor;
    float const slotYDeltaFactor;

    Deck Deck;
    //eventually will receive list of players from user and store each player object inside a vector
    Player p1{"Jim"};
    Player p2{"Bobby"};
};

#endif
