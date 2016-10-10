#include <Game/DrawableTile.hpp>

#include <iostream>

DrawableTile::DrawableTile(int left, int top, int width, int height)
  : Tile(left, top, width, height)
{

}

void DrawableTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::cout << "DrawableTile::draw()\n";
}