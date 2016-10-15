#include <Tile/TileSet.hpp>

TileSet::TileSet()
  : mSet()
{

}

size_t TileSet::getSize() const
{
  return mSet.size();
}

void TileSet::addTile(Tile::Ptr &tile)
{
  mSet.push_back(std::move(tile));
}