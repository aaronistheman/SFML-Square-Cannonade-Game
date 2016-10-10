#include <Catch/Catch.hpp>

#include <Game/TileSet.hpp>

TEST_CASE("TileSet::addTile() #1")
{
  TileSet tileSet;
  tileSet.addTile(Tile::Ptr(new Tile(0, 30, 30, 30)));
  tileSet.addTile(Tile::Ptr(new Tile(30, 30, 30, 30)));
  tileSet.addTile(Tile::Ptr(new Tile(60, 30, 30, 30)));

  REQUIRE(tileSet.getSize() == 3);
}