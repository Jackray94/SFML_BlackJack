#include "Game.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <exception>
#include <sstream>

Game::Game()
  :
    taskBarOffset{50},
    screenWidth{sf::VideoMode::getDesktopMode().width},
    screenHeight{sf::VideoMode::getDesktopMode().height},
    centerPosition{screenWidth / 2.f, (screenHeight / 2.f) - taskBarOffset},
    dialogueBoxPosition{centerPosition.left, centerPosition.right + 350},
    buttonToHitPosition{centerPosition.left + 600, centerPosition.right + 400},
    buttonToStayPosition{centerPosition.left - 600, centerPosition.right + 400},
    dealerNamePlatePosition{centerPosition.left, centerPosition.right - 225},
    player1NamePlatePosition{centerPosition.left - 600, centerPosition.right + 250},
    player2NamePlatePosition{centerPosition.left + 600, centerPosition.right + 250},
    player3NamePlatePosition{centerPosition.left, centerPosition.right + 250},
    dealerCardPlacement{dealerNamePlatePosition.left, dealerNamePlatePosition.right - 150},
    player1CardPlacement{player1NamePlatePosition.left, player1NamePlatePosition.right - 150},
    player2CardPlacement{player2NamePlatePosition.left, player2NamePlatePosition.right - 150},
    player3CardPlacement{player3NamePlatePosition.left, player2NamePlatePosition.right -150},
    mWindow(sf::VideoMode(screenWidth, screenHeight), "BlackJack"),
    mapOfCardTextures{std::unordered_map<std::string, std::unique_ptr<sf::Texture>>()}, 
    listOfFileNames{filesInDirectory()},
    cardsAsSprites{},
    mFont{},
    dealerNamePlate{},
    player1NamePlate{},    
    player2NamePlate{},    
    player3NamePlate{},    
    mDialogueBox{},
    ButtonToHit{},
    ButtonToStay{},
    hitPressed{false},
    stayPressed{false},
    currentState{State::init},
    slotScaleFactor{0.25f},
    slotXDeltaFactor{125.f},
    slotYDeltaFactor{182.f},
    clock{},
    timeSinceLastUpdate{sf::Time::Zero},
    TimePerFrame{sf::seconds(1.f/60.f)},
    dialogueClock{},
    dialogueDelay{sf::seconds(1.5f)},
    diaglogueRate{},
    dealerSprites{std::vector<int>()},
    player1Sprites{std::vector<int>()},
    player2Sprites{std::vector<int>()},
    player3Sprites{std::vector<int>()},
    winningScore{21}
{
}

void Game::Run()
{
  setupDeck();
  loadFont();
  initTextBoxes();

  while(mWindow.isOpen()){
    updateGameLogic();
    processEvents();
    timeSinceLastUpdate += clock.restart();
    while(timeSinceLastUpdate > TimePerFrame){
      timeSinceLastUpdate -= TimePerFrame;
      processEvents();
    }
    render();
  }
}

