#include <Game/WallTile.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

WallTile::WallTile(int left, int top, int width, int height)
  : Tile(left, top, width, height)
  , mSprite(sf::Vector2f(width, height))
{
  mSprite.setPosition(left, top);
}

void WallTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite);
}