#include <Catch/Catch.hpp>

#include <Game/World.hpp>
#include <Game/Tile.hpp>
#include <Game/TileMapConstants.hpp>

#include <vector>

int computeCorrectNumberTiles(sf::IntRect rect, int tileLength)
{
  return rect.width / tileLength * rect.height / tileLength;
}

// For tests that just use default/platform/nonspecial tiles
std::string createTileMapAllDefault(sf::IntRect area, int tileLength)
{
  int numTiles = computeCorrectNumberTiles(area, tileLength);
  std::string tileMap = "";

  for (int i = 0; i < numTiles; ++i)
  {
    // The cast is needed because of the strongly typed enumerator
    // (isn't technically char, but takes up size of a char)
    tileMap += (char) TileType::Default;
  }

  return tileMap;
}

TEST_CASE("Created correct number of tiles #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 30);
  int tileLength = 10;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  int answer = computeCorrectNumberTiles(rect, tileLength);
  REQUIRE(tileGrid.size() == answer);
}

TEST_CASE("Created correct number of tiles #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 1200, 600);
  int tileLength = 30;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  int answer = computeCorrectNumberTiles(rect, tileLength);
  REQUIRE(tileGrid.size() == answer);
}

TEST_CASE("Created correct number of tiles #3")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(20, 20, 1200, 600);
  int tileLength = 15;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  int answer = computeCorrectNumberTiles(rect, tileLength);
  REQUIRE(tileGrid.size() == answer);
}

TEST_CASE("Correct tile x-coordinate #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 30);
  int tileLength = 10;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  // Second tile should be offset from left by tile length
  Tile *tile = tileGrid.at(1).get();
  REQUIRE(tile->getRect().left == tileLength);
}

TEST_CASE("Correct tile y-coordinate #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 30);
  int tileLength = 10;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  // Second tile should still be on first row
  Tile *tile = tileGrid.at(1).get();
  REQUIRE(tile->getRect().top == 0);
}

TEST_CASE("Correct tile x-coordinate #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 25;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(10).get();
  REQUIRE(tile->getRect().left == 50);
}

TEST_CASE("Correct tile y-coordinate #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 25;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(6).get();
  REQUIRE(tile->getRect().top == 25);
}

TEST_CASE("Correct tile width")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 25;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(8).get(); // random tile
  REQUIRE(tile->getRect().width == tileLength);
}

TEST_CASE("Correct tile height")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 20;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  World::createGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(2).get(); // random tile
  REQUIRE(tile->getRect().height == tileLength);
}