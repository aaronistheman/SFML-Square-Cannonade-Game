#pragma once

#include <Tile/Tile.hpp>

#include <vector>


/**
 * Vertex class with adjacency list(s).
 */
struct PathfindingGraphVertex
{
public: // non-data related; just for cleaner code

  typedef std::unique_ptr<PathfindingGraphVertex> Ptr;
  sf::Vector2i getPosition() const;
  sf::IntRect getRect() const;

  // for initializing vertex data for A* search
  static const int NoPrevious;
  static const int InfiniteMovementCost;

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
};
typedef PathfindingGraphVertex PGVertex;




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



  // These are public for testing purposes
  size_t getNumSearchStartVertices() const;
  const std::vector<PGVertex*>& getSearchStartVertices() const;
  size_t getNumSearchEndVertices() const;
  const std::vector<PGVertex*>& getSearchEndVertices() const;



  // For setting start/end of pathfinding search based on entity's traits
  // (e.g. entity's position, entity's width). More specifically, the
  // tiles touched by the entity are set as the start or end tiles,
  // depending on which method is called.
  void setSearchStart(sf::Vector2f entityCenterPosition,
    int entityWidth, int entityHeight);
  void setSearchEnd(sf::Vector2f entityCenterPosition,
    int entityWidth, int entityHeight);
  // If width=height, can use these instead of the above
  void setSearchStart(sf::Vector2f entityCenterPosition, int entityLength);
  void setSearchEnd(sf::Vector2f entityCenterPosition, int entityLength);


  // Perform's the search part of A* algorithm.
  // Returns index of the path ending vertex (with which the path can
  // be generated) in mVertices.
  unsigned int performAStarSearch();


  // Generates the path found by the A* algorithm.
  // Returns said path as an array of pointers to the vertices involved
  // in the path, where index 0 corresponds to the start of the path.
  PGVertex** generatePath(int pathEndingVertexId);

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

private:
  std::vector<PGVertex::Ptr> mVertices;
  unsigned int mNumEdges;

  // A* data
  std::vector<PGVertex*> mSearchStartVertices;
  std::vector<PGVertex*> mSearchEndVertices;
  std::vector<PGVertex*> mResolvedVertices; // the vertices that have been
                                            // evaluated in the search
  std::vector<PGVertex*> mUnresolvedVertices; // the vertices that haven't
                                              // been resolved
};