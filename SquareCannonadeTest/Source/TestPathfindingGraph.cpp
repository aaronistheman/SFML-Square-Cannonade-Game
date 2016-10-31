#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/PathfindingGraph.hpp>

#include <cassert>


/**
 * There are multiple different test sets involving PathfindingGraph
 * in this file.
 */




/**
 * Tests for creation of correct number of vertices
 */

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




/**
 * Tests for accessing vertex by position
 */

TEST_CASE("Vertex access by position #1: successful find")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 10);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Get vertex to assert about
  int left = tileLength;
  int top = 0;
  PGVertex* vertex = pg.getVertex(sf::Vector2i(left, top));

  // Assertion
  REQUIRE(vertex);
  REQUIRE(vertex->tile->getRect().left == left);
  REQUIRE(vertex->tile->getRect().top == top);
}

TEST_CASE("Vertex access by position #2: successful find")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Get vertex to assert about
  int left = tileLength;
  int top = tileLength;
  PGVertex* vertex = pg.getVertex(sf::Vector2i(left, top));

  // Assertion
  REQUIRE(vertex);
  REQUIRE(vertex->tile->getRect().left == left);
  REQUIRE(vertex->tile->getRect().top == top);
}

TEST_CASE("Vertex access by position #3: fail to find")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Try to get vertex to assert about
  int left = tileLength * 2;
  int top = 0;
  PGVertex* vertex = pg.getVertex(sf::Vector2i(left, top));

  // Assertion
  REQUIRE(!vertex);
}





/**
 * Tests for creation of correct number of edges
 */

// Test for creation of one non-diagonal edge
TEST_CASE("Created correct number of edges #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 10);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 1);
}

// Test for creation of a complete graph ("complete" as in there
// exists an edge between every pair of vertices)
TEST_CASE("Created correct number of edges #2")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 6);
}

// Basic test for the exclusion of an edge that would let an entity
// cut diagonally across a wall
TEST_CASE("Created correct number of edges #3")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  std::string tileMap = "";
  tileMap += "00";
  tileMap += "0w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 2);
}

TEST_CASE("Created correct number of edges #4")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 30, 20);
  int tileLength = 10;

  // Use tile map with no walls
  std::string tileMap = createTileMapAllDefault(rect, tileLength);

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 11);
}

TEST_CASE("Created correct number of edges #5")
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

TEST_CASE("Created correct number of edges #6")
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

// Another test meant to make sure no edges that would let entities
// partially cut across walls are created
TEST_CASE("Created correct number of edges #7")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 20, 20);
  int tileLength = 10;

  std::string tileMap = "";
  tileMap += "w0";
  tileMap += "0w";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Assertion
  REQUIRE(pg.getNumEdges() == 0);
}




/**
 * Tests for setting vertices at which pathfinding search should start
 */

PathfindingGraph* setupPathfindingSearchStartTests(int caseNum)
{
  std::vector<Tile::Ptr> tileGrid;

  // Set tileLength
  int tileLength = 0;
  switch (caseNum)
  {
  case 5:
    tileLength = 5;
    break;
  default:
    tileLength = 10;
    break;
  }
  int enemyLength = tileLength;

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1:
    area = sf::IntRect(0, 0, 50, 40);
    break;
  default:
    assert(false); // shouldn't be reached
    break;
  }

  // Create tile map
  std::string tileMap = "";
  switch (caseNum)
  {
  default:
    tileMap = createTileMapAllDefault(area, tileLength);
    break;
  }

  // Stuff for every test case
  runCreateGrid(tileGrid, area, tileLength, tileMap);
  PathfindingGraph* pg = new PathfindingGraph(tileGrid);

  // Run method-to-test
  switch (caseNum)
  {
  case 1:
    pg->setSearchStart(sf::Vector2f(29, 18), enemyLength, enemyLength);
    break;
  }

  return pg;
}

TEST_CASE("Setting pathfinding search's start vertices #1")
{
  PathfindingGraph* pg = setupPathfindingSearchStartTests(1);

  // Assertion
  REQUIRE(pg->getNumSearchStartVertices() == 4);
}

TEST_CASE("Setting pathfinding search's start vertices #2")
{

}

/*
TEST_CASE("Setting pathfinding search's start vertices #3")
{

}

TEST_CASE("Setting pathfinding search's start vertices #4")
{

}

TEST_CASE("Setting pathfinding search's start vertices #5")
{

}
*/




/**
 * Tests for finding the correct path with pathfinding algorithm
 */

/*
TEST_CASE("Found correct path in search #1")
{
  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 30, 20);
  int tileLength = 10;

  std::string tileMap = "";
  tileMap += "000";
  tileMap += "0w0";

  runCreateGrid(tileGrid, rect, tileLength, tileMap);
  PathfindingGraph pg(tileGrid);

  // Run method-to-test
  PGVertex** path = pg.generatePath(pg.performAStarSearch());

  // Assertion
  REQUIRE(path);
  REQUIRE(path[0]);
  REQUIRE(path[1]);
}
*/