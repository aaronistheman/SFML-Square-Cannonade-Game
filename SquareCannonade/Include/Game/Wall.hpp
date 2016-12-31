#pragma once


#include <SFML/Graphics/Rect.hpp>


class Wall
{
public:
  Wall(int left, int top, int width, int height);

  sf::IntRect   getBoundingRect() const;

  // Returns true if the given entity-related data proves the entity
  // is colliding with this wall.
  bool    entityCollidesWithWall(sf::IntRect entityRect);

private:
  // Storage for wall's location and size
  sf::IntRect     mRect;
}; // class Wall