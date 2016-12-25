#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <iostream>



/**
 * There are two sets of tests (one for finding the correct path ending,
 * and one for finding the correct path itself) in this file.
 */







/**
 * Tests for performAStarSearch() (that is, for finding correct path
 * ending vertex)
 */

std::unique_ptr<PathfindingGraph> setupPathfindingEndTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // Set tile and enemy length
  int tileLength = 0;
  int enemyLength = 0;
  switch (caseNum)
  {
  case 1: case 2: case 3: case 6: // if tile should be larger than enemy
    tileLength = 10;
    enemyLength = 5;
    break;
  default:
    tileLength = 10;
    enemyLength = 10;
    break;
  }
  // So I don't mess up:
  assert(tileLength != 0);
  assert(enemyLength != 0);

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1:
    area = sf::IntRect(0, 0, 30, 10);
    break;
  case 2:
    area = sf::IntRect(0, 0, 30, 20);
    break;
  case 3:
    area = sf::IntRect(0, 0, 200, 200);
    break;
  case 4:
    area = sf::IntRect(0, 0, 80, 20);
    break;
  case 5:
    area = sf::IntRect(0, 0, 70, 70);
    break;
  case 6:
    area = sf::IntRect(0, 0, 20, 20);
    break;
  case 7:
    area = sf::IntRect(0, 0, 100, 90);
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
  case 2:
    tileMap += "000";
    tileMap += "0w0";
    break;
  case 3: // just one wall for first spot of second row
    tileMap = createTileMapAllDefault(area, tileLength);
    tileMap.at(20) = 'w';
    break;
  case 4:
    tileMap += "00000000";
    tileMap += "00w00000";
    break;
  case 7:
    tileMap += "0000000000";
    tileMap += "0000000000";
    tileMap += "000wwww000";
    tileMap += "000wwww000";
    tileMap += "000wwww000";
    tileMap += "000wwww000";
    tileMap += "0000www000";
    tileMap += "0000000000";
    tileMap += "0000000000";
    break;
  default:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  }

  // Stuff for every test case
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  std::unique_ptr<PathfindingGraph> pg =
    std::unique_ptr<PathfindingGraph>(new PathfindingGraph(tileGrid));

  // Set search start and end
  switch (caseNum)
  {
  case 1:
    pg->setSearchStart(sf::Vector2f(5, 5), enemyLength);
    pg->setSearchEnd(sf::Vector2f(25, 5), enemyLength);
    break;
  case 2:
    pg->setSearchStart(sf::Vector2f(5, 15), enemyLength);
    pg->setSearchEnd(sf::Vector2f(25, 15), enemyLength);
    break;
  case 3:
    pg->setSearchStart(sf::Vector2f(5, 5), enemyLength);
    pg->setSearchEnd(sf::Vector2f(195, 195), enemyLength);
    break;
  case 4:
    pg->setSearchStart(sf::Vector2f(10, 10), enemyLength);
    pg->setSearchEnd(sf::Vector2f(70, 10), enemyLength);
    break;
  case 5:
    pg->setSearchStart(sf::Vector2f(60, 60), enemyLength);
    pg->setSearchEnd(sf::Vector2f(9, 11), enemyLength);
    break;
  case 6:
    pg->setSearchStart(sf::Vector2f(5, 15), enemyLength);
    pg->setSearchEnd(sf::Vector2f(15, 5), enemyLength);
    break;
  case 7:
    pg->setSearchStart(sf::Vector2f(80, 80), enemyLength);
    pg->setSearchEnd(sf::Vector2f(18, 11), enemyLength);
    break;
  default:
    std::cerr << "Invalid case number\n";
    assert(false); // no logical default
  }

  return pg;
} // setupPathfindingEndTests()

TEST_CASE("Correct path end #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(1, tileGrid)->performAStarSearch();

  REQUIRE(index == 2);
}

TEST_CASE("Correct path end #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(2, tileGrid)->performAStarSearch();

  REQUIRE(index == 4);
}

TEST_CASE("Correct path end #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(3, tileGrid)->performAStarSearch();

  REQUIRE(index == 398);
}

TEST_CASE("Correct path end #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(4, tileGrid)->performAStarSearch();

  REQUIRE(index == 6);
}

TEST_CASE("Correct path end #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(5, tileGrid)->performAStarSearch();

  REQUIRE(index == 8);
}

TEST_CASE("Correct path end #6")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(6, tileGrid)->performAStarSearch();

  REQUIRE(index == 1);
}

TEST_CASE("Correct path end #7")
{
  std::vector<Tile::Ptr> tileGrid;
  auto index = setupPathfindingEndTests(7, tileGrid)->performAStarSearch();

  REQUIRE(index == 12);
}







/**
 * Tests for finding the correct path with pathfinding algorithm
 */

std::vector<unsigned int> * setupGeneratePathTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid)
{
  // The test cases are handled in this method, which means performAStarSearch()
  // and generatePath() have same test cases (but different tested values)
  auto pg = setupPathfindingEndTests(caseNum, tileGrid);

  int pathEndingVertexId = pg->performAStarSearch();

  // run method-to-test
  return pg->generatePath(pathEndingVertexId);
} // setupGeneratePathTests()

TEST_CASE("Found correct path #1")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(1, tileGrid);

  REQUIRE(path.size() == 3);
  REQUIRE(path[0] == 0);
  REQUIRE(path[1] == 1);
  REQUIRE(path[2] == 2);
}

TEST_CASE("Found correct path #2")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(2, tileGrid);

  REQUIRE(path.size() == 5);
  REQUIRE(path[0] == 3);
  REQUIRE(path[1] == 0);
  REQUIRE(path[2] == 1);
  REQUIRE(path[4] == 4);
}

TEST_CASE("Found correct path #3")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(3, tileGrid);

  REQUIRE(path.size() == 21);
  REQUIRE(path[0] == 0);
  REQUIRE(path[1] == 1);
  REQUIRE(path[20] == 398);
}

TEST_CASE("Found correct path #4")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(4, tileGrid);

  REQUIRE(path.size() == 6);
  REQUIRE(path[0] == 1);
  REQUIRE(path[1] == 2);
  REQUIRE(path[2] == 3);
}

TEST_CASE("Found correct path #5")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(5, tileGrid);

  REQUIRE(path.size() == 5);
  REQUIRE(path[0] == 40);
  REQUIRE(path[1] == 32);
  REQUIRE(path[2] == 24);
}

TEST_CASE("Found correct path #6")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(6, tileGrid);

  REQUIRE(path.size() == 2);
  REQUIRE(path[0] == 2);
  REQUIRE(path[1] == 1);
}

TEST_CASE("Found correct path #7")
{
  std::vector<Tile::Ptr> tileGrid;
  auto path = *setupGeneratePathTests(7, tileGrid);

  REQUIRE(path.size() == 11);
  REQUIRE(path[0] == 58);
  REQUIRE(path[1] == 57);
  REQUIRE(path[2] == 56);
}