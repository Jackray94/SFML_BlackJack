#ifndef CARDS_H
#define CARDS_H

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class Cards
{
  public:
    // I think the rule of zero here is preferred
    Cards(int scr, std::unique_ptr<sf::Texture> ptr);
    int Score;
    std::unique_ptr<sf::Texture> cardPicture;
};

#endif
