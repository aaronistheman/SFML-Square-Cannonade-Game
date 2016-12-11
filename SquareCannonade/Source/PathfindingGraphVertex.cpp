#include <Game/PathfindingGraphVertex.hpp>


const int PathfindingGraphVertex::NoPrevious = -1;
const int PathfindingGraphVertex::InfiniteMovementCost = INT_MAX;



sf::Vector2i PathfindingGraphVertex::getPosition() const
{
  return tile->getPosition();
}



sf::IntRect PathfindingGraphVertex::getRect() const
{
  return tile->getRect();
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