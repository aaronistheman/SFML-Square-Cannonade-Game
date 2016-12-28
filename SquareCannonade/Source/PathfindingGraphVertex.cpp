#include <Game/PathfindingGraphVertex.hpp>


const int PathfindingGraphVertex::NoPrevious = -1;
const int PathfindingGraphVertex::InfiniteMovementCost = INT_MAX;



sf::Vector2i PathfindingGraphVertex::getPosition() const
{
  return tile->getPosition();
}

sf::Vector2i PathfindingGraphVertex::getCenterPosition() const
{
  sf::Vector2i topLeftPos = getPosition();
  int halfLength = getTileLength() / 2;

  return sf::Vector2i(topLeftPos.x + halfLength, topLeftPos.y + halfLength);
}

sf::IntRect PathfindingGraphVertex::getRect() const
{
  return tile->getRect();
}

int PathfindingGraphVertex::getTileLength() const
{
  return tile->getLength();
}



bool PathfindingGraphVertex::isDiagonallyAdjacent(
  const PathfindingGraphVertex * vertex) const
{
  for (auto const& d : adjacentDiagonalVertices)
  {
    if (d == vertex) // the given vertex matches a diagonal neighbor
      return true;
  }
}