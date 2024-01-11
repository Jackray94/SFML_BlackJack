#include "Cards.h"

using bj::Cards;

Cards::Cards(int scr, std::unique_ptr<sf::Texture> ptr)
  : Score{scr}, cardPicture{std::move(ptr)}
{
}
