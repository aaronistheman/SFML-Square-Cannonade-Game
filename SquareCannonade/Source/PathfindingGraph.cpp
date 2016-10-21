#include <Game/PathfindingGraph.hpp>

#include <cassert>

const int PathfindingGraph::NondiagonalEdgeWeight = 10;
const int PathfindingGraph::DiagonalEdgeWeight = 14;

sf::Vector2i PathfindingGraphVertex::getPosition() const
{
  return tile->getPosition();
}

PathfindingGraph::PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid)
  : mVertices()
  , mNumEdges(0)
{
  createVertices(tileGrid);

  assert(tileGrid.size() > 0);
  int tileLength = tileGrid[0]->getLength();
  createEdges(tileLength);
}

int PathfindingGraph::getNumVertices() const
{
  return mVertices.size();
}

int PathfindingGraph::getNumEdges() const
{
  return mNumEdges;
}

/*
PGVertex * PathfindingGraph::getVertex(int rowIndex, int colIndex)
{
  // If attempting to access non-existent vertex
  if (rowIndex *)

  // Compute index for accessing the desired vertex
  int index = rowIndex * mNumVerticesPerRow + colIndex;

  return mVertices[index].get();
}
*/

PGVertex * PathfindingGraph::getVertex(sf::Vector2i position)
{
  for (auto & vertex : mVertices)
  {
    if (vertex->getPosition() == position)
      return vertex.get();
  }

  return nullptr;
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
void PathfindingGraph::createEdges(int tileLength)
{
  for (auto & vertex : mVertices)
  {
    createNondiagonalEdges(vertex, tileLength);
    createDiagonalEdges(vertex, tileLength);
  }

  // Edge counter is updated whenever a vertex is added to another
  // vertex's main adjacency list, so we must correct for double counting
  // (since each created edge updates the counter twice)
  assert(mNumEdges % 2 == 0); // should be even number
  mNumEdges /= 2;
}

void PathfindingGraph::createNondiagonalEdges(
  PGVertex::Ptr &vertex, int tileLength)
{
  sf::Vector2i position = vertex->getPosition();

  // Offsets to reach left, right, above, or below vertices
  sf::Vector2i nonDiagonalOffsets[4] = {
    sf::Vector2i(-tileLength, 0), sf::Vector2i(tileLength, 0),
    sf::Vector2i(0, -tileLength), sf::Vector2i(0, tileLength)
  };

  // Check if are adjacent vertices non-diagonally from
  // the current vertex
  for (auto & offset : nonDiagonalOffsets)
  {
    // Get the vertex (if any) at that offset
    sf::Vector2i newPosition = position + offset;
    PGVertex* adjacentVertex = getVertex(newPosition);

    if (adjacentVertex) // if found a vertex
    {
      // Add to appropriate adjacency lists
      vertex->adjacentVertices.push_back(adjacentVertex);
      vertex->adjacentNondiagonalVertices.push_back(adjacentVertex);

      mNumEdges++;
    }
  }
} // createNondiagonalEdges()

void PathfindingGraph::createDiagonalEdges(
  PGVertex::Ptr &vertex, int tileLength)
{
  sf::Vector2i position = vertex->getPosition();

  // Offsets to reach top-left, top-right, bottom-left, bottom-right
  sf::Vector2i diagonalOffsets[4] = {
    sf::Vector2i(-tileLength, -tileLength),
    sf::Vector2i(tileLength, -tileLength),
    sf::Vector2i(-tileLength, tileLength),
    sf::Vector2i(tileLength, tileLength)
  };

  // Check if are adjacent vertices diagonally from
  // the current vertex
  for (auto & offset : diagonalOffsets)
  {
    // Get the vertex (if any) at that offset
    sf::Vector2i newPosition = position + offset;
    PGVertex* adjacentVertex = getVertex(newPosition);

    if (adjacentVertex) // if found a vertex
    {
      if (true) // if there isn't a non-traversable tile in the way
      {
        // Add to appropriate adjacency lists
        vertex->adjacentVertices.push_back(adjacentVertex);
        vertex->adjacentDiagonalVertices.push_back(adjacentVertex);

        mNumEdges++;
      }
    }
  }
} // createDiagonalEdges()
