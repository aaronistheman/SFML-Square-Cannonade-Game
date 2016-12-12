#include <GeneralHelpersForTests.hpp>
#include <Catch/Catch.hpp>

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

/**
 * Helps avoid the repetition of manually comparing the x and y values
 * of Vector2f instances. (Comparing the primitive x's and y's individually
 * makes the Catch testing framework more helpful in reporting failed
 * tests.)
 */
void assertEquality(const sf::Vector2i& lhs, const sf::Vector2i& rhs)
{
  REQUIRE(lhs.x == rhs.x);
  REQUIRE(lhs.y == rhs.y);
}