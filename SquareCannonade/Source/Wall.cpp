#include <Game/Wall.hpp>


Wall::Wall(int left, int top, int width, int height)
  : mRect(left, top, width, height)
{
}

sf::IntRect Wall::getBoundingRect() const
{
  return mRect;
}

bool Wall::entityCollidesWithWall(sf::IntRect entityRect,
  sf::IntRect &intersectionRect)
{
  return mRect.intersects(entityRect, intersectionRect);
}
