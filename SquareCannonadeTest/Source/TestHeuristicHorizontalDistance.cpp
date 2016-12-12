#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <iostream>


int setupHeuristicHorizontalDistanceTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  int tileLength = 10, enemyLength = 10;

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1: case 4: case 5: case 6:
    area = sf::IntRect(0, 0, 60, 50);
    break;
  case 2:
    area = sf::IntRect(0, 0, 90, 90);
    break;
  case 3:
    area = sf::IntRect(0, 0, 60, 60);
    break;
  default:
    // No suitable default; stop tests
    std::cerr << "Invalid case number\n";
    assert(false);
  }

  // Set tile map
  std::string tileMap = "";
  switch (caseNum)
  {
  case 1: case 2: case 3:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  case 4: case 5: case 6:
    tileMap += "000000";
    tileMap += "000w00";
    tileMap += "000w00";
    tileMap += "000w00";
    tileMap += "000000";
    break;
  }
  assert(tileMap != "");



  // Create the graph
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  std::unique_ptr<PathfindingGraph> pg =
    std::unique_ptr<PathfindingGraph>(new PathfindingGraph(tileGrid));



  // Set pathfinding search end vertices (since the heuristic function
  // depends on where these are)
  switch (caseNum)
  {
  case 1:
    pg->setSearchEnd(sf::Vector2f(50, 40), enemyLength);
    break;
  case 2:
    pg->setSearchEnd(sf::Vector2f(10, 30), enemyLength);
    break;
  case 3:
    pg->setSearchEnd(sf::Vector2f(30, 10), enemyLength);
    break;
  case 4: case 5: case 6:
    pg->setSearchEnd(sf::Vector2f(50, 30), enemyLength);
    break;
  }

  // Pick parameter for the method-to-test
  sf::Vector2i currentPos;
  switch (caseNum)
  {
  case 1:
    currentPos = sf::Vector2i(10, 10);
    break;
  case 2: 
    currentPos = sf::Vector2i(50, 40);
    break;
  case 3:
    currentPos = sf::Vector2i(20, 30);
    break;
  case 4:
    currentPos = sf::Vector2i(20, 10);
    break;
  case 5:
    currentPos = sf::Vector2i(20, 20);
    break;
  case 6:
    currentPos = sf::Vector2i(50, 20);
    break;
  }
  PGVertex* current = pg->getVertex(currentPos);
  assert(current);

  return pg->getEstimatedGraphDistanceInTiles(current);
}

TEST_CASE("Correct heuristic horizonal distance #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto distance = setupHeuristicHorizontalDistanceTests(1, tileGrid);

  REQUIRE(distance == 3);
}

TEST_CASE("Correct heuristic horizonal distance #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto distance = setupHeuristicHorizontalDistanceTests(2, tileGrid);

  REQUIRE(distance == 4);
}

TEST_CASE("Correct heuristic horizonal distance #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto distance = setupHeuristicHorizontalDistanceTests(3, tileGrid);

  REQUIRE(distance == 0);
}

TEST_CASE("Correct heuristic horizonal distance #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto distance = setupHeuristicHorizontalDistanceTests(4, tileGrid);

  REQUIRE(distance == 2);
}

TEST_CASE("Correct heuristic horizonal distance #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto distance = setupHeuristicHorizontalDistanceTests(5, tileGrid);

  REQUIRE(distance == 2);
}

TEST_CASE("Correct heuristic horizonal distance #6")
{
  std::vector<Tile::Ptr> tileGrid;
  auto distance = setupHeuristicHorizontalDistanceTests(6, tileGrid);

  REQUIRE(distance == 0);
}