#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/World.hpp>
#include <Tile/Tile.hpp>
#include <Tile/TileMapConstants.hpp>

#include <vector>
#include <iostream>

TEST_CASE("Created correct number of tiles #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 30);
  int tileLength = 10;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  int answer = computeCorrectNumberTiles(rect, tileLength);
  REQUIRE(tileGrid.size() == answer);
}

TEST_CASE("Created correct number of tiles #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 1200, 600);
  int tileLength = 30;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  int answer = computeCorrectNumberTiles(rect, tileLength);
  REQUIRE(tileGrid.size() == answer);
}

TEST_CASE("Created correct number of tiles #3")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(20, 20, 1200, 600);
  int tileLength = 15;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  int answer = computeCorrectNumberTiles(rect, tileLength);
  REQUIRE(tileGrid.size() == answer);
}

TEST_CASE("Correct tile x-coordinate #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 30);
  int tileLength = 10;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

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

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

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

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(10).get();
  REQUIRE(tile->getRect().left == 50);
}

TEST_CASE("Correct tile y-coordinate #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 25;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(6).get();
  REQUIRE(tile->getRect().top == 25);
}

TEST_CASE("Correct tile width")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 25;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(8).get(); // random tile
  REQUIRE(tile->getRect().width == tileLength);
}

TEST_CASE("Correct tile height")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 100, 100);
  int tileLength = 20;
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);

  Tile *tile = tileGrid.at(2).get(); // random tile
  REQUIRE(tile->getRect().height == tileLength);
}

TEST_CASE("Correct number of wall tiles created #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 20);
  int tileLength = 10;
  std::vector<WallTile*> wallTiles;

  std::string tileMap = "";
  tileMap += "000w0";
  tileMap += "0w0w0";

  runCreateGrid(tileGrid, rect, tileLength, tileMap, wallTiles);

  // Assertion
  REQUIRE(wallTiles.size() == 3);
}

TEST_CASE("Correct number of wall tiles created #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 20);
  int tileLength = 10;
  std::vector<WallTile*> wallTiles;

  std::string tileMap = "";
  tileMap += "00000";
  tileMap += "00w00";

  runCreateGrid(tileGrid, rect, tileLength, tileMap, wallTiles);

  // Assertion
  REQUIRE(wallTiles.size() == 1);
}

TEST_CASE("Correct wall tile x-coordinate #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 50, 20);
  int tileLength = 10;
  std::vector<WallTile*> wallTiles;

  std::string tileMap = "";
  tileMap += "000w0";
  tileMap += "0w0w0";

  runCreateGrid(tileGrid, rect, tileLength, tileMap, wallTiles);

  // Assertion
  REQUIRE(wallTiles.at(1)->getRect().left == tileLength);
}