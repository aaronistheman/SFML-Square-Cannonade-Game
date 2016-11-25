#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <stack>
#include <iostream> // for debugging

const int PathfindingGraphVertex::NoPrevious = -1;
const int PathfindingGraphVertex::InfiniteMovementCost = INT_MAX;

const int PathfindingGraph::NondiagonalEdgeWeight = 10;
const int PathfindingGraph::DiagonalEdgeWeight = 14;

sf::Vector2i PathfindingGraphVertex::getPosition() const
{
  return tile->getPosition();
}

sf::IntRect PathfindingGraphVertex::getRect() const
{
  return tile->getRect();
}

bool PathfindingGraphVertex::isDiagonallyAdjacent(
  const PathfindingGraphVertex * vertex)
{
  for (auto const& d : adjacentDiagonalVertices)
  {
    if (d == vertex) // the given vertex matches a diagonal neighbor
      return true;
  }
}

PathfindingGraph::PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid)
  : mVertices()
  , mNumEdges(0)
  , mSearchStartVertices()
  , mSearchEndVertices()
  , mUnresolvedVertices()
{
  createVertices(tileGrid);

  assert(tileGrid.size() > 0);
  int tileLength = tileGrid[0]->getLength();
  createEdges(tileLength);
}

size_t PathfindingGraph::getNumVertices() const
{
  return mVertices.size();
}

unsigned int PathfindingGraph::getNumEdges() const
{
  return mNumEdges;
}

PGVertex * PathfindingGraph::getVertex(sf::Vector2i position)
{
  for (auto & vertex : mVertices)
  {
    if (vertex->getPosition() == position)
      return vertex.get();
  }

  return nullptr;
}

size_t PathfindingGraph::getNumSearchStartVertices() const
{
  return mSearchStartVertices.size();
}

const std::vector<PGVertex*>& PathfindingGraph::getSearchStartVertices() const
{
  return mSearchStartVertices;
}

size_t PathfindingGraph::getNumSearchEndVertices() const
{
  return mSearchEndVertices.size();
}

const std::vector<PGVertex*>& PathfindingGraph::getSearchEndVertices() const
{
  return mSearchEndVertices;
}

void PathfindingGraph::setSearchStart(sf::Vector2f entityCenterPosition,
  int entityWidth, int entityHeight)
{
  setSearchStartOrEnd(true, entityCenterPosition, entityWidth, entityHeight);
}

void PathfindingGraph::setSearchEnd(sf::Vector2f entityCenterPosition,
  int entityWidth, int entityHeight)
{
  setSearchStartOrEnd(false, entityCenterPosition, entityWidth, entityHeight);
}

void PathfindingGraph::setSearchStart(sf::Vector2f entityCenterPosition,
  int entityLength)
{
  setSearchStart(entityCenterPosition, entityLength, entityLength);
}

void PathfindingGraph::setSearchEnd(sf::Vector2f entityCenterPosition,
  int entityLength)
{
  setSearchEnd(entityCenterPosition, entityLength, entityLength);
}

/**
 * Note: I know it's bad practice to implement an algorithm that
 * something like the Boost library has already implemented,
 * but I just implemented this for the fun of it.
 *
 * The pseudocode found on the Wikipedia page cited in the readme
 * greatly helped in implementing this algorithm.
 */
unsigned int PathfindingGraph::performAStarSearch()
{
  setUpAStarSearch();
  
  // this while loop shouldn't end by the condition being false
  while (!mUnresolvedVertices.empty())
  {
    PGVertex* vertex = getNextAStarVertex();

    if (isGoalVertex(vertex))
    {
      // reached the goal; abandon the search
      return getIndex(vertex);
    }

    // this vertex is about to be evaluated; mark it resolved
    vertex->resolutionStatus = PGVertex::ResolutionStatus::Resolved;

    // for each neighbor of current vertex
    for (auto const& neighbor : vertex->adjacentVertices)
    {
      // if neighbor not in closed set (i.e. not already evaluated)
      if (neighbor->resolutionStatus != PGVertex::ResolutionStatus::Resolved)
      {
        // determine if neighbor is diagonally adjacent,
        // then pick which edge weight to use
        int edgeWeight = 0;
        if (vertex->isDiagonallyAdjacent(neighbor))
          edgeWeight = DiagonalEdgeWeight;
        else
          edgeWeight = NondiagonalEdgeWeight;

        // set newMovementCost to current vertex's movementCost plus
        // ...distance to get to that neighbor
        int newMovementCost = vertex->movementCost + edgeWeight;

        // if neighbor not in open set (i.e. if found a new node)
        if (neighbor->resolutionStatus == PGVertex::ResolutionStatus::Untouched)
        {
          // add neighbor to the open set
          mUnresolvedVertices.push(neighbor);
          neighbor->resolutionStatus = PGVertex::ResolutionStatus::CouldResolve;
        }

        // if newMovementCost < neighbor's movementCost (i.e. if
        // ...found better path); for just touched vertices,
        // this block is still run
        if (newMovementCost < neighbor->movementCost)
        {
          // update neighbor's pv
          neighbor->previousVertexIndex = getIndex(vertex);

          // update neighbor's movementCost to be newMovementCost
          neighbor->movementCost = newMovementCost;

          // update neighbor's estimatedMovementCost to be
          // ...neighbor's movementCost + h(neighbor)
          neighbor->estimatedMovementCost = neighbor->movementCost;
        }
      } // if neighbor not in closed set
    } // for each neighbor of the closed vertex
  }

  // failed to reach goal; create failed assertion
  assert(false);

} // performAStarSearch()

std::vector<unsigned int> * PathfindingGraph::generatePath(int pathEndingVertexId)
{
  // Setup
  std::stack<unsigned int> reversedPath;
  reversedPath.push(pathEndingVertexId);

  // Trace back from the (given) index of the path-ending vertex until
  // the start vertex is reached, updating the stack with the reversed path
  auto vertex = mVertices[pathEndingVertexId].get();
  while (vertex->previousVertexIndex != PGVertex::NoPrevious)
  {
    int pv = vertex->previousVertexIndex;
    reversedPath.push(pv);
    vertex = mVertices[pv].get();
  }

  // Use the stack to generate the correct (non-reversed) path
  auto path = new std::vector<unsigned int>;
  while (!reversedPath.empty())
  {
    path->push_back(reversedPath.top());
    reversedPath.pop();
  }

  return path;
} // generatePath()

void PathfindingGraph::printAStarTable() const
{
  // Table header
  std::cout << "\n--------------------------------------\n";
  std::cout << "index pv movementCost estimatedMovementCost\n";

  for (unsigned int i = 0; i < mVertices.size(); ++i)
  {
    auto & vertex = mVertices[i];
    std::cout << i << ' ' << vertex->previousVertexIndex << ' '
      << vertex->movementCost << ' ' << vertex->estimatedMovementCost << '\n';
  }

  std::cout << "\n--------------------------------------\n\n";
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
    } // if found a vertex
  } // for each diagonal offset
} // createDiagonalEdges()


void PathfindingGraph::setSearchStartOrEnd(bool isSettingStart,
  sf::Vector2f centerPosition, int width, int height)
{
  // Form a rectangle representing the entity's position
  sf::Vector2i topLeft = sf::Vector2i(
    (int)centerPosition.x - width / 2,
    (int)centerPosition.y - height / 2);
  sf::IntRect entityRect = sf::IntRect(topLeft, sf::Vector2i(width, height));

  // Note each vertex that's area intersects the entity's rectangle
  for (auto const &ptr : mVertices)
  {

    if (ptr->getRect().intersects(entityRect))
    {
      if (isSettingStart)
        mSearchStartVertices.push_back(ptr.get());
      else
        mSearchEndVertices.push_back(ptr.get());
    }
  }
} // setSearchStartOrEnd()

void PathfindingGraph::setUpAStarSearch()
{
  // initialize each vertex's data
  for (auto& vertex : mVertices) // for each vertex
  {
    vertex->previousVertexIndex = PGVertex::NoPrevious;
    vertex->movementCost = vertex->estimatedMovementCost
      = PGVertex::InfiniteMovementCost;
    vertex->resolutionStatus = PGVertex::ResolutionStatus::Untouched;
  }

  // create open set with the start vertices; clear each
  // start vertex's movement cost, since they're reached by default
  mUnresolvedVertices = std::priority_queue<PGVertex*,
    std::vector<PGVertex*>, CompareVerticesEstimatedMovementCost>();
  for (auto& vertex : mSearchStartVertices)
  {
    mUnresolvedVertices.push(vertex);
    vertex->resolutionStatus = PGVertex::ResolutionStatus::CouldResolve;
    vertex->movementCost = 0;
  }
} // setUpAStarSearch()

void PathfindingGraph::cleanUpAStarSearch()
{
  mSearchStartVertices.clear();
  mSearchEndVertices.clear();
} // cleanUpAStarSearch()

bool PathfindingGraph::isGoalVertex(PGVertex * vertex) const
{
  for (auto& const g : mSearchEndVertices)
  {
    if (vertex == g) // if given vertex is one of the goal vertices
      return true;
  }

  return false; // found no match
}

PGVertex * PathfindingGraph::getNextAStarVertex()
{
  assert(mUnresolvedVertices.size() > 0);

  // Keep checking vertices with the lowest estimated movement cost until
  // find data on a vertex that can be resolved
  PGVertex * selected = mUnresolvedVertices.top();
  mUnresolvedVertices.pop();

  while (selected->resolutionStatus != PGVertex::ResolutionStatus::CouldResolve)
  {
    // If this assertion is false, then there's no more data regarding
    // more pathfinding, so the algorithm should've finished
    assert(mUnresolvedVertices.size() > 0);

    selected = mUnresolvedVertices.top();
    mUnresolvedVertices.pop();
  }

  return selected;
} // getNextAStarVertex()

unsigned int PathfindingGraph::getIndex(const PGVertex * vertex) const
{
  // Can't use foreach loop because need index
  for (unsigned int i = 0; i < mVertices.size(); ++i)
  {
    if (mVertices[i].get() == vertex) // if found the vertex
      return i; // return the vertex's index
  }
}
