#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <iostream>



/**
 * Tests for setting vertices at which pathfinding search should start/end
 *
 * Note that there is a confusing part in that an enemy's position is
 * centered, whereas a vertex's position uses its top-left coordinate.
 * This is a bad design choice on my part.
 *
 * tileGrid can't be local to this function because the generated
 * PathfindingGraph instance has vertices that reference the tiles
 * in tileGrid.
 */

// Setup function to help with the tests of the setup of the pathfinding
std::unique_ptr<PathfindingGraph> setupPathfindingSetupTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // Set tile and enemy length
  int tileLength = 0;
  int enemyLength = 0;
  switch (caseNum)
  {
  case 2: case 6:
    tileLength = 30;
    enemyLength = 20;
    break;
  case 3: case 4: case 7: case 8:
    tileLength = 10;
    enemyLength = 5;
    break;
  case 10:
    tileLength = 10;
    enemyLength = 1;
  default:
    tileLength = enemyLength = 10;
    break;
  }

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1: case 5:
    area = sf::IntRect(0, 0, 50, 40);
    break;
  case 2: case 6:
    area = sf::IntRect(0, 0, 150, 150);
    break;
  case 3: case 7:
    area = sf::IntRect(0, 0, 20, 20);
    break;
  case 4: case 8:
    area = sf::IntRect(0, 0, 30, 20);
    break;
  case 9:
    area = sf::IntRect(0, 0, 50, 40);
    break;
  case 10:
    area = sf::IntRect(0, 0, 60, 60);
    break;
  default:
    std::cerr << "Invalid case number\n";
    assert(false); // shouldn't be reached; no logical default area
    break;
  }

  // Create tile map
  std::string tileMap = "";
  switch (caseNum)
  {
  case 2: case 6: // some random walls
    tileMap += "00www";
    tileMap += "w000w";
    tileMap += "00w00";
    tileMap += "00000";
    tileMap += "00ww0";
    break;
  case 9:
    tileMap += "00000";
    tileMap += "0ww00";
    tileMap += "000w0";
    tileMap += "00000";
    break;
  case 10:
    tileMap += "000000";
    tileMap += "00w000";
    tileMap += "000000";
    tileMap += "000w00";
    tileMap += "0w000w";
    tileMap += "00000w";
    break;
  default:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  }

  // Stuff for every test case
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  std::unique_ptr<PathfindingGraph> pg =
    std::unique_ptr<PathfindingGraph>(new PathfindingGraph(tileGrid));

  // Run method-to-test
  switch (caseNum)
  {
  case 1:
    pg->setSearchStart(sf::Vector2f(29, 18), enemyLength);
    break;
  case 2:
    pg->setSearchStart(sf::Vector2f(32, 94), enemyLength);
    break;
  case 3:
    pg->setSearchStart(sf::Vector2f(15, 5), enemyLength);
    break;
  case 4:
    pg->setSearchStart(sf::Vector2f(15, 10), enemyLength);
    break;
  case 5:
    pg->setSearchEnd(sf::Vector2f(29, 18), enemyLength);
    break;
  case 6:
    pg->setSearchEnd(sf::Vector2f(32, 94), enemyLength);
    break;
  case 7:
    pg->setSearchEnd(sf::Vector2f(15, 5), enemyLength);
    break;
  case 8:
    pg->setSearchEnd(sf::Vector2f(15, 10), enemyLength);
    break;
  case 9:
    pg->setSearchStart(sf::Vector2f(40, 10), enemyLength);
    pg->setSearchEnd(sf::Vector2f(20, 30), enemyLength);
    break;
  case 10:
    pg->setSearchStart(sf::Vector2f(20, 30), enemyLength);
    pg->setSearchEnd(sf::Vector2f(45, 15), enemyLength);
    break;
  default:
    assert(false); // no logical default
  }

  return pg;
} // setupPathfindingSetupTests()

TEST_CASE("Setting pathfinding search's start vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  std::unique_ptr<PathfindingGraph> pg =
    setupPathfindingSetupTests(1, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(20, 10));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(30, 10));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(30, 20));
}

// Involves some random walls that *shouldn't* affect anything
TEST_CASE("Setting pathfinding search's start vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(2, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(0, 60));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(30, 60));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(0, 90));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(30, 90));
}

// Enemy completely fits in one tile
TEST_CASE("Setting pathfinding search's start vertices #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(3, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 1);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(10, 0));
}

// Enemy completely fits in two tiles
TEST_CASE("Setting pathfinding search's start vertices #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(4, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 2);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(10, 0));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(10, 10));
}

TEST_CASE("Setting pathfinding search's end vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  std::unique_ptr<PathfindingGraph> pg =
    setupPathfindingSetupTests(5, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 4);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(20, 10));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(30, 10));
  assertEquality(endVertices[2]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(endVertices[3]->getPosition(), sf::Vector2i(30, 20));
}

// Involves some random walls that *shouldn't* affect anything
TEST_CASE("Setting pathfinding search's end vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(6, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 4);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(0, 60));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(30, 60));
  assertEquality(endVertices[2]->getPosition(), sf::Vector2i(0, 90));
  assertEquality(endVertices[3]->getPosition(), sf::Vector2i(30, 90));
}

// Target entity completely fits in one tile
TEST_CASE("Setting pathfinding search's end vertices #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(7, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 1);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(10, 0));
}

// Target entity completely fits in two tiles
TEST_CASE("Setting pathfinding search's end vertices #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(8, tileGrid);

  // Assertion
  REQUIRE(pg->getNumSearchEndVertices() == 2);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(10, 0));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(10, 10));
}

TEST_CASE("Setting pathfinding search's start and end vertices #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(9, tileGrid);

  // Assertions for start vertices
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(30, 0));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(40, 0));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(30, 10));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(40, 10));

  // Assertions for end vertices
  REQUIRE(pg->getNumSearchEndVertices() == 4);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(10, 20));
  assertEquality(endVertices[1]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(endVertices[2]->getPosition(), sf::Vector2i(10, 30));
  assertEquality(endVertices[3]->getPosition(), sf::Vector2i(20, 30));
}

TEST_CASE("Setting pathfinding search's start and end vertices #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupPathfindingSetupTests(10, tileGrid);

  // Assertions for start vertices
  REQUIRE(pg->getNumSearchStartVertices() == 4);
  auto startVertices = pg->getSearchStartVertices();
  assertEquality(startVertices[0]->getPosition(), sf::Vector2i(10, 20));
  assertEquality(startVertices[1]->getPosition(), sf::Vector2i(20, 20));
  assertEquality(startVertices[2]->getPosition(), sf::Vector2i(10, 30));
  assertEquality(startVertices[3]->getPosition(), sf::Vector2i(20, 30));

  // Assertions for end vertices
  REQUIRE(pg->getNumSearchEndVertices() == 1);
  auto endVertices = pg->getSearchEndVertices();
  assertEquality(endVertices[0]->getPosition(), sf::Vector2i(40, 10));
}
