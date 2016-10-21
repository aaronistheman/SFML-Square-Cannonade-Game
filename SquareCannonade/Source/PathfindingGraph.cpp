#include <Game/PathfindingGraph.hpp>

PathfindingGraph::PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid)
  : mVertices()
  , mNumEdges(0)
{
  createVertices(tileGrid);
  createEdges();
}

int PathfindingGraph::getNumVertices() const
{
  return mVertices.size();
}

int PathfindingGraph::getNumEdges() const
{
  return mNumEdges;
}

void PathfindingGraph::createVertices(const std::vector<Tile::Ptr> &tileGrid)
{
  for (auto const& tile : tileGrid)
  {
    // Only bother creating a vertex if that vertex can be used by
    // a traveling entity
    if (tile->isTraversable())
    {
      PGVertex *vertex = new PGVertex;
      vertex->tile = tile.get();
      mVertices.push_back(PGVertex::Ptr(vertex));
    }
  }
}

// Creates edges (which are represented in the vertices' adjacency
// lists) by checking which vertices are adjacent to each other
// (whether through a possible diagonal edge or non-diagonal edge)
void PathfindingGraph::createEdges()
{
  // For each vertex
    // For each coordinate a tile length to left, above, right, or below
      // If tile exists there
        // Add to approriate adjacency lists
        // Update edge count
    // For each coordinate diagonally from current vertex
      // If tile exists there
        // If there isn't a non-traversable tile in the way
          // Add to appropriate adjacency lists
          // Update edge count
}