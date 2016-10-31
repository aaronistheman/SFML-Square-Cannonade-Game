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

public: // data

  std::vector<PathfindingGraphVertex*> adjacentVertices;

  // set of references to vertices reachable through non-diagonal edge
  std::vector<PathfindingGraphVertex*> adjacentNondiagonalVertices;

  // set of references to vertices reachable through diagonal edge
  std::vector<PathfindingGraphVertex*> adjacentDiagonalVertices;
  
  Tile* tile; // each vertex is associated with one tile
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

  int getNumVertices() const;
  int getNumEdges() const;

  // Returns nullptr if fails to find vertex.
  // Is slow and meant to be used for edge creation (which happens once),
  // but has to be public to be testable
  PGVertex* getVertex(sf::Vector2i position); // locate tile by position

  // These are public for testing purposes
  int getNumSearchStartVertices() const;
  const std::vector<Tile*>& getSearchStartVertices() const;

  // Based on enemy's location, sets the tiles on which the pathfinding
  // search would start (i.e. which tiles this entity is touching).
  void setSearchStart(sf::Vector2f centerPosition, int width, int height);

  // Perform's the search part of A* algorithm.
  // Returns index of the path ending vertex (with which the path can
  // be generated).
  int performAStarSearch();

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

private:
  std::vector<PGVertex::Ptr> mVertices;
  int mNumEdges;

  // A* data
  std::vector<Tile*> mSearchStartVertices;
};