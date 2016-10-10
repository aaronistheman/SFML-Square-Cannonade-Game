#include <Catch/Catch.hpp>

#include <Game/World.hpp>
#include <Game/Tile.hpp>

#include <vector>

TEST_CASE("Created correct number of tiles") {

  std::vector<Tile::Ptr> tileGrid;
  REQUIRE(tileGrid.size() == 2);
}

TEST_CASE("Correct positions of tiles") {

}