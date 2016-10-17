#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

TEST_CASE("Created correct number of vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 40, 30);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumVertices() == 12);
}

TEST_CASE("Created correct number of vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 40, 30);
  int tileLength = 10;

  // This tile map has a few walls, which are not translated into vertices
  std::string tileMap = "";
  tileMap += "0000";
  tileMap += "00w0";
  tileMap += "000w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg = PathfindingGraph(tileGrid);

  // Assertion
  REQUIRE(pg.getNumVertices() == 10);
}

TEST_CASE("Created correct number of edges #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 30, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 10);
}

TEST_CASE("Created correct number of edges #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 40, 30);
  int tileLength = 10;

  // This tile map has a few walls, which are not translated into vertices
  std::string tileMap = "";
  tileMap += "0000";
  tileMap += "00w0";
  tileMap += "000w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg = PathfindingGraph(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 15);
}

TEST_CASE("Created correct number of edges #3")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 30, 30);
  int tileLength = 10;

  // This tile map has a few walls, which are not translated into vertices
  std::string tileMap = "";
  tileMap += "000";
  tileMap += "00w";
  tileMap += "w00";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg = PathfindingGraph(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 9);
}