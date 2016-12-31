#include <Catch/Catch.hpp>
#include <GeneralHelpersForTests.hpp>

#include <Game/World.hpp>

#include <cassert>


/**
 * Set of tests for World::addWallsToTileMap
 */

const int NumTestCases = 2;

// This function is effectively meant to have two return values:
// returnedTileMap and goalTileMap
void setupAddWallsToTileMapTests(int caseNum,
  std::string &returnedTileMap, std::string &goalTileMap)
{
  assert(1 <= caseNum);
  assert(caseNum <= NumTestCases);

  int tileLength = 10;

  // Set area rect
  sf::IntRect area;
  switch (caseNum)
  {
  case 1:
    area = sf::IntRect(0, 0, 2 * tileLength, 2 * tileLength);
    break;
  case 2:
    area = sf::IntRect(0, 0, 4 * tileLength, 5 * tileLength);
    break;
  }
  assert(area != sf::IntRect());

  // Create initial tile map
  assert(returnedTileMap == "");
  returnedTileMap = createTileMapAllDefault(area, tileLength);

  // Create junk wall data
  std::vector<sf::IntRect> wallData;
  switch (caseNum)
  {
  case 1:
    wallData.push_back(sf::IntRect(1 * tileLength,
      1 * tileLength, tileLength, tileLength));
    break;
  case 2:
    wallData.push_back(sf::IntRect(2 * tileLength,
      1 * tileLength, tileLength, tileLength));
    wallData.push_back(sf::IntRect(1 * tileLength,
      2 * tileLength, tileLength, tileLength));
    wallData.push_back(sf::IntRect(2 * tileLength,
      2 * tileLength, tileLength, tileLength));
    wallData.push_back(sf::IntRect(3 * tileLength,
      2 * tileLength, tileLength, tileLength));
    wallData.push_back(sf::IntRect(2 * tileLength,
      3 * tileLength, tileLength, tileLength));
    break;
  }
  assert(wallData.size() > 0);
  
  // Run method on the initial tile map
  World::addWallsToTileMap(returnedTileMap, wallData, tileLength);

  // Create goal tile map
  assert(goalTileMap == "");
  switch (caseNum)
  {
  case 1:
    goalTileMap += "00";
    goalTileMap += "0w";
    break;
  case 2:
    goalTileMap += "0000";
    goalTileMap += "00w0";
    goalTileMap += "0www";
    goalTileMap += "00w0";
    goalTileMap += "0000";
    break;
  }
  assert(goalTileMap != "");

} // setupAddWallsToTileMapTests()

TEST_CASE("Correct tile map #1")
{
  std::string returnedTileMap = "";
  std::string goalTileMap = "";
  setupAddWallsToTileMapTests(1, returnedTileMap, goalTileMap);

  REQUIRE(returnedTileMap == goalTileMap);
}

TEST_CASE("Correct tile map #2")
{
  std::string returnedTileMap = "";
  std::string goalTileMap = "";
  setupAddWallsToTileMapTests(2, returnedTileMap, goalTileMap);

  REQUIRE(returnedTileMap == goalTileMap);
}