#include <Tile/DefaultTile.hpp>

DefaultTile::DefaultTile(int left, int top, int width, int height)
  : Tile(left, top, width, height, TileType::Default, 0)
{

}

void DefaultTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}