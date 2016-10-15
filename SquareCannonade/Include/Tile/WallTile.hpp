#pragma once

#include <Tile/Tile.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

class WallTile : public Tile
{
public:
  typedef std::unique_ptr<WallTile> Ptr;

public:
  WallTile(int left, int top, int width, int height);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::RectangleShape mSprite;
};