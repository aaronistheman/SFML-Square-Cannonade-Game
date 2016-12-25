#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <iostream>






/**
 * Tests the A* algorithm implementation in PathfindingGraph,
 * with MULTIPLE consecutive searches (i.e. multiple enemies)
 */

std::unique_ptr<PathfindingGraph> setupMultiplePathfindingTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // Set tile and enemy length
  int tileLength = 0, enemyLength = 0;
  switch (caseNum)
  {
  default:
    tileLength = enemyLength = 10;
  }


  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1:
    area = sf::IntRect(0, 0, 30, 10);
    break;
  case 2: case 3:
    area = sf::IntRect(0, 0, 30, 30);
    break;
  case 4:
    area = sf::IntRect(0, 0, 60, 30);
    break;
  case 5:
    area = sf::IntRect(0, 0, 120, 80);
    break;
  case 6:
    area = sf::IntRect(0, 0, 90, 60);
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
  case 3:
    tileMap += "000";
    tileMap += "00w";
    tileMap += "000";
    break;
  case 4:
    tileMap += "000000";
    tileMap += "0w0w00";
    tileMap += "0w0000";
    break;
  case 5:
    tileMap += "000000000000";
    tileMap += "000000000000";
    tileMap += "00000w000000";
    tileMap += "00000w000w00";
    tileMap += "00000w000w00";
    tileMap += "00000w000w00";
    tileMap += "000000000w00";
    tileMap += "000000000000";
    break;
  case 6:
    tileMap += "000000000";
    tileMap += "00000w000";
    tileMap += "00w00w000";
    tileMap += "00w00w000";
    tileMap += "00w000000";
    tileMap += "000000000";
    break;
  default:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  }


  // Stuff for every test case
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  std::unique_ptr<PathfindingGraph> pg =
    std::unique_ptr<PathfindingGraph>(new PathfindingGraph(tileGrid));


  // Set search end point
  switch (caseNum)
  {
  case 1:
    pg->setSearchEnd(sf::Vector2f(25, 5), enemyLength);
    break;
  case 2:
    pg->setSearchEnd(sf::Vector2f(5, 5), enemyLength);
    break;
  case 3:
    pg->setSearchEnd(sf::Vector2f(5, 5), enemyLength);
    break;
  case 4:
    pg->setSearchEnd(sf::Vector2f(35, 25), enemyLength);
    break;
  case 5:
    pg->setSearchEnd(sf::Vector2f(75, 45), enemyLength);
    break;
  case 6:
    pg->setSearchEnd(sf::Vector2f(70, 40), enemyLength);
    break;
  default:
    std::cerr << "Invalid case number\n";
    assert(false); // no logical default
  }


  // Remainder of setup occurs outside of this method
  return pg;
} // setupMultiplePathfindingTests()

TEST_CASE("Corret paths #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupMultiplePathfindingTests(1, tileGrid);

  // Set up two start points


  // Run the algorithm


  // Test results

}

TEST_CASE("Correct paths #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupMultiplePathfindingTests(2, tileGrid);


}

TEST_CASE("Correct paths #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupMultiplePathfindingTests(3, tileGrid);


}

TEST_CASE("Correct paths #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupMultiplePathfindingTests(4, tileGrid);


}

TEST_CASE("Correct paths #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupMultiplePathfindingTests(5, tileGrid);


}

TEST_CASE("Correct paths #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto pg = setupMultiplePathfindingTests(6, tileGrid);


}