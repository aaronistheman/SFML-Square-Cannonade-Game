#pragma once

#include <Tile/Tile.hpp>

#include <vector>
#include <queue>


/**
 * Vertex class with adjacency list(s).
 */
struct PathfindingGraphVertex
{
public: // non-data related; just for cleaner/better code

  typedef std::unique_ptr<PathfindingGraphVertex> Ptr;

  sf::Vector2i getPosition() const;
  sf::IntRect getRect() const;

  // Returns true if and only if the given vertex is diagonally adjacent
  // from "this" vertex.
  bool isDiagonallyAdjacent(const PathfindingGraphVertex* vertex) const;

  // for initializing vertex data for A* search
  static const int NoPrevious;
  static const int InfiniteMovementCost;

  // For A* pathfinding search
  enum class ResolutionStatus
  {
    CouldResolve, // This vertex is a neighbor of at least one resolved
                  // vertex, meaning it *could* be resolved next.
    Resolved,     // Also called "closed". The quickest path to this vertex
                  // has been found in the search.
    Untouched,    // This vertex hasn't been interacted with in the search.
  };

public: // data

  // set of references to neighbors
  std::vector<PathfindingGraphVertex*> adjacentVertices;

  // set of references to vertices reachable through non-diagonal edge
  std::vector<PathfindingGraphVertex*> adjacentNondiagonalVertices;

  // set of references to vertices reachable through diagonal edge
  std::vector<PathfindingGraphVertex*> adjacentDiagonalVertices;
  
  Tile* tile; // each vertex is associated with one tile


  // A* data
  int previousVertexIndex; // represents the vertex that comes before
                           // this one in the best path to this vertex
  int movementCost; // objective distance to get to this vertex from
                    // a start vertex
  int estimatedMovementCost; // estimated distance to get to this vertex
                             // from a start vertex
  ResolutionStatus resolutionStatus;
};
typedef PathfindingGraphVertex PGVertex;




// Represents an option to select an edge to "traverse" in the A*
// algorithm.
struct PossibleAStarEdgeSelection
{
  int   vertexToComeFromIndex;  // Is already resolved.
  int   vertexToResolveIndex;   // Index of the vertex that would be resolved.

  int   movementCost;           // Movement cost of reaching the vertex
                                // the vertex-to-resolve through the shortest
                                // path through the vertex-to-come-from.
                                // IS NOT the weight of the edge.

  int   estimatedMovementCost;  // The "estimated" (by A* algorithm's
                                // definition) variant of the movementCost.

  // To make life easier
  PossibleAStarEdgeSelection(int vtcf, int vtr, int emc);
};
typedef PossibleAStarEdgeSelection PossibleSelection;




// For use with an instance of std::priority_queue<PossibleSelection>
struct ComparePossibleAStarEdgeSelections
{
  // If returns true, rhs will be closer to the top of the
  // std::priority_queue than lhs will
  bool operator()(const PossibleSelection& lhs,
    const PossibleSelection& rhs)
  {
    return lhs.estimatedMovementCost > rhs.estimatedMovementCost;
  }
};




/**
 * Class that represents an immutable graph based on a tile map.
 * (Thus, it is assumed that no tile, such as a wall tile, can move.)
 */
class PathfindingGraph
{
public:
  explicit PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid);

  size_t getNumVertices() const;
  unsigned int getNumEdges() const;


  // Returns nullptr if fails to find vertex.
  // Is slow and meant to be used for edge creation (which happens once),
  // but has to be public to be testable
  PGVertex* getVertex(sf::Vector2i position); // locate tile by position



  // These are public for testing purposes, which hopefully doesn't couple
  // this class's implementation to its tests too severely
  size_t                          getNumSearchStartVertices() const;
  const std::vector<PGVertex*>&   getSearchStartVertices() const;
  size_t                          getNumSearchEndVertices() const;
  const std::vector<PGVertex*>&   getSearchEndVertices() const;



  // For setting start/end of pathfinding search based on entity's traits
  // (e.g. entity's position, entity's width). More specifically, the
  // tiles touched by the entity are set as the start or end tiles,
  // depending on which method is called.
  void    setSearchStart(sf::Vector2f entityCenterPosition,
                         int entityWidth, int entityHeight);
  void    setSearchEnd(sf::Vector2f entityCenterPosition,
                       int entityWidth, int entityHeight);

  // If width=height, can use these instead of the above
  void    setSearchStart(sf::Vector2f entityCenterPosition, int entityLength);
  void    setSearchEnd(sf::Vector2f entityCenterPosition, int entityLength);


  // Perform's the search part of A* algorithm.
  // Returns index of the path ending vertex (with which the path can
  // be generated) in mVertices.
  // REQUIRES that a valid path exist.
  unsigned int performAStarSearch();


  // Generates the path found by the A* algorithm.
  // Returns said path as a set of vertices involved
  // in the path, where the first element of the set corresponds to
  // the start of the path. (Note that this first element must be one
  // of the designated start vertices in the A* search.)
  // Each vertex is represented by its index
  // in the container of vertices.
  std::vector<unsigned int> * generatePath(int pathEndingVertexId);


  // For debugging
  // Prints A* data of each vertex
  void printAStarTable() const;


private:
  static const int NondiagonalEdgeWeight;
  static const int DiagonalEdgeWeight;

private:
  void createVertices(const std::vector<Tile::Ptr> &tileGrid);
  void createEdges(int tileLength);

  void createNondiagonalEdges(PGVertex::Ptr &vertex, int tileLength);
  void createDiagonalEdges(PGVertex::Ptr &vertex, int tileLength);


  // Based on parameters, sets the tiles on which the pathfinding
  // search would start/end (i.e. which tiles this entity is touching).
  // Set isSettingStart to false to set path ending vertices.
  // "width" and "height" refer to characteristics of the entity located
  // at parameter "centerPosition".
  void setSearchStartOrEnd(bool isSettingStart,
    sf::Vector2f centerPosition, int width, int height);


  void setUpAStarSearch();
  void cleanUpAStarSearch();


  // Returns true if given vertex could end the pathfinding algorithm
  bool isGoalVertex(PGVertex* vertex) const;


  // Returns an edge from the set of possible edge selections, such
  // that one end of the edge is resolved, and the other could be resolved,
  // and such that the vertex-to-resolve has the lowest estimated movement
  // cost among other selectable vertices-to-resolve.
  PossibleSelection getNextAStarEdge();


  // Updates the neighbors of the given vertex, so as to prepare to continue
  // the A* search.
  // The given vertex should be the one currently being resolved.
  void updateNeighborsAStar(const PGVertex* vertex);


  // This method is O(N) (where N is number of vertices). Which is bad!
  // Try not to use this method!
  // Returns the index of the given vertex in mVertices. Kills program
  // if fails to find index.
  unsigned int getIndex(const PGVertex* vertex) const;


private:

  ///////////////////////////////////////////
  //// General graph data
  ///////////////////////////////////////////

  std::vector<PGVertex::Ptr> mVertices;
  unsigned int mNumEdges;


  ///////////////////////////////////////////
  //// A* data
  ///////////////////////////////////////////

  std::vector<PGVertex*> mSearchStartVertices;
  std::vector<PGVertex*> mSearchEndVertices;      // evaluated in the search

  // Original idea was to use an std::priority_queue of PGVertex*
  // instances, but this opens the door for a "heap violation" exception
  // (which is used by the Visual Studio 2015 compiler but not by g++),
  // because the PGVertex pointers can be used to modify the heap's
  // contents from outside.
  std::priority_queue<PossibleSelection, std::vector<PossibleSelection>,
    ComparePossibleAStarEdgeSelections>
    mPossibleEdgeSelections;
};