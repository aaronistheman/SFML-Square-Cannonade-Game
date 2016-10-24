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
      /**
       * Now, we have to check if a non-traversable tile is in the way.
       * For example, say I have the following tile setup:
       *     A B
       *     C D
       * (where D is a wall tile).
       * There shouldn't be an edge from B to C, because such an edge
       * would allow an entity to partially "go through the wall"
       * represented by D as said entity travels from B directly to C.
       * The following bool variable is false if there is such a
       * wall that prevents the creation of a diagonal edge.
       * (Note that A could also prevent the creation of the edge BC
       * by being a wall tile.)
       */
      bool canTraverseDiagonally = true;

      // The first vertex-to-check is vertically aligned with current vertex
      // (e.g. like A in the above block comment's example)
      sf::Vector2i positionToCheck1 = position + sf::Vector2i(0, offset.y);
      PGVertex* vertexToCheck1 = getVertex(positionToCheck1);

      // The second vertex-to-check is horizontally aligned with the current
      // vertex (e.g. like D in the above block comment's example)
      sf::Vector2i positionToCheck2 = position + sf::Vector2i(offset.x, 0);
      PGVertex* vertexToCheck2 = getVertex(positionToCheck2);

      if (!(vertexToCheck1 && vertexToCheck2)) // if either vertex is
                                               // non-traversable
      {
        canTraverseDiagonally = false;
      }

      if (canTraverseDiagonally)
      {
        // Add to appropriate adjacency lists
        vertex->adjacentVertices.push_back(adjacentVertex);
        vertex->adjacentDiagonalVertices.push_back(adjacentVertex);

        mNumEdges++;
      }
    }
  }
} // createDiagonalEdges()
