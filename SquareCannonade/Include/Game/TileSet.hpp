#pragma once

#include <Game/Tile.hpp>

#include <vector>

/**
 * Represents a set of instances of class Tile
 */
class TileSet
{
public:
  TileSet();

  size_t getSize() const;

  void addTile(Tile::Ptr &tile);

private:
  std::vector<Tile::Ptr> mSet;
};