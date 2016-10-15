#include <Catch/Catch.hpp>

#include <Tile/TileSet.hpp>
#include <Tile/DefaultTile.hpp>

TEST_CASE("TileSet::addTile() #1")
{
  TileSet tileSet;
  tileSet.addTile(Tile::Ptr(new DefaultTile(0, 30, 30, 30)));
  tileSet.addTile(Tile::Ptr(new DefaultTile(30, 30, 30, 30)));
  tileSet.addTile(Tile::Ptr(new DefaultTile(60, 30, 30, 30)));

  REQUIRE(tileSet.getSize() == 3);
}