#include <Tile/Tile.hpp>

Tile::Tile(int left, int top, int width, int height, TileType type, int penalty)
  : mRect(left, top, width, height)
  , mType(type)
  , mPenalty(penalty)
{

}

sf::IntRect Tile::getRect() const
{
  return mRect;
}

int Tile::getPenalty() const
{
  return mPenalty;
}