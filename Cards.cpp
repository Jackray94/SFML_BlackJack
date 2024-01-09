#include "Cards.h"

Cards::Cards(int scr, std::unique_ptr<sf::Texture> ptr)
  : Score{scr}, cardPicture{std::move(ptr)}
{
}
