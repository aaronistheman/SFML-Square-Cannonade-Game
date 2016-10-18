#include <Game/PathfindingGraph.hpp>

PathfindingGraph::PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid)
  : mVertices()
{
  // Can't seem to use foreach loop here
  for (auto itr = tileGrid.begin(); itr != tileGrid.end(); ++itr)
  {
    Tile* tile = itr->get();

    // Only bother creating a vertex if that vertex can be used by
    // a traveling entity
    if (tile->isTraversable())
    {
      PGVertex *vertex = new PGVertex;
      vertex->tile = itr->get();
      mVertices.push_back(PGVertex::Ptr(vertex));
    }
  }
}

int PathfindingGraph::getNumVertices() const
{
  return mVertices.size();
}

int PathfindingGraph::getNumEdges() const
{
  return 0; // to be implemented correctly
}