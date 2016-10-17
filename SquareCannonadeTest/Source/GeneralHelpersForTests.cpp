#include <GeneralHelpersForTests.hpp>

#include <Game/World.hpp>

int computeCorrectNumberTiles(sf::IntRect rect, int tileLength)
{
  return rect.width / tileLength * rect.height / tileLength;
}

std::string createTileMapAllDefault(sf::IntRect area, int tileLength)
{
  int numTiles = computeCorrectNumberTiles(area, tileLength);
  std::string tileMap = "";

  for (int i = 0; i < numTiles; ++i)
  {
    // The cast is needed because of the strongly typed enumerator
    // (isn't technically char, but takes up size of a char)
    tileMap += (char)TileType::Default;
  }

  return tileMap;
}

/**
 * Helpful because I keep changing the parameters of World::createGrid().
 */
void runCreateGrid(std::vector<Tile::Ptr> &tileGrid,
  const sf::IntRect &area, int tileLength,
  const std::string &tileMap,
  std::vector<WallTile*> &wallTiles)
{
  World::createGrid(tileGrid, area, tileLength, tileMap, wallTiles);
}