#pragma once

#include <Tile/TileMapConstants.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>

class Tile : public sf::Drawable
{
public:
  typedef std::unique_ptr<Tile> Ptr;

public:
  Tile(int left, int top, int width, int height, TileType type, int penalty);

  sf::IntRect getRect() const;
  int getPenalty() const;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

private:
  sf::IntRect mRect;

  TileType mType;
  int mPenalty; // corresponds to this vertex's cost in pathfinding graph
};