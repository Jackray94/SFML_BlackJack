#include "Game.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>

Game::Game()
  :// mWindow(sf::VideoMode(800, 600), "sfml application"), 
    taskBarOffset{50},
    screenWidth{sf::VideoMode::getDesktopMode().width},
    screenHeight{sf::VideoMode::getDesktopMode().height},
    // centerLeft{screenWidth / 2.f},
    // centerRight{(screenHeight / 2.f) - taskBarOffset},
    centerPosition{screenWidth / 2.f, (screenHeight / 2.f) - taskBarOffset},
    dialogueBoxPosition{centerPosition.left, centerPosition.right + 400},
    buttonToHitPosition{centerPosition.left + 600, centerPosition.right + 400},
    buttonToStayPosition{centerPosition.left - 600, centerPosition.right + 400},
    dealerNamePlatePosition{centerPosition.left, centerPosition.right - 200},
    player1NamePlatePosition{centerPosition.left - 600, centerPosition.right + 200},
    player2NamePlatePosition{centerPosition.left + 600, centerPosition.right + 200},
    player3NamePlatePosition{centerPosition.left, centerPosition.right + 200},
    dealerCardPlacement{dealerNamePlatePosition.left, dealerNamePlatePosition.right - 150},
    player1CardPlacement{player1NamePlatePosition.left, player1NamePlatePosition.right - 150},
    player2CardPlacement{player2NamePlatePosition.left, player2NamePlatePosition.right - 150},
    player3CardPlacement{player3NamePlatePosition.left, player2NamePlatePosition.right -150},
    mWindow(sf::VideoMode(screenWidth, screenHeight), "sfml application"),
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
    dialogueDelay{sf::seconds(1.0f)},
    diaglogueRate{},
    dealerSprites{std::vector<int>()},
    player1Sprites{std::vector<int>()},
    player2Sprites{std::vector<int>()},
    player3Sprites{std::vector<int>()}
{
}

void Game::Run()
{
  loadCardTexturesToMap();
  Deck.randomizeListOfCardKeys();
  loadFont(); //<--  take all of  these inits and put htem into a function called init(). It will init these guys and also loop through the player names (or any other dialogue/text/sprite that depends on the number of players)
  initDialogueBox(); //later on change name to updateDialogueBox instead and ripple thourhg consistencies
  initButtonToHit();
  initButtonToStay();
  initDealerNamePlate();
  initPlayer1NamePlate();
  initPlayer2NamePlate();
  initPlayer3NamePlate();
  // initDealerName();
  // initPlayerName(); //<-- for now just assume there is 2 players and a dealer
  int countButtonToDrawClicks = 0;
  while(mWindow.isOpen()){
    // switch(currentState)
    // {
    //   case State::handoutFirstCards:
    //     break;
    //   case State::promptPlayerMoves:
    //     break;
    // }
    //      prompt.......dealer draws 1 card
    //      prompt ......player 1 draws 2 cards.....
    //      prompt ......player 2 draws 2 cards.....
    //      prompt ......player 1 what do you want to hit or stay?      <------thorugh this point everytthing is inside dialogue box that is bottom of screen
    //      hit             stay          <------ this is 2 buttons 
    // updateGameLogic(dialogueClock, dialogueDelay, diaglogueRate, countButtonToDrawClicks);
    updateGameLogic();
    processEvents(countButtonToDrawClicks);
    timeSinceLastUpdate += clock.restart();
    while(timeSinceLastUpdate > TimePerFrame){
      timeSinceLastUpdate -= TimePerFrame;
      processEvents(countButtonToDrawClicks);
    }
    render();
  }
}

