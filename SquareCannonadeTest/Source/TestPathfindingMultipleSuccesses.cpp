#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <iostream>




/**
 * IMPORTANT NOTE: This is an unfinished test set. It was meant
 * to help me find the cause of a bug, but then I happened to
 * find the bug's cause while writing the tests. I left the
 * tests unfinished because I don't think they add much value
 * (They practically just test the simple clean-up lines
 * used between calls to the A* methods.). The test cases
 * are commented out.
 */





/**
 * Tests the A* algorithm implementation in PathfindingGraph,
 * with MULTIPLE consecutive searches (i.e. multiple enemies)
 */

auto setupMultiplePathfindingTests(
  int caseNum, std::vector<Tile::Ptr>& tileGrid) // ,
  // std::vector<std::vector<unsigned int>>& paths)
{
  // Set tile and entity length
  int tileLength = 0, entityLength = 0;
  switch (caseNum)
  {
  default:
    // Have entityLength smaller than tileLength. This isn't crucial;
    // it just affects the start/end points of the test case.
    tileLength = 10;
    entityLength = 4;
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
    pg->setSearchEnd(sf::Vector2f(25, 5), entityLength);
    break;
  case 2:
    pg->setSearchEnd(sf::Vector2f(5, 5), entityLength);
    break;
  case 3:
    pg->setSearchEnd(sf::Vector2f(5, 5), entityLength);
    break;
  case 4:
    pg->setSearchEnd(sf::Vector2f(35, 25), entityLength);
    break;
  case 5:
    pg->setSearchEnd(sf::Vector2f(75, 45), entityLength);
    break;
  case 6:
    pg->setSearchEnd(sf::Vector2f(70, 40), entityLength);
    break;
  default:
    std::cerr << "Invalid case number\n";
    assert(false); // no logical default
  }


  // For the specified test case, set the start points, run
  // the algorithm, and store the paths.
  // The paths are stored
  // as a reference to a set of references to paths.
  std::unique_ptr<std::vector<std::unique_ptr<std::vector<unsigned int>>>> paths
    = std::unique_ptr<std::vector<std::unique_ptr<std::vector<unsigned int>>>>();
  switch (caseNum)
  {
  case 1:
    pg->setSearchStart(sf::Vector2f(5, 5), entityLength);
    paths->push_back(pg->generatePath(pg->performAStarSearch()));

    pg->setSearchStart(sf::Vector2f(5, 5), entityLength);
    paths->push_back(pg->generatePath(pg->performAStarSearch()));

    break;
  case 2: case 3: // both cases have same start points
    pg->setSearchStart(sf::Vector2f(25, 5), entityLength);
    paths->push_back(pg->generatePath(pg->performAStarSearch()));

    pg->setSearchStart(sf::Vector2f(5, 25), entityLength);
    paths->push_back(pg->generatePath(pg->performAStarSearch()));

    pg->setSearchStart(sf::Vector2f(25, 25), entityLength);
    paths->push_back(pg->generatePath(pg->performAStarSearch()));

    break;
  case 4:
    // pg->set

    break;
  case 5:

    break;
  case 6:

    break;
  default:
    assert(false);
  }


  return paths;
} // setupMultiplePathfindingTests()

/*
TEST_CASE("Corret paths #1")
{
  std::vector<Tile::Ptr> tileGrid;
  // std::vector<std::vector<unsigned int>> paths;
  // auto pg = setupMultiplePathfindingTests(1, tileGrid, paths);
  
  // Test results

}

TEST_CASE("Correct paths #2")
{
  std::vector<Tile::Ptr> tileGrid;
  std::vector<std::vector<unsigned int>> paths;
  auto pg = setupMultiplePathfindingTests(2, tileGrid, paths);


}

TEST_CASE("Correct paths #3")
{
  std::vector<Tile::Ptr> tileGrid;
  std::vector<std::vector<unsigned int>> paths;
  auto pg = setupMultiplePathfindingTests(3, tileGrid, paths);


}

TEST_CASE("Correct paths #4")
{
  std::vector<Tile::Ptr> tileGrid;
  std::vector<std::vector<unsigned int>> paths;
  auto pg = setupMultiplePathfindingTests(4, tileGrid, paths);


}

TEST_CASE("Correct paths #5")
{
  std::vector<Tile::Ptr> tileGrid;
  std::vector<std::vector<unsigned int>> paths;
  auto pg = setupMultiplePathfindingTests(5, tileGrid, paths);


}

TEST_CASE("Correct paths #6")
{
  std::vector<Tile::Ptr> tileGrid;
  std::vector<std::vector<unsigned int>> paths;
  auto pg = setupMultiplePathfindingTests(6, tileGrid, paths);


}
*/