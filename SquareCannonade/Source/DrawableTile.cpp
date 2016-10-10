#include <Game/DrawableTile.hpp>
// #include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

DrawableTile::DrawableTile(int left, int top, int width, int height)
  : Tile(left, top, width, height)
  , mWhatToDraw(sf::Vector2f(width, height))
{
  // centerOrigin(mWhatToDraw);
  mWhatToDraw.setPosition(left, top);
}

void DrawableTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mWhatToDraw);
}