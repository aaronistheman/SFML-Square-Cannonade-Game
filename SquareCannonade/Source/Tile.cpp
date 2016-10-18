#include <Tile/Tile.hpp>

Tile::Tile(int left, int top, int width, int height, TileType type, int penalty)
  : mRect(left, top, width, height)
  , mType(type)
  , mPenalty(penalty)
{

}

Tile::~Tile()
{
}

sf::IntRect Tile::getRect() const
{
  return mRect;
}

TileType Tile::getType() const
{
  return mType;
}

int Tile::getPenalty() const
{
  return mPenalty;
}

bool Tile::isTraversable() const
{
  switch (mType) {
  case TileType::Wall:
    return false;
  default:
    return true;
  }
}
