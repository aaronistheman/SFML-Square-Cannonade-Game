#pragma once

#include <Game/Tile.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

/**
 * This class is strictly for debugging purposes
 * (so I can see where a certain tile is) and is
 * thus a little wasteful memory-wise.
 */
class DrawableTile : public Tile, public sf::Drawable
{
public:
  typedef std::unique_ptr<DrawableTile> Ptr;

public:
  DrawableTile(int left, int top, int width, int height);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::RectangleShape mWhatToDraw;
};