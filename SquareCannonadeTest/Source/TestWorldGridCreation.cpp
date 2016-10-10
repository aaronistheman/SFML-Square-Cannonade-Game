#include <Catch/Catch.hpp>

#include <Game/World.hpp>
#include <Game/Tile.hpp>

#include <vector>

TEST_CASE("Created correct number of tiles #1") {

  std::vector<Tile::Ptr> tileGrid;
  sf::IntRect rect(0, 0, 1200, 600);
  int tileLength = 30;

  World::createGrid(tileGrid, rect, tileLength);

  REQUIRE(tileGrid.size() == 2);
}

/*
TEST_CASE("Correct positions of tiles") {

}
*/