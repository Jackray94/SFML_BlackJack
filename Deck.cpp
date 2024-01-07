#include "Deck.h"
#include "imageFileHandle.h"

Deck::Deck()
  : stringCardKeys{ListOfFilesInDirectory()}
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
  if(!ptr->loadFromFile("./Media/Textures" + key + ".png")){
    std::cerr << "Failed to open " << key << '\n';
    exit(1);
  }
  //I believe this return will cause NRVO (instead of RVO) which does not guarentee elision. If NRVO doesn't happen then move ctor should be called anyway. 
  return ptr;
}

int Deck::loadMapWithCardScore(std::string const & key)
{
   
  if(key == "Ace of Clubs"){return 11;}
  else if(key == "Ace of Spades"){return 11;}
  else if(key == "Ace of Diamonds"){return 11;}
  else if(key == "Ace of Hearts"){return 11;}
  else if(key == "King of Clubs"){return 10;}
  else if(key == "King of Spades"){return 10;}
  else if(key == "King of Diamonds"){return 10;}
  else if(key == "King of Hearts"){return 10;}
  else if(key == "Queen of Clubs"){return 10;}
  else if(key == "Queen of Spades"){return 10;}
  else if(key == "Queen of Diamonds"){return 10;}
  else if(key == "Queen of Hearts"){return 10;}
  else if(key == "Jack of Clubs"){return 10;}
  else if(key == "Jack of Spades"){return 10;}
  else if(key == "Jack of Diamonds"){return 10;}
  else if(key == "Jack of Hearts"){return 10;}
  else if(key == "Ten of Clubs"){return 10;}
  else if(key == "Ten of Spades"){return 10;}
  else if(key == "Ten of Diamonds"){return 10;}
  else if(key == "Ten of Hearts"){return 10;}
  else if(key == "Nine of Clubs"){return 9;}
  else if(key == "Nine of Spades"){return 9;}
  else if(key == "Nine of Diamonds"){return 9;}
  else if(key == "Nine of Hearts"){return 9;}
  else if(key == "Eight of Clubs"){return 8;}
  else if(key == "Eight of Spades"){return 8;}
  else if(key == "Eight of Diamonds"){return 8;}
  else if(key == "Eight of Hearts"){return 8;}
  else if(key == "Seven of Clubs"){return 7;}
  else if(key == "Seven of Spades"){return 7;}
  else if(key == "Seven of Diamonds"){return 7;}
  else if(key == "Seven of Hearts"){return 7;}
  else if(key == "Six of Clubs"){return 6;}
  else if(key == "Six of Spades"){return 6;}
  else if(key == "Six of Diamonds"){return 6;}
  else if(key == "Six of Hearts"){return 6;}
  else if(key == "Five of Clubs"){return 5;}
  else if(key == "Five of Spades"){return 5;}
  else if(key == "Five of Diamonds"){return 5;}
  else if(key == "Five of Hearts"){return 5;}
  else if(key == "Four of Clubs"){return 4;}
  else if(key == "Four of Spades"){return 4;}
  else if(key == "Four of Diamonds"){return 4;}
  else if(key == "Four of Hearts"){return 4;}
  else if(key == "Three of Clubs"){return 3;}
  else if(key == "Three of Spades"){return 3;}
  else if(key == "Three of Diamonds"){return 3;}
  else if(key == "Three of Hearts"){return 3;}
  else if(key == "Two of Clubs"){return 2;}
  else if(key == "Two of Spades"){return 2;}
  else if(key == "Two of Diamonds"){return 2;}
  else if(key == "Two of Hearts"){return 2;}
}

/*#include "Deck.h"

Deck::Deck()
  : deckOfCards{mapOfCards()}, listOfCardKeys{cardKeys()}, index{0}
{
}

// Vector has no issue, unlike Unordered_map, with operator[] and const elements. This is because std::vector::operator[] has overloads to handle const, unlike std::unordered_map::operator[].
//
// The point made above is good-to-know but not relevent bceause vector listOfCardKeys doesn't have const elements in this example.

// Since I can't return by const reference, I believe it is preferred to even still avoid returning by const value. This is because you want to allow for RVO (return value optimization) copy elision - never return by const value because you can screw up copy elision (meaning using const can prevent move semantics (copy elision)) 
std::string Deck::currentCardName() const{return listOfCardKeys[index];}


int Deck::currentCardValue() const
{
  //I can't use std::unordered_map::operater[] with const. Also I control the setup which ensures there will not be a need to check if past-the-end iterator is returned (i.e. key not found).
  auto found = deckOfCards.find(listOfCardKeys[index]);
  return found->second;
}

void Deck::increaseIndex() {index++;}

void Deck::resetIndex() {index = 0;}

int const & Deck::getIndex() const {return index;}

void Deck::randomizeListOfCardKeys()
{
  static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
  std::shuffle(listOfCardKeys.begin(), listOfCardKeys.end(), mt);
}
*/