void Game::processEvents()
{
  sf::Event event;
  while(mWindow.pollEvent(event)){
    if(event.type == sf::Event::Closed){
      mWindow.close();
    }
    sf::IntRect rectangleHitCollision(
      (ButtonToHit.getPosition().x - ButtonToHit.getLocalBounds().width/2), 
      (ButtonToHit.getPosition().y - ButtonToHit.getLocalBounds().height/2), 
      (ButtonToHit.getLocalBounds().width), 
      (ButtonToHit.getLocalBounds().height)
    );
    sf::IntRect rectangleStayCollision(
      (ButtonToStay.getPosition().x - ButtonToStay.getLocalBounds().width/2), 
      (ButtonToStay.getPosition().y - ButtonToStay.getLocalBounds().height/2), 
      (ButtonToStay.getLocalBounds().width), 
      (ButtonToStay.getLocalBounds().height)
    );
    if(currentState == State::promptPlayerMoves){
      if(rectangleHitCollision.contains(sf::Mouse::getPosition(mWindow)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        ButtonToHit.setFillColor(sf::Color::Blue);
        hitPressed = true;
      }
      else{
        ButtonToHit.setFillColor(sf::Color::Red);
      }

      if(rectangleStayCollision.contains(sf::Mouse::getPosition(mWindow)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        ButtonToStay.setFillColor(sf::Color::Blue);
        stayPressed = true;
      }
      else{
        ButtonToStay.setFillColor(sf::Color::Red);
      }
    }
    else{
      ButtonToHit.setFillColor(sf::Color::Red);
      ButtonToStay.setFillColor(sf::Color::Red);
    }
  }
}

void Game::render()
{
  mWindow.clear(sf::Color::Green);
  mWindow.draw(player3NamePlate);
  mWindow.draw(player2NamePlate);
  mWindow.draw(player1NamePlate);
  mWindow.draw(dealerNamePlate);
  mWindow.draw(mDialogueBox);
  mWindow.draw(ButtonToStay);
  mWindow.draw(ButtonToHit);
  for(auto const & card : cardsAsSprites){
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

void Game::updatePlayerEarlyBlackJackToNamePlate()
{
  std::ostringstream message;
  if(p1.isTurn()){
    message << p1.getName() << "\nBlackJack\n";
    player1NamePlate.setString(message.str());
    player1NamePlate.setOrigin(player1NamePlate.getLocalBounds().left + player1NamePlate.getLocalBounds().width/2, player1NamePlate.getLocalBounds().top + player1NamePlate.getLocalBounds().height/2);
    player1NamePlate.setPosition(player1NamePlatePosition.left, player1NamePlatePosition.right);
  }
  else if(p2.isTurn()){
    message << p2.getName() << "\nBlackJack\n";
    player2NamePlate.setString(message.str());
    player2NamePlate.setOrigin(player2NamePlate.getLocalBounds().left + player2NamePlate.getLocalBounds().width/2, player2NamePlate.getLocalBounds().top + player2NamePlate.getLocalBounds().height/2);
    player2NamePlate.setPosition(player2NamePlatePosition.left, player2NamePlatePosition.right);
  }
  else if(p3.isTurn()){
    message << p3.getName() << "\nBlackJack\n";
    player3NamePlate.setString(message.str());
    player3NamePlate.setOrigin(player3NamePlate.getLocalBounds().left + player3NamePlate.getLocalBounds().width/2, player3NamePlate.getLocalBounds().top + player3NamePlate.getLocalBounds().height/2);
    player3NamePlate.setPosition(player3NamePlatePosition.left, player3NamePlatePosition.right);
  }
}

void Game::updatePlayerBustToNamePlate()
{
  std::ostringstream message;
  if(p1.isTurn()){
    message << p1.getName() << "\nBUST\n";
    player1NamePlate.setString(message.str());
    player1NamePlate.setOrigin(player1NamePlate.getLocalBounds().left + player1NamePlate.getLocalBounds().width/2, player1NamePlate.getLocalBounds().top + player1NamePlate.getLocalBounds().height/2);
    player1NamePlate.setPosition(player1NamePlatePosition.left, player1NamePlatePosition.right);
  }
  else if(p2.isTurn()){
    message << p2.getName() << "\nBUST\n";
    player2NamePlate.setString(message.str());
    player2NamePlate.setOrigin(player2NamePlate.getLocalBounds().left + player2NamePlate.getLocalBounds().width/2, player2NamePlate.getLocalBounds().top + player2NamePlate.getLocalBounds().height/2);
    player2NamePlate.setPosition(player2NamePlatePosition.left, player2NamePlatePosition.right);
  }
  else if(p3.isTurn()){
    message << p3.getName() << "\nBUST\n";
    player3NamePlate.setString(message.str());
    player3NamePlate.setOrigin(player3NamePlate.getLocalBounds().left + player3NamePlate.getLocalBounds().width/2, player3NamePlate.getLocalBounds().top + player3NamePlate.getLocalBounds().height/2);
    player3NamePlate.setPosition(player3NamePlatePosition.left, player3NamePlatePosition.right);
  }
}

void Game::updateDialogueBox()
{
  diaglogueRate = dialogueClock.getElapsedTime();
  if(diaglogueRate >= dialogueDelay){
    std::ostringstream message;
    switch(currentState)
    {
      case State::init:
        dialogueClock.restart();
        break;
      case State::dealerFirstCardReveal:
        mDialogueBox.setString("Dealer draws their first card\n");
        mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
        mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        dialogueClock.restart();
        break;
      case State::dealFirstCardsToPlayers:
        break;
      case State::evaluateEarlyBlackJack:
        while(dialogueClock.getElapsedTime() <= dialogueDelay){
          //wait for 1 second
        }
        if(p1.hasEarlyBlackJack() && !p1.checkedEarlyBlackJack()){
          message << p1.getName() << " has 21 and has won.\n";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
          p1.updateEarlyBlackJackCheck(true);
        }
        else if(p2.hasEarlyBlackJack() && !p2.checkedEarlyBlackJack()){
          message << p2.getName() << " has 21 and has won.\n";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
          p2.updateEarlyBlackJackCheck(true);
        }
        else if(p3.hasEarlyBlackJack() && !p3.checkedEarlyBlackJack()){
          message << p3.getName() << " has 21 and has won.\n";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
          p3.updateEarlyBlackJackCheck(true);
        }
        break;
      case State::promptPlayerMoves:
        if(p1.isTurn()){
          message << p1.getName() << " you have score of " << p1.getScore() << ".\n\nDo you want to Hit or Stay?";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        }
        if(p2.isTurn()){
          message << p2.getName() << " you have score of " << p2.getScore() << ".\n\nDo you want to Hit or Stay?";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        }
        if(p3.isTurn()){
          message << p3.getName() << " you have score of " << p3.getScore() << ".\n\nDo you want to Hit or Stay?";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        }
        break;
      case State::dealerFinalTurn:
          message << dealer.getName() << " draws remaining cards\n";
          mDialogueBox.setString(message.str());
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        break;
    }
  }
}

void Game::initPlayer3NamePlate()
{
  player3NamePlate.setFont(mFont);
  player3NamePlate.setCharacterSize(36);
  player3NamePlate.setString(p3.getName());
  player3NamePlate.setOrigin(player3NamePlate.getLocalBounds().left + player3NamePlate.getLocalBounds().width/2, player3NamePlate.getLocalBounds().top + player3NamePlate.getLocalBounds().height/2);
  player3NamePlate.setPosition(player3NamePlatePosition.left, player3NamePlatePosition.right);
  player3NamePlate.setFillColor(sf::Color::Red);
}

void Game::initPlayer2NamePlate()
{
  player2NamePlate.setFont(mFont);
  player2NamePlate.setCharacterSize(36);
  player2NamePlate.setString(p2.getName());
  player2NamePlate.setOrigin(player2NamePlate.getLocalBounds().left + player2NamePlate.getLocalBounds().width/2, player2NamePlate.getLocalBounds().top + player2NamePlate.getLocalBounds().height/2);
  player2NamePlate.setPosition(player2NamePlatePosition.left, player2NamePlatePosition.right);
  player2NamePlate.setFillColor(sf::Color::Red);
}

void Game::initPlayer1NamePlate()
{
  player1NamePlate.setFont(mFont);
  player1NamePlate.setCharacterSize(36);
  player1NamePlate.setString(p1.getName());
  player1NamePlate.setOrigin(player1NamePlate.getLocalBounds().left + player1NamePlate.getLocalBounds().width/2, player1NamePlate.getLocalBounds().top + player1NamePlate.getLocalBounds().height/2);
  player1NamePlate.setPosition(player1NamePlatePosition.left, player1NamePlatePosition.right);
  player1NamePlate.setFillColor(sf::Color::Red);
}

void Game::initDealerNamePlate()
{
  dealerNamePlate.setFont(mFont);
  dealerNamePlate.setCharacterSize(36);
  dealerNamePlate.setString(dealer.getName());
  dealerNamePlate.setOrigin(dealerNamePlate.getLocalBounds().left + dealerNamePlate.getLocalBounds().width/2, dealerNamePlate.getLocalBounds().top + dealerNamePlate.getLocalBounds().height/2);
  dealerNamePlate.setPosition(dealerNamePlatePosition.left, dealerNamePlatePosition.right);
  dealerNamePlate.setFillColor(sf::Color::Red);
}

void Game::initDialogueBox()
{
  mDialogueBox.setFont(mFont);
  mDialogueBox.setCharacterSize(36);
  mDialogueBox.setString("Starting BlackJack\n");
  mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
  mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
  mDialogueBox.setFillColor(sf::Color::Red);
}

void Game::initButtonToStay()
{

  ButtonToStay.setFont(mFont);
  ButtonToStay.setString("Stay?\n");
  ButtonToStay.setCharacterSize(48);
  ButtonToStay.setOrigin(ButtonToStay.getLocalBounds().left + ButtonToStay.getLocalBounds().width/2, ButtonToStay.getLocalBounds().top + ButtonToStay.getLocalBounds().height/2);
  ButtonToStay.setPosition(buttonToStayPosition.left, buttonToStayPosition.right);
  ButtonToStay.setFillColor(sf::Color::Red);
}

void Game::initButtonToHit()
{
  ButtonToHit.setFont(mFont);
  ButtonToHit.setString("Hit?\n");
  ButtonToHit.setCharacterSize(48);
  ButtonToHit.setOrigin(ButtonToHit.getLocalBounds().left + ButtonToHit.getLocalBounds().width/2, ButtonToHit.getLocalBounds().top + ButtonToHit.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text (its origin) at the center of the screen. 
  ButtonToHit.setPosition(buttonToHitPosition.left, buttonToHitPosition.right);
  ButtonToHit.setFillColor(sf::Color::Red);
}

void Game::updatePositionOfCardSprites()
{ 
  int spritesIDX = Deck.getIndex();
  int maxCardsPerRow = 3;
  cardsAsSprites[spritesIDX].setScale(slotScaleFactor, slotScaleFactor); // set slot scale regardless of slot number
  cardsAsSprites[spritesIDX].setOrigin(cardsAsSprites[spritesIDX].getLocalBounds().left + cardsAsSprites[spritesIDX].getLocalBounds().width/2, cardsAsSprites[spritesIDX].getLocalBounds().top + cardsAsSprites[spritesIDX].getLocalBounds().height/2);
  switch(currentState)
  {
    case State::init:
      break;
    case State::dealerFirstCardReveal:
      dealerSprites.push_back(spritesIDX);
      cardsAsSprites[dealerSprites[0]].setPosition(dealerCardPlacement.left, dealerCardPlacement.right);
      break;
    case State::dealFirstCardsToPlayers:
      if(p1.isTurn()){ 
        player1Sprites.push_back(spritesIDX);
        player1CardPlacement.left -= (player1Sprites.size() - 1) * slotXDeltaFactor / 2;
        for(int i = 0; i < player1Sprites.size(); i++){
          cardsAsSprites[player1Sprites[i]].setPosition(player1CardPlacement.left + i*slotXDeltaFactor, player1CardPlacement.right);
        }
      }
      if(p2.isTurn()){
        player2Sprites.push_back(spritesIDX);
        player2CardPlacement.left -= (p2.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player2Sprites.size(); i++){
          cardsAsSprites[player2Sprites[i]].setPosition(player2CardPlacement.left + i*slotXDeltaFactor, player2CardPlacement.right);
        }
      }
      if(p3.isTurn()){
        player3Sprites.push_back(spritesIDX);
        player3CardPlacement.left -= (p3.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player3Sprites.size(); i++){
          cardsAsSprites[player3Sprites[i]].setPosition(player3CardPlacement.left + i*slotXDeltaFactor, player3CardPlacement.right);
        }
      }
      break;
    case State::evaluateEarlyBlackJack:
      break;
    case State::promptPlayerMoves:
      if(p1.isTurn() && hitPressed){
        player1Sprites.push_back(spritesIDX);
        if(player1Sprites.size() <= maxCardsPerRow){
          player1CardPlacement.left -= slotXDeltaFactor / 2;
        }
        for(int i = 0; i < player1Sprites.size(); i++){
          if(i < maxCardsPerRow){
            cardsAsSprites[player1Sprites[i]].setPosition(player1CardPlacement.left + i*slotXDeltaFactor, player1CardPlacement.right);
          }
          else{
            cardsAsSprites[player1Sprites[i]].setPosition(cardsAsSprites[player1Sprites[i%maxCardsPerRow]].getPosition().x, cardsAsSprites[player1Sprites[i%maxCardsPerRow]].getPosition().y - slotYDeltaFactor);
          }
        }
      }
      if(p2.isTurn() && hitPressed){
        player2Sprites.push_back(spritesIDX);
        if(player2Sprites.size() <= maxCardsPerRow){
          player2CardPlacement.left -= slotXDeltaFactor / 2;
        }
        for(int i = 0; i < player2Sprites.size(); i++){
          if(i < maxCardsPerRow){
            cardsAsSprites[player2Sprites[i]].setPosition(player2CardPlacement.left + i*slotXDeltaFactor, player2CardPlacement.right);
          }
          else{
            cardsAsSprites[player2Sprites[i]].setPosition(cardsAsSprites[player2Sprites[i%maxCardsPerRow]].getPosition().x, cardsAsSprites[player2Sprites[i%maxCardsPerRow]].getPosition().y - slotYDeltaFactor);
          }
        }
      }
      if(p3.isTurn() && hitPressed){
        player3Sprites.push_back(spritesIDX);
        if(player3Sprites.size() <= maxCardsPerRow){
          player3CardPlacement.left -= slotXDeltaFactor / 2;
        }
        for(int i = 0; i < player3Sprites.size(); i++){
          if(i < maxCardsPerRow){
            cardsAsSprites[player3Sprites[i]].setPosition(player3CardPlacement.left + i*slotXDeltaFactor, player3CardPlacement.right);
          }
          else{
            cardsAsSprites[player3Sprites[i]].setPosition(cardsAsSprites[player3Sprites[i%maxCardsPerRow]].getPosition().x, cardsAsSprites[player3Sprites[i%maxCardsPerRow]].getPosition().y - slotYDeltaFactor);
          }
        }
      }
        break;
      case State::dealerFinalTurn:
        dealerSprites.push_back(spritesIDX);
        dealerCardPlacement.left -= slotXDeltaFactor / 2;
        for(int i = 0; i < dealerSprites.size(); i++){
          cardsAsSprites[dealerSprites[i]].setPosition(dealerCardPlacement.left + i*slotXDeltaFactor, dealerCardPlacement.right);
        }
        break;
  }
}


void Game::updateSpritesFromTextureMapOfCards()
{
  auto found = mapOfCardTextures.find(Deck.currentCardName());
  if(found == mapOfCardTextures.end()){
    std::cerr << "Failed to access map key/value pair";
    exit(1);
  }
  generateSprite(*found); 
}

void Game::generateSprite(std::pair<const std::string, std::unique_ptr<sf::Texture>> & kv)
{
  cardsAsSprites.push_back(sf::Sprite(*kv.second));
}

void Game::loadCardTexturesToMap()
{
  int count = 0;
  for(auto const & texture : listOfFileNames){
    auto ptr = std::make_unique<sf::Texture>();
    if(!ptr->loadFromFile(listOfFileNames[count])){
      std::cerr << "Failed to open " << listOfFileNames[count] << '\n';
      exit(1);
    }
    auto successfulPairFromInsertion = mapOfCardTextures.insert(std::make_pair(Deck.currentCardName(), std::move(ptr))); 
    Deck.increaseIndex();
    if(!successfulPairFromInsertion.second){
      std::cerr << "Failed to insert " << listOfFileNames[count] << '\n';
      exit(1);
    }
    count++;
  }
  // for(std::vector<std::string>::const_iterator i = listOfFileNames.begin(), e = listOfFileNames.end(); i != e; ++i){
  //   auto ptr = std::make_unique<sf::Texture>();
  //   if(!ptr->loadFromFile(listOfFileNames[count])){
  //     std::cerr << "Failed to open " << listOfFileNames[count] << '\n';
  //     exit(1);
  //   }
  //   auto successfulPairFromInsertion = mapOfCardTextures.insert(std::make_pair(Deck.currentCardName(), std::move(ptr))); 
  //   Deck.increaseIndex();
  //   if(!successfulPairFromInsertion.second){
  //     std::cerr << "Failed to insert " << listOfFileNames[count] << '\n';
  //     exit(1);
  //   }
  //   count++;
  // }
  Deck.resetIndex();
}

void Game::updateGameLogic()
{
    switch(currentState)
    {
      case State::init:
        updateDialogueBox();
        currentState = Game::State::dealerFirstCardReveal;
        break;
      case State::dealerFirstCardReveal:
        updateDialogueBox(); 
        drawCardsAndUpdateDeck(dealer);
        currentState = Game::State::dealFirstCardsToPlayers;
        break;

      case State::dealFirstCardsToPlayers:
        p1.setTurn(true);
        drawCardsAndUpdateDeck(p1);
        p1.setTurn(false);

        p1.setTurn(true);
        drawCardsAndUpdateDeck(p1);
        p1.setTurn(false);
      
        p2.setTurn(true);
        drawCardsAndUpdateDeck(p2);
        p2.setTurn(false);

        p2.setTurn(true);
        drawCardsAndUpdateDeck(p2);
        p2.setTurn(false);

        p3.setTurn(true);
        drawCardsAndUpdateDeck(p3);
        p3.setTurn(false);

        p3.setTurn(true);
        drawCardsAndUpdateDeck(p3);
        p3.setTurn(false);

        //P1 turn is set to kick off next state
        p1.setTurn(true);
        currentState = State::evaluateEarlyBlackJack;

        break;
      case State::evaluateEarlyBlackJack: 
        if(!p1.hasEarlyBlackJack() && !p2.hasEarlyBlackJack() && !p3.hasEarlyBlackJack()){
          currentState = State::promptPlayerMoves;
        }
        else if(p1.hasEarlyBlackJack() && !p1.checkedEarlyBlackJack()){
          updateDialogueBox();
        }
        else if(p2.hasEarlyBlackJack() && !p2.checkedEarlyBlackJack()){
          updateDialogueBox();
        }
        else if(p3.hasEarlyBlackJack() && !p3.checkedEarlyBlackJack()){
          updateDialogueBox();
        }
        else{
          currentState = State::promptPlayerMoves;
          dialogueClock.restart();
          while(dialogueClock.getElapsedTime() <= 2.0f * dialogueDelay){
            //wait for 2 second
          }
        }
        break;
      case State::promptPlayerMoves: 
        if(p1.isTurn() && !p1.hasEarlyBlackJack()){
          updateDialogueBox();
          if(hitPressed){
            p1.pushCardToHand(Deck.currentCardName());
            p1.updateScore(Deck.currentCardValue());
            updateSpritesFromTextureMapOfCards();
            updatePositionOfCardSprites();
            Deck.increaseIndex();
            hitPressed = false;
          }
          if(stayPressed){
            p1.setTurn(false);
            p2.setTurn(true);
            stayPressed = false;
          }
          if(p1.hasBust()){
            updatePlayerBustToNamePlate();
            p1.setTurn(false);
            p2.setTurn(true);
          }
        }
        else if(p1.isTurn() && p1.hasEarlyBlackJack()){
          updatePlayerEarlyBlackJackToNamePlate();
          p1.setTurn(false);
          p2.setTurn(true);
        }
        else if(p2.isTurn() && !p2.hasEarlyBlackJack()){
          updateDialogueBox();
          if(hitPressed){
            p2.pushCardToHand(Deck.currentCardName());
            p2.updateScore(Deck.currentCardValue());
            updateSpritesFromTextureMapOfCards();
            updatePositionOfCardSprites();
            Deck.increaseIndex();
            hitPressed = false;
          }
          if (stayPressed){
            p2.setTurn(false);
            p3.setTurn(true);
            stayPressed = false;
          }
          if(p2.hasBust()){
            updatePlayerBustToNamePlate();
            p2.setTurn(false);
            p3.setTurn(true);
          }
        }
        else if(p2.isTurn() && p2.hasEarlyBlackJack()){
          updatePlayerEarlyBlackJackToNamePlate();
          p2.setTurn(false);
          p3.setTurn(true);
        }
        else if(p3.isTurn() && !p3.hasEarlyBlackJack()){
          updateDialogueBox();
          if(hitPressed){
            p3.pushCardToHand(Deck.currentCardName());
            p3.updateScore(Deck.currentCardValue());
            updateSpritesFromTextureMapOfCards();
            updatePositionOfCardSprites();
            Deck.increaseIndex();
            hitPressed = false;
          }
          if (stayPressed){
            stayPressed = false;
            p3.setTurn(false);
            dealer.setTurn(true);
          }
          if(p3.hasBust()){
            updatePlayerBustToNamePlate();
            p3.setTurn(false);
            dealer.setTurn(true);
          }
        }
        else if(p3.isTurn() && p3.hasEarlyBlackJack()){
          updatePlayerEarlyBlackJackToNamePlate();
          p3.setTurn(false);
          dealer.setTurn(true);
        }
        else if(dealer.isTurn()){
          currentState = State::dealerFinalTurn;
        }
        break;
      case State::dealerFinalTurn:
        updateDialogueBox();
        if(/*dealer score less than 17*/dealer.requiredToHit()){
          dealer.pushCardToHand(Deck.currentCardName());
          dealer.updateScore(Deck.currentCardValue());
          updateSpritesFromTextureMapOfCards();
          updatePositionOfCardSprites();
          Deck.increaseIndex();
        }
        break;
    }
}

void Game::initTextBoxes()
{
  initDialogueBox();
  initButtonToHit();
  initButtonToStay();
  initDealerNamePlate();
  initPlayer1NamePlate();
  initPlayer2NamePlate();
  initPlayer3NamePlate();
}

void Game::setupDeck()
{
  loadCardTexturesToMap();
  // TODO --> Since i'm on dev branch with the goal of combining 2 std::unordered_maps<string, int> and std::unordered_maps<string, std::unique_ptr<sf::Texture>> into 1 std::unordered_map<std::string, newStructType>
  //
  // I think I'll put the new struct into Cards.h/.cpp -> will need to have score, std::unique_ptr<sf::Texture>
  //
  // If combining hash maps then Deck.cpp and Cards.cpp can combine, and from here I would call imageFile function to get list of file names / string keys
  Deck.randomizeListOfCardKeys();
}

void Game::drawCardsAndUpdateDeck(Player & p)
{
  p.pushCardToHand(Deck.currentCardName());
  p.updateScore(Deck.currentCardValue());
  updateSpritesFromTextureMapOfCards();
  updatePositionOfCardSprites();
  Deck.increaseIndex();
}
