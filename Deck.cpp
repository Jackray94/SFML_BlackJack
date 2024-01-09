#include "Deck.h"
#include "imageFileHandle.h"

Deck::Deck()
  : stringCardKeys{ListOfFilesInDirectory()}, deckOfCards{MapSCards()}, index{0}
{
}

void Deck::loadMapWithCardData()
{
  int cardCount = 0;
  for(auto const & texture : stringCardKeys){
    //I believe NRVO or move ctor happens here (worst case)
    auto ptr = loadMapWithCardPNGTextures(texture);
    // I don't think taking the the above function call and placing it in card's initilization is a good idea beacuse it might affect the elision for ptr above. 
    Cards card{loadMapWithCardScore(texture), std::move(ptr)};
    auto successfulPairFromInsertion = deckOfCards.insert(std::make_pair(stringCardKeys[cardCount], std::move(card))); 
    if(!successfulPairFromInsertion.second){
      std::cerr << "Failed to insert " << stringCardKeys[cardCount] << '\n';
      exit(1);
    }
    cardCount++;
  }
}

std::unique_ptr<sf::Texture> Deck::loadMapWithCardPNGTextures(std::string const & key)
{
  auto ptr = std::make_unique<sf::Texture>();
  if(!ptr->loadFromFile("./Media/Textures/" + key + ".png")){
    std::cerr << "Failed to open " << key << '\n';
    // exit(1);
  }
  //I believe this return will cause NRVO (instead of RVO) which does not guarentee elision. If NRVO doesn't happen then move ctor should be called anyway. 
  return ptr;
}

int Deck::loadMapWithCardScore(std::string const & key)
{
   
  if(key == "ace_of_clubs"){return 11;}
  else if(key == "ace_of_spades"){return 11;}
  else if(key == "ace_of_diamonds"){return 11;}
  else if(key == "ace_of_hearts"){return 11;}
  else if(key == "king_of_clubs"){return 10;}
  else if(key == "king_of_spades"){return 10;}
  else if(key == "king_of_diamonds"){return 10;}
  else if(key == "king_of_hearts"){return 10;}
  else if(key == "queen_of_clubs"){return 10;}
  else if(key == "queen_of_spades"){return 10;}
  else if(key == "queen_of_diamonds"){return 10;}
  else if(key == "queen_of_hearts"){return 10;}
  else if(key == "jack_of_clubs"){return 10;}
  else if(key == "jack_of_spades"){return 10;}
  else if(key == "jack_of_diamonds"){return 10;}
  else if(key == "jack_of_hearts"){return 10;}
  else if(key == "10_of_clubs"){return 10;}
  else if(key == "10_of_spades"){return 10;}
  else if(key == "10_of_diamonds"){return 10;}
  else if(key == "10_of_hearts"){return 10;}
  else if(key == "9_of_clubs"){return 9;}
  else if(key == "9_of_spades"){return 9;}
  else if(key == "9_of_diamonds"){return 9;}
  else if(key == "9_of_hearts"){return 9;}
  else if(key == "8_of_clubs"){return 8;}
  else if(key == "8_of_spades"){return 8;}
  else if(key == "8_of_diamonds"){return 8;}
  else if(key == "8_of_hearts"){return 8;}
  else if(key == "7_of_clubs"){return 7;}
  else if(key == "7_of_spades"){return 7;}
  else if(key == "7_of_diamonds"){return 7;}
  else if(key == "7_of_hearts"){return 7;}
  else if(key == "6_of_clubs"){return 6;}
  else if(key == "6_of_spades"){return 6;}
  else if(key == "6_of_diamonds"){return 6;}
  else if(key == "6_of_hearts"){return 6;}
  else if(key == "5_of_clubs"){return 5;}
  else if(key == "5_of_spades"){return 5;}
  else if(key == "5_of_diamonds"){return 5;}
  else if(key == "5_of_hearts"){return 5;}
  else if(key == "4_of_clubs"){return 4;}
  else if(key == "4_of_spades"){return 4;}
  else if(key == "4_of_diamonds"){return 4;}
  else if(key == "4_of_hearts"){return 4;}
  else if(key == "3_of_clubs"){return 3;}
  else if(key == "3_of_spades"){return 3;}
  else if(key == "3_of_diamonds"){return 3;}
  else if(key == "3_of_hearts"){return 3;}
  else if(key == "2_of_clubs"){return 2;}
  else if(key == "2_of_spades"){return 2;}
  else if(key == "2_of_diamonds"){return 2;}
  else {return 2;}
}

void Deck::randomizeListOfCardKeys()
{
  static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
  std::shuffle(stringCardKeys.begin(), stringCardKeys.end(), mt);
}

// Since I can't return by const reference, I believe it is preferred to even still avoid returning by const value. This is because you want to allow for RVO (return value optimization) copy elision - never return by const value because you can screw up copy elision (meaning using const can prevent move semantics (copy elision)) 
std::string Deck::currentCardName() const
{
  return stringCardKeys[index];
}


int Deck::currentCardValue() const
{
  //I can't use std::unordered_map::operater[] with const. (Unrelated, now that I changed stuff up, but good to know.) Also I control the setup which ensures there will not be a need to check if past-the-end iterator is returned (i.e. key not found).
  auto found = deckOfCards.find(stringCardKeys[index]);
  if(found != deckOfCards.end()){
    return found->second.Score;
  }
  else{
    std::cerr << "Failed to access map key/value pair.\n";
    exit(1);
  }
}

void Deck::increaseIndex() {index++;}

void Deck::resetIndex() {index = 0;}

int Deck::getIndex() const {return index;}

MapSCards::const_iterator Deck::foundCard()
{
  // I think that because I contorl the setup I don't need to check if past-the-end iterator but am doing it here anyway.
  auto found = deckOfCards.find(stringCardKeys[index]);
  if(found == deckOfCards.end()){
    std::cerr << "Failed to access map key/value pair";
    exit(1);
  }
  return found;
}
