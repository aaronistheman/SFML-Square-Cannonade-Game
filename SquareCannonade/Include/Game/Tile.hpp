#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <memory>

class Tile
{
public:
  typedef std::unique_ptr<Tile> Ptr;

public:
  Tile(int left, int top, int width, int height);

  sf::IntRect getRect() const;

private:
  sf::IntRect mRect;
};