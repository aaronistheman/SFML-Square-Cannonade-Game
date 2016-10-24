#pragma once

#include <Tile/Tile.hpp>
#include <Tile/WallTile.hpp>

#include <vector>

int computeCorrectNumberTiles(sf::IntRect rect, int tileLength);

// For tests that just use default/platform/nonspecial tiles
std::string createTileMapAllDefault(sf::IntRect area, int tileLength);

void runCreateGrid(std::vector<Tile::Ptr> &tileGrid,
  const sf::IntRect &area, int tileLength,
  const std::string &tileMap,
  std::vector<WallTile*> &wallTiles = std::vector<WallTile*>());