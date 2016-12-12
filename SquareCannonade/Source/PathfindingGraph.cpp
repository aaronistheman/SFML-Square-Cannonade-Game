#include <Game/PathfindingGraph.hpp>

#include <cassert>
#include <stack>
#include <iostream> // for debugging
#include <string>



const int PathfindingGraph::NondiagonalEdgeWeight = 10;
const int PathfindingGraph::DiagonalEdgeWeight = 14;



PossibleAStarEdgeSelection::PossibleAStarEdgeSelection(
  int vtcf, int vtr, int mc, int emc)
  : vertexToComeFromIndex(vtcf)
  , vertexToResolveIndex(vtr)
  , movementCost(mc)
  , estimatedMovementCost(emc)
{
}




PathfindingGraph::PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid)
  : mVertices()
  , mNumEdges(0)
  , mSearchStartVertices()
  , mSearchEndVertices()
  , mPossibleEdgeSelections()
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

  // One vertex is resolved per iteration
  auto numVertices = getNumVertices();
  for (size_t i = 0; i < numVertices; ++i)
  {
    auto selectedEdge = getNextAStarEdge();
    auto vertex = mVertices.at(selectedEdge.vertexToResolveIndex).get();

    // Update the found vertex, just in case its data is from a different
    // (worse) selectable edge more recently put in the heap
    vertex->previousVertexIndex = selectedEdge.vertexToComeFromIndex;
    vertex->movementCost = selectedEdge.movementCost;
    vertex->estimatedMovementCost = selectedEdge.estimatedMovementCost;
    vertex->resolutionStatus = PGVertex::ResolutionStatus::Resolved;

    // if reached the goal, abandon the search
    if (isGoalVertex(vertex))
    {
      clearVerticesSets();
      return getIndex(vertex);
    }

    updateNeighborsAStar(vertex);
  }

  // Resolved all vertices reachable from the start vertex/vertices,
  // but failed to reach the goal, violating a prerequisite of use
  // of this method
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



int PathfindingGraph::getEstimatedGraphDistanceInTiles(
  const PGVertex * current) const
{
  // Find minimum real horizontal distance between given vertex and
  // any end vertex
  int minRealHorizontalDistance = INT_MAX;
  int d = 0;
  for (const auto &endVertex : mSearchEndVertices)
  {
    d = getHorizontalDistanceInPixels(current, endVertex);
    if (d < minRealHorizontalDistance)   // if found smaller distance
      minRealHorizontalDistance = d;  // record it
  }
  
  // Return the distance as a number of tiles
  return minRealHorizontalDistance / getTileLength();
} // getEstimatedGraphDistanceInTiles()




void PathfindingGraph::printAStarTable() const
{
  // Table header
  std::cout << "\n--------------------------------------\n";
  std::cout << "index pv movementCost estimatedMovementCost\n";

  for (unsigned int i = 0; i < mVertices.size(); ++i)
  {
    auto & vertex = mVertices[i];
    std::string resolutionStatus =
      (vertex->resolutionStatus == PGVertex::ResolutionStatus::Resolved)
      ? "Resolved" : "Not Yet Resolved";
    std::cout << i << ' ' << vertex->previousVertexIndex << ' '
      << vertex->movementCost << ' ' << vertex->estimatedMovementCost << ' '
      << resolutionStatus << '\n';
  }

  std::cout << "\n--------------------------------------\n\n";
}





int PathfindingGraph::getHorizontalDistanceInPixels(const PGVertex * current,
  const PGVertex * goal)
{
  return abs(goal->getPosition().x - current->getPosition().x);
} // getHorizontalDistance()




int PathfindingGraph::getTileLength() const
{
  return mVertices.at(0)->getTileLength();
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

  // Reset priority queue
  mPossibleEdgeSelections = std::priority_queue<PossibleSelection,
    std::vector<PossibleSelection>, ComparePossibleAStarEdgeSelections>();

  // Make each designated start vertex a possible first selection.
  // Clear each start vertex's movement cost, since they're reached by default.
  for (auto& vertex : mSearchStartVertices)
  {
    vertex->resolutionStatus = PGVertex::ResolutionStatus::CouldResolve;
    vertex->movementCost = 0;
    vertex->estimatedMovementCost =
      getEstimatedGraphDistanceAsGraphCost(vertex);

    // Make this vertex selectable for resolution
    mPossibleEdgeSelections.push(
      PossibleSelection(PGVertex::NoPrevious, getIndex(vertex),
        vertex->movementCost,
        vertex->estimatedMovementCost));
  }
} // setUpAStarSearch()




void PathfindingGraph::clearVerticesSets()
{
  mSearchStartVertices.clear();
  mSearchEndVertices.clear();
} // clearVerticesSets()




bool PathfindingGraph::isGoalVertex(PGVertex * vertex) const
{
  for (auto& const g : mSearchEndVertices)
  {
    if (vertex == g) // if given vertex is one of the goal vertices
      return true;
  }

  return false; // found no match
}




PossibleSelection PathfindingGraph::getNextAStarEdge()
{
  assert(mPossibleEdgeSelections.size() > 0);

  // Keep checking vertices with the lowest estimated movement cost until
  // find data on a vertex that can be resolved
  auto selection = mPossibleEdgeSelections.top();
  mPossibleEdgeSelections.pop();

  // While failing to find an edge to a vertex that has NOT been resolved.
  while (mVertices.at(selection.vertexToResolveIndex)->resolutionStatus
    != PGVertex::ResolutionStatus::CouldResolve)
  {
    // If this assertion is false, then there's no more data regarding
    // more pathfinding, so the algorithm should've finished
    assert(mPossibleEdgeSelections.size() > 0);

    // Pick another edge.
    selection = mPossibleEdgeSelections.top();
    mPossibleEdgeSelections.pop();

    // We shouldn't encounter an untouched vertex, because otherwise,
    // it wouldn't have been in the edge selection heap in the first place!
    assert(mVertices.at(selection.vertexToResolveIndex)->resolutionStatus
      != PGVertex::ResolutionStatus::Untouched);
  }

  return selection;
} // getNextAStarEdge()




void PathfindingGraph::updateNeighborsAStar(const PGVertex * vertex)
{
  auto vertexIndex = getIndex(vertex);

  // for each neighbor of current vertex
  for (auto const& neighbor : vertex->adjacentVertices)
  {
    if (neighbor->resolutionStatus != PGVertex::ResolutionStatus::Resolved)
    {
      int edgeWeight = (vertex->isDiagonallyAdjacent(neighbor))
        ? DiagonalEdgeWeight : NondiagonalEdgeWeight;

      // set newMovementCost to current vertex's movementCost plus
      // distance to get to that neighbor
      int newMovementCost = vertex->movementCost + edgeWeight;

      // if found a new node
      if (neighbor->resolutionStatus == PGVertex::ResolutionStatus::Untouched)
      {
        // add neighbor to the set of vertices that could be resolved
        neighbor->resolutionStatus = PGVertex::ResolutionStatus::CouldResolve;
      }

      // if newMovementCost < neighbor's movementCost (i.e. if
      // found better path); for vertices that were just "touched",
      // this block is still run
      if (newMovementCost < neighbor->movementCost)
      {
        // update neighbor's pv
        neighbor->previousVertexIndex = vertexIndex;

        // update neighbor's movementCost to be newMovementCost
        neighbor->movementCost = newMovementCost;

        // Update neighbor's estimatedMovementCost to be
        // neighbor's movementCost + h(neighbor).
        neighbor->estimatedMovementCost =
          neighbor->movementCost
          + getEstimatedGraphDistanceAsGraphCost(neighbor);

        // Introduce the possibility of selecting this neighbor next.
        mPossibleEdgeSelections.push(
          PossibleSelection(vertexIndex, getIndex(neighbor),
            neighbor->movementCost,
            neighbor->estimatedMovementCost));
      } // if improved movement cost
    } // if neighbor not in closed set
  } // for each neighbor of the closed vertex
} // updateNeighborsAStar()




unsigned int PathfindingGraph::getIndex(const PGVertex * vertex) const
{
  // Can't use foreach loop because need index
  for (unsigned int i = 0; i < mVertices.size(); ++i)
  {
    if (mVertices[i].get() == vertex) // if found the vertex
      return i; // return the vertex's index
  }
}



int PathfindingGraph::getEstimatedGraphDistanceAsGraphCost(
  const PGVertex * current) const
{
  return NondiagonalEdgeWeight * getEstimatedGraphDistanceInTiles(current);
} // getEstimatedGraphDistanceAsGraphCost()
