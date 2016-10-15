#pragma once

#include <Tile/Tile.hpp>

class DefaultTile : public Tile
{
public:
  typedef std::unique_ptr<DefaultTile> Ptr;

public:
  DefaultTile(int left, int top, int width, int height);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};