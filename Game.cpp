#include "Game.h"
#include "cardKeys.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

Game::Game()
  : mWindow(sf::VideoMode(800, 600), "sfml application"), 
    mapOfCardTextures{std::unordered_map<cardKeys, std::unique_ptr<sf::Texture>>()}, 
    listOfCardKeys{cardsAsKeys()},
    listOfFileNames{filesInDirectory()},
    cardsAsSprites{},
    mFont{},
    mText{},
    slotScaleFactor{0.25f},
    slotXDeltaFactor{125.f},
    slotYDeltaFactor{182.f}
{
}

void Game::Run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
  loadCardTexturesToMap(mapOfCardTextures, listOfCardKeys, listOfFileNames);
  randomizeListOfCardKeys(listOfCardKeys);
  loadFont();
  buttonToDrawCard();

  int countButtonToDrawClicks = 0;
  while(mWindow.isOpen()){
    processEvents(countButtonToDrawClicks);
    timeSinceLastUpdate += clock.restart();
    while(timeSinceLastUpdate > TimePerFrame){
      timeSinceLastUpdate -= TimePerFrame;
      processEvents(countButtonToDrawClicks);
    }
    render(cardsAsSprites);
  }
}

void Game::processEvents(int & countButtonToDrawClicks)
{
  sf::Event event;
  while(mWindow.pollEvent(event)){
    if(event.type == sf::Event::Closed){
      mWindow.close();
    }
    sf::IntRect rectangleCollisionButtonToDrawCard(mText.getPosition().x, mText.getPosition().y, mText.getGlobalBounds().width, mText.getGlobalBounds().height);
    if(rectangleCollisionButtonToDrawCard.contains(sf::Mouse::getPosition(mWindow)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
      handleButtonToDrawInput(countButtonToDrawClicks);
      countButtonToDrawClicks++;
    }
    else{
      mText.setFillColor(sf::Color::Red);
    }
  }
}

void Game::render(std::vector<sf::Sprite> const & cardsAsSptires)
{
  mWindow.clear();
  mWindow.draw(mText);
  for(auto const & card : cardsAsSptires){
    mWindow.draw(card);
  }
  mWindow.display();
}

void Game::loadFont()
{
  if(!mFont.loadFromFile("arial.ttf")){
    std::cout << "Error loading font" << '\n';
  }
}

void Game::buttonToDrawCard()
{
  mText.setFont(mFont);
  mText.setString("Select here to draw card\n");
  mText.setCharacterSize(48);
  mText.setPosition(300,400);
  mText.setFillColor(sf::Color::Red);
}

void Game::handleButtonToDrawInput(int & countButtonToDrawClicks){
  mText.setFillColor(sf::Color::Blue);
  updateSpritesFromTextureMapOfCards(cardsAsSprites, listOfCardKeys[countButtonToDrawClicks], mapOfCardTextures);
  updatePositionOfCardSprites(cardsAsSprites, countButtonToDrawClicks);
}

  void Game::updatePositionOfCardSprites(std::vector<sf::Sprite> & cardsAsSprites, int & countButtonToDrawClicks)
{  /* |_|_|_|_|_|
  ** |_|_|_|_|_| A 5x2 layout of sprites on window is made here. 
  */
  if(countButtonToDrawClicks >= 10){
    std::cerr << "Program can only work for up to 10 cards\n";
    exit(1);
  }
  if(countButtonToDrawClicks < 5){
    cardsAsSprites[countButtonToDrawClicks].setScale(slotScaleFactor, slotScaleFactor); // set slot scale regardless of slot number
    cardsAsSprites[countButtonToDrawClicks].move(countButtonToDrawClicks * slotXDeltaFactor, 0.f); 
  }
  else{
    cardsAsSprites[countButtonToDrawClicks].setScale(slotScaleFactor, slotScaleFactor); // set slot scale regardless of slot number
    cardsAsSprites[countButtonToDrawClicks].move(countButtonToDrawClicks%5 * slotXDeltaFactor, slotYDeltaFactor); // only x movement for <= 5
  }

}


void Game::updateSpritesFromTextureMapOfCards(std::vector<sf::Sprite> & cardsAsSprites, cardKeys const & cardKey, std::unordered_map<cardKeys, std::unique_ptr<sf::Texture>> & mapOfCardsTextures)
{
  auto found = mapOfCardsTextures.find(cardKey);
  if(found == mapOfCardsTextures.end()){
    std::cerr << "Failed to access map key/value pair";
    exit(1);
  }

  generateSprite(cardsAsSprites, *found); 
}

void Game::generateSprite(std::vector<sf::Sprite> & cardsAsSprites, std::pair<const cardKeys, std::unique_ptr<sf::Texture>> & kv)
{
  cardsAsSprites.push_back(sf::Sprite(*kv.second));
}

void Game::loadCardTexturesToMap(std::unordered_map<cardKeys, std::unique_ptr<sf::Texture>> & mapOfCardsTextures, std::vector<cardKeys> const & listOfCardKeys, std::vector<std::string> const & listOfFileValues)
{
  int count = 0;
  // loop through the 52 files. They're sorted alphabetically, and enums are made to match this sorted file vector for its vector of keys
  // For each file name, create Texture object pointer and load each file.
  for(std::vector<std::string>::const_iterator i = listOfFileValues.begin(), e = listOfFileValues.end(); i != e; ++i){
    auto ptr = std::make_unique<sf::Texture>();
    if(!ptr->loadFromFile(listOfFileValues[count])){
      std::cerr << "Failed to open " << listOfFileValues[count] << '\n';
      exit(1);
    }
    //insert each pair into map. Check insertion happened okay by true/false of .second of returned std::pair
    auto successfulPairFromInsertion = mapOfCardsTextures.insert(std::make_pair(listOfCardKeys[count], std::move(ptr))); 
    if(!successfulPairFromInsertion.second){
      std::cerr << "Failed to insert " << listOfFileValues[count] << '\n';
      exit(1);
    }
    count++;
  }
}

void Game::randomizeListOfCardKeys(std::vector<cardKeys> & listOfCardKeys)
{
  static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
  std::shuffle(listOfCardKeys.begin(), listOfCardKeys.end(), mt);
}



