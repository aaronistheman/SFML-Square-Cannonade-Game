#include <Game/Tile.hpp>

Tile::Tile(int left, int top, int width, int height)
  : mRect(left, top, width, height)
{

}

sf::IntRect Tile::getRect() const
{
  return mRect;
}