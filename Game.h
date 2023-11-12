#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "imageFileHandle.h"
#include "cardKeys.h"

class Game
{
  public:
    Game();
    void Run();

  private:
    void processEvents(int & countButtonToDrawClicks);
    void render(std::vector<sf::Sprite> const & cardsAsSptires);
    void loadFont();
    void buttonToDrawCard();
    void handleButtonToDrawInput(int & countButtonToDrawClicks);
    void loadCardTexturesToMap(std::unordered_map<cardKeys, std::unique_ptr<sf::Texture>> & mapOfCardsTextures, std::vector<cardKeys> const & listOfCardKeys, std::vector<std::string> const & listOfFileValues);
    void updateSpritesFromTextureMapOfCards(std::vector<sf::Sprite> & cardsAsSprites, cardKeys const & cardKey, std::unordered_map<cardKeys, std::unique_ptr<sf::Texture>> & mapOfCardsTextures);
    void generateSprite(std::vector<sf::Sprite> & cardsAsSprites, std::pair<const cardKeys, std::unique_ptr<sf::Texture>> & kv);
  void updatePositionOfCardSprites(std::vector<sf::Sprite> & cardsAsSprites, int & countButtonToDrawClicks);

  private:
    sf::RenderWindow mWindow;
    std::unordered_map<cardKeys, std::unique_ptr<sf::Texture>> mapOfCardTextures;    std::vector<cardKeys> listOfRandomCardKeys;
    std::vector<std::string> listOfFileNames;
    std::vector<sf::Sprite> cardsAsSprites;
    sf::Font mFont;
    sf::Text mText;
    float const slotScaleFactor;
    float const slotXDeltaFactor;
    float const slotYDeltaFactor;
};

#endif