void Game::processEvents(int & countButtonToDrawClicks)
{
  sf::Event event;
  while(mWindow.pollEvent(event)){
    if(event.type == sf::Event::Closed){
      mWindow.close();
    }
    // sf::FloatRect rectangleHitCollision(ButtonToHit.getPosition().x, ButtonToHit.getPosition().y, ButtonToHit.getGlobalBounds().width, ButtonToHit.getGlobalBounds().height);
    // sf::FloatRect rectangleStayCollision(ButtonToStay.getPosition().x, ButtonToStay.getPosition().y, ButtonToStay.getGlobalBounds().width, ButtonToStay.getGlobalBounds().height);
    sf::IntRect rectangleHitCollision(ButtonToHit.getPosition().x, ButtonToHit.getPosition().y, ButtonToHit.getGlobalBounds().width, ButtonToHit.getGlobalBounds().height);
    sf::IntRect rectangleStayCollision(ButtonToStay.getPosition().x, ButtonToStay.getPosition().y, ButtonToStay.getGlobalBounds().width, ButtonToStay.getGlobalBounds().height);
    // sf::IntRect rectangleHitCollision(ButtonToHit.getLocalBounds().left, ButtonToHit.getLocalBounds().top, ButtonToHit.getLocalBounds().width, ButtonToHit.getLocalBounds().height);
    // sf::IntRect rectangleStayCollision(ButtonToStay.getLocalBounds().left, ButtonToStay.getLocalBounds().top, ButtonToStay.getLocalBounds().width, ButtonToStay.getLocalBounds().height);
    if(currentState == State::promptPlayerMoves){
      if(rectangleHitCollision.contains(sf::Mouse::getPosition(mWindow)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        ButtonToHit.setFillColor(sf::Color::Blue);
        hitPressed = true;
        countButtonToDrawClicks++;
      }
      else{
        ButtonToHit.setFillColor(sf::Color::Red);
      }

      if(rectangleStayCollision.contains(sf::Mouse::getPosition(mWindow)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        ButtonToStay.setFillColor(sf::Color::Blue);
        stayPressed = true;
        countButtonToDrawClicks++;
      }
      else{
        ButtonToStay.setFillColor(sf::Color::Red);
      }
    }
  }
}

void Game::render()
{
  mWindow.clear();
  // switch(State){
  //   case init_drawFirstCards : 
  //     mWindow.draw(mText);
  //   case state2 : 
  //     mWindow.draw(mText);
  //     mWindow.draw(mText);
  // }
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

void Game::updateDialogueBox()
{
  diaglogueRate = dialogueClock.getElapsedTime();
  if(diaglogueRate >= dialogueDelay){
    switch(currentState)
    {
      case State::init:
        // mDialogueBox.setString("Starting BlackJack\n");
        // mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
        // // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
        // mDialogueBox.setPosition(x_coordZero, y_coordZero + 200);
        dialogueClock.restart();
        // currentState = Game::State::dealerFirstCardReveal; <-- this won't update here. Mkae it update after the cards phyics happens to land a card on the dealer "bucket"
        break;
      case State::dealerFirstCardReveal:
        mDialogueBox.setString("Dealer draws their first card\n");
        mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
        // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
        mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        dialogueClock.restart();
        break;
      case State::dealFirstCardsToPlayers:
        break;
      case State::promptPlayerMoves:
        if(p1.isTurn()){
          mDialogueBox.setString("P1 do you hit or stay?\n");
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        }
        if(p2.isTurn()){
          mDialogueBox.setString("P2 do you hit or stay?\n");
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        }
        if(p3.isTurn()){
          mDialogueBox.setString("P3 do you hit or stay?\n");
          mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
          mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
        }
        break;
    }
  }
  // mDialogueBox.setFillColor(sf::Color::Red);
}

void Game::initPlayer3NamePlate()
{
  player3NamePlate.setFont(mFont);
  player3NamePlate.setCharacterSize(36);
  player3NamePlate.setString("Player 3\n");
  player3NamePlate.setOrigin(player3NamePlate.getLocalBounds().left + player3NamePlate.getLocalBounds().width/2, player3NamePlate.getLocalBounds().top + player3NamePlate.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // player3NamePlate.setPosition(x_coordZero, y_coordZero+200);
  player3NamePlate.setPosition(player3NamePlatePosition.left, player3NamePlatePosition.right);
  player3NamePlate.setFillColor(sf::Color::Red);
}

void Game::initPlayer2NamePlate()
{
  player2NamePlate.setFont(mFont);
  player2NamePlate.setCharacterSize(36);
  player2NamePlate.setString("Player 2\n");
  player2NamePlate.setOrigin(player2NamePlate.getLocalBounds().left + player2NamePlate.getLocalBounds().width/2, player2NamePlate.getLocalBounds().top + player2NamePlate.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // player2NamePlate.setPosition(x_coordZero+600, y_coordZero+200);
  player2NamePlate.setPosition(player2NamePlatePosition.left, player2NamePlatePosition.right);
  player2NamePlate.setFillColor(sf::Color::Red);
}

void Game::initPlayer1NamePlate()
{
  player1NamePlate.setFont(mFont);
  player1NamePlate.setCharacterSize(36);
  player1NamePlate.setString("Player 1\n");
  player1NamePlate.setOrigin(player1NamePlate.getLocalBounds().left + player1NamePlate.getLocalBounds().width/2, player1NamePlate.getLocalBounds().top + player1NamePlate.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // player1NamePlate.setPosition(x_coordZero-600, y_coordZero+200);
  player1NamePlate.setPosition(player1NamePlatePosition.left, player1NamePlatePosition.right);
  player1NamePlate.setFillColor(sf::Color::Red);
}

void Game::initDealerNamePlate()
{
  dealerNamePlate.setFont(mFont);
  dealerNamePlate.setCharacterSize(36);
  dealerNamePlate.setString("Dealer\n");
  dealerNamePlate.setOrigin(dealerNamePlate.getLocalBounds().left + dealerNamePlate.getLocalBounds().width/2, dealerNamePlate.getLocalBounds().top + dealerNamePlate.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // dealerNamePlate.setPosition(x_coordZero, y_coordZero-200);
  dealerNamePlate.setPosition(dealerNamePlatePosition.left, dealerNamePlatePosition.right);
  dealerNamePlate.setFillColor(sf::Color::Red);
}

void Game::initDialogueBox()
{
  mDialogueBox.setFont(mFont);
  mDialogueBox.setCharacterSize(36);
  mDialogueBox.setString("Starting BlackJack\n");
  mDialogueBox.setOrigin(mDialogueBox.getLocalBounds().left + mDialogueBox.getLocalBounds().width/2, mDialogueBox.getLocalBounds().top + mDialogueBox.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // mDialogueBox.setPosition(x_coordZero, y_coordZero + 400);
  mDialogueBox.setPosition(dialogueBoxPosition.left, dialogueBoxPosition.right);
  mDialogueBox.setFillColor(sf::Color::Red);
}

void Game::initButtonToStay()
{

  ButtonToStay.setFont(mFont);
  ButtonToStay.setString("Stay?\n");
  ButtonToStay.setCharacterSize(48);
  // ButtonToStay.setPosition(850,700);
  ButtonToStay.setOrigin(ButtonToStay.getLocalBounds().left + ButtonToStay.getLocalBounds().width/2, ButtonToStay.getLocalBounds().top + ButtonToStay.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // ButtonToStay.setPosition(x_coordZero - 600, y_coordZero + 400);
  ButtonToStay.setPosition(buttonToStayPosition.left, buttonToStayPosition.right);
  ButtonToStay.setFillColor(sf::Color::Red);
}

void Game::initButtonToHit()
{
  ButtonToHit.setFont(mFont);
  ButtonToHit.setString("Hit?\n");
  ButtonToHit.setCharacterSize(48);
  // ButtonToStay.setPosition(850,700);
  ButtonToHit.setOrigin(ButtonToHit.getLocalBounds().left + ButtonToHit.getLocalBounds().width/2, ButtonToHit.getLocalBounds().top + ButtonToHit.getLocalBounds().height/2);
  // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
  // ButtonToHit.setPosition(x_coordZero + 600, y_coordZero + 400);
  ButtonToHit.setPosition(buttonToHitPosition.left, buttonToHitPosition.right);
  ButtonToHit.setFillColor(sf::Color::Red);
}

// void Game::initDealerName()
// {
//
//   #define x_coordZero screenWidth / 2.f
//   //Position of ButtonToStay is set to the middle of the screen. taskBarOffset is used to compensate for the fact that sf::VideoMode::getDesktopMode().height acts as if taskbar is not there.
//   #define y_coordZero (screenHeight / 2.f) - taskBarOffset
//
//   ButtonToHit.setFont(mFont);
//   ButtonToHit.setString("Dealer XXX\n");
//   ButtonToHit.setCharacterSize(48);
//   // ButtonToStay.setPosition(850,700);
//   ButtonToHit.setOrigin(ButtonToHit.getLocalBounds().left + ButtonToHit.getLocalBounds().width/2, ButtonToHit.getLocalBounds().top + ButtonToHit.getLocalBounds().height/2);
//   // A call to ButtonToStay.setPosition(x_coordZero, y_coordZero) would place text in the center of the screen. 
//   ButtonToHit.setPosition(x_coordZero + 600, y_coordZero + 400);
//   ButtonToHit.setFillColor(sf::Color::Red);
//
//   #undef x_coordZero
//   #undef y_coordZero
// }

// void Game::handleButtonToDrawInput(int & countButtonToDrawClicks){
//   mText.setFillColor(sf::Color::Blue);
//   updateSpritesFromTextureMapOfCards();
//   updatePositionOfCardSprites(countButtonToDrawClicks);
// }

void Game::updatePositionOfCardSprites()
{  /* |_|_|_|_|_|
  ** |_|_|_|_|_| A 5x2 layout of sprites on window is made here. 
  */
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
        //p1.numberOfCardsInHand() is equivalent to player1Sprites.size()
        player1CardPlacement.left -= (p1.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player1Sprites.size(); i++){
          //Will dynamically resize but the max number of cards per player will hold this pattern: |5|6|7|8|
          //                                                                            |1|2|3|4|
          if(player1Sprites.size() < 4){
            cardsAsSprites[player1Sprites[i]].setPosition(player1CardPlacement.left + i*slotXDeltaFactor, player1CardPlacement.right);
          }
          else{
            cardsAsSprites[player1Sprites[i]].setPosition(cardsAsSprites[player1Sprites[i%4]].getPosition().x, cardsAsSprites[player1Sprites[i%4]].getPosition().y - slotYDeltaFactor);
          }
        }
      }
      if(p2.isTurn()){
        player2Sprites.push_back(spritesIDX);
        //p1.numberOfCardsInHand() is equivalent to player1Sprites.size()
        player2CardPlacement.left -= (p2.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player2Sprites.size(); i++){
          //Will dynamically resize but the max number of cards per player will hold this pattern: |5|6|7|8|
          //                                                                            |1|2|3|4|
          if(player2Sprites.size() < 4){
            cardsAsSprites[player2Sprites[i]].setPosition(player2CardPlacement.left + i*slotXDeltaFactor, player2CardPlacement.right);
          }
          else{
            cardsAsSprites[player2Sprites[i]].setPosition(cardsAsSprites[player2Sprites[i%4]].getPosition().x, cardsAsSprites[player2Sprites[i%4]].getPosition().y - slotYDeltaFactor);
          }
        }
      }
      if(p3.isTurn()){
        player3Sprites.push_back(spritesIDX);
        //p1.numberOfCardsInHand() is equivalent to player1Sprites.size()
        player3CardPlacement.left -= (p3.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player3Sprites.size(); i++){
          //Will dynamically resize but the max number of cards per player will hold this pattern: |5|6|7|8|
          //                                                                            |1|2|3|4|
          if(player3Sprites.size() < 4){
            cardsAsSprites[player3Sprites[i]].setPosition(player3CardPlacement.left + i*slotXDeltaFactor, player3CardPlacement.right);
          }
          else{
            cardsAsSprites[player3Sprites[i]].setPosition(cardsAsSprites[player3Sprites[i%4]].getPosition().x, cardsAsSprites[player3Sprites[i%4]].getPosition().y - slotYDeltaFactor);
          }
        }
      }
      break;
    case State::promptPlayerMoves:
      if(p1.isTurn() && hitPressed){
        player1Sprites.push_back(spritesIDX);
        //p1.numberOfCardsInHand() is equivalent to player1Sprites.size()
        if(player1Sprites.size() <= maxCardsPerRow){
          player1CardPlacement.left -= slotXDeltaFactor / 2;
        }
        for(int i = 0; i < player1Sprites.size(); i++){
          //Will dynamically resize but the max number of cards per player will hold this pattern: |5|6|7|8|
          //                                                                            |1|2|3|4|
          if(i < maxCardsPerRow){
            cardsAsSprites[player1Sprites[i]].setPosition(player1CardPlacement.left + i*slotXDeltaFactor, player1CardPlacement.right);
          }
          else{
            cardsAsSprites[player1Sprites[i]].setPosition(cardsAsSprites[player1Sprites[i%3]].getPosition().x, cardsAsSprites[player1Sprites[i%3]].getPosition().y - slotYDeltaFactor);
          }
        }
        // cardsAsSprites[spritesIDX].setPosition(player1CardPlacement.left + p1.numberOfCardsInHand()*slotXDeltaFactor, player1CardPlacement.right);
      }
      if(p2.isTurn() && hitPressed){
        player2Sprites.push_back(spritesIDX);
        //p1.numberOfCardsInHand() is equivalent to player1Sprites.size()
        // player2CardPlacement.left -= (p2.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        player2CardPlacement.left = player2CardPlacement.left - (p2.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player2Sprites.size(); i++){
          //Will dynamically resize but the max number of cards per player will hold this pattern: |5|6|7|8|
          //                                                                            |1|2|3|4|
          if(player2Sprites.size() < 4){
            cardsAsSprites[player2Sprites[i]].setPosition(player2CardPlacement.left + i*slotXDeltaFactor, player2CardPlacement.right);
          }
          else{
            cardsAsSprites[player2Sprites[i]].setPosition(cardsAsSprites[player2Sprites[i%4]].getPosition().x, cardsAsSprites[player2Sprites[i%4]].getPosition().y - slotYDeltaFactor);
          }
        }
        // cardsAsSprites[spritesIDX].setPosition(player2CardPlacement.left + p2.numberOfCardsInHand()*slotXDeltaFactor, player2CardPlacement.right);
      }
      if(p3.isTurn() && hitPressed){
        player3Sprites.push_back(spritesIDX);
        //p1.numberOfCardsInHand() is equivalent to player1Sprites.size()
        // player3CardPlacement.left -= (p3.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        player3CardPlacement.left = player3CardPlacement.left - (p3.numberOfCardsInHand() - 1) * (slotXDeltaFactor / 2);
        for(int i = 0; i < player3Sprites.size(); i++){
          //Will dynamically resize but the max number of cards per player will hold this pattern: |5|6|7|8|
          //                                                                            |1|2|3|4|
          if(player3Sprites.size() < 4){
            cardsAsSprites[player3Sprites[i]].setPosition(player3CardPlacement.left + i*slotXDeltaFactor, player3CardPlacement.right);
          }
          else{
            cardsAsSprites[player3Sprites[i]].setPosition(cardsAsSprites[player3Sprites[i%4]].getPosition().x, cardsAsSprites[player3Sprites[i%4]].getPosition().y - slotYDeltaFactor);
          }
        }
        // cardsAsSprites[spritesIDX].setPosition(player3CardPlacement.left + p3.numberOfCardsInHand()*slotXDeltaFactor, player3CardPlacement.right);
      }
      break;
  }

  // if(countButtonToDrawClicks >= 10){
  //   std::cerr << "Program can only work for up to 10 cards\n";
  //   exit(1);
  // }
  // if(countButtonToDrawClicks < 5){ // makde these deltas #dfineds contained in the functino itself, or constatn integers of the class that re members 
  //   cardsAsSprites[countButtonToDrawClicks].setScale(slotScaleFactor, slotScaleFactor); // set slot scale regardless of slot number
  //   cardsAsSprites[countButtonToDrawClicks].move(countButtonToDrawClicks * slotXDeltaFactor, 0.f); 
  // }
  // else{
  //   cardsAsSprites[countButtonToDrawClicks].setScale(slotScaleFactor, slotScaleFactor); // set slot scale regardless of slot number
  //   cardsAsSprites[countButtonToDrawClicks].move(countButtonToDrawClicks%5 * slotXDeltaFactor, slotYDeltaFactor); // only x movement for <= 5
  // }
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
  // loop through the 52 files. They're sorted alphabetically, and enums are made to match this sorted file vector for its vector of keys
  // For each file name, create Texture object pointer and load each file.
  for(std::vector<std::string>::const_iterator i = listOfFileNames.begin(), e = listOfFileNames.end(); i != e; ++i){
    auto ptr = std::make_unique<sf::Texture>();
    if(!ptr->loadFromFile(listOfFileNames[count])){
      std::cerr << "Failed to open " << listOfFileNames[count] << '\n';
      exit(1);
    }
    //insert each pair into map. Check insertion happened okay by true/false of .second of returned std::pair
    auto successfulPairFromInsertion = mapOfCardTextures.insert(std::make_pair(Deck.currentCardName(), std::move(ptr))); 
    Deck.increaseIndex();
    if(!successfulPairFromInsertion.second){
      std::cerr << "Failed to insert " << listOfFileNames[count] << '\n';
      exit(1);
    }
    count++;
  }
  Deck.resetIndex();
}

// void Game::drawCard(Player & p)
// {
//   p.pushCardToHand(Deck.currentCardName());
//   p.updateScore(Deck.currentCardValue());
//   Deck.increaseIndex();
// }

// void Game::updateGameLogic(sf::Clock & dialogueClock, sf::Time & dialogueDelay, sf::Time & diaglogueRate, int & countButtonToDrawClicks)
void Game::updateGameLogic()
{
    switch(currentState)
    {
      case State::init:
        updateDialogueBox(); //<-- will go inside updateGameLogic() eventually
        currentState = Game::State::dealerFirstCardReveal;
        break;
      case State::dealerFirstCardReveal:
        updateDialogueBox(); //<-- will go inside updateGameLogic() eventually
        dealer.pushCardToHand(Deck.currentCardName());
        dealer.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        Deck.increaseIndex();
        currentState = Game::State::dealFirstCardsToPlayers;
        break;

      case State::dealFirstCardsToPlayers:
        p1.setTurn(true);
        p1.pushCardToHand(Deck.currentCardName());
        p1.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        p1.setTurn(false);
        Deck.increaseIndex();

        p1.setTurn(true);
        p1.pushCardToHand(Deck.currentCardName());
        p1.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        p1.setTurn(false);
        Deck.increaseIndex();
        //
        p2.setTurn(true);
        p2.pushCardToHand(Deck.currentCardName());
        p2.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        p2.setTurn(false);
        Deck.increaseIndex();
        p2.setTurn(true);
        p2.pushCardToHand(Deck.currentCardName());
        p2.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        p2.setTurn(false);
        Deck.increaseIndex();

        p3.setTurn(true);
        p3.pushCardToHand(Deck.currentCardName());
        p3.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        p3.setTurn(false);
        Deck.increaseIndex();
        p3.setTurn(true);
        p3.pushCardToHand(Deck.currentCardName());
        p3.updateScore(Deck.currentCardValue());
        updateSpritesFromTextureMapOfCards();
        updatePositionOfCardSprites();
        p3.setTurn(false);
        Deck.increaseIndex();

        currentState = State::promptPlayerMoves;
        //Kicks off selection of actions in promptPlayerMoves state
        p1.setTurn(true);
        break;
      case State::promptPlayerMoves: //<-- later on the stayButton selection will be used to control the loops that all of these steps will end up in
          if(p1.isTurn()){
            updateDialogueBox();
            if(hitPressed){
              p1.pushCardToHand(Deck.currentCardName());
              p1.updateScore(Deck.currentCardValue());
              updateSpritesFromTextureMapOfCards();
              updatePositionOfCardSprites();
              Deck.increaseIndex();
              hitPressed = false;
            }
            if (stayPressed){
              p1.setTurn(false);
              p2.setTurn(true);
              stayPressed = false;
            }
          }
          else if(p2.isTurn()){
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
          }
          else if(p3.isTurn()){
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
              p3.setTurn(false);
              stayPressed = false;
            }
          }
        // p1.setTurn(true);
        // updateDialogueBox();
        // if(hitPressed){
        //   p1.pushCardToHand(Deck.currentCardName());
        //   p1.updateScore(Deck.currentCardValue());
        //   updateSpritesFromTextureMapOfCards();
        //   updatePositionOfCardSprites();
        //   Deck.increaseIndex();
        // }

        break;
    }
  // p1.pushCardToHand(Deck.currentCardName());
  // p1.updateScore(Deck.currentCardValue());
  // Deck.increaseIndex();
}
