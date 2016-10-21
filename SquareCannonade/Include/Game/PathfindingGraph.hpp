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

  // set of references to reachable vertices

  // set of references to vertices reachable through non-diagonal edge
  // set of references to vertices reachable through diagonal edge
  
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

  // returns nullptr if fails to find vertex
  // PGVertex* getVertex(int rowIndex, int colIndex);

  // returns nullptr if fails to find vertex;
  // is slow and meant to be used for edge creation (which happens once),
  // but has to be public to be testable
  PGVertex* getVertex(sf::Vector2i position); // locate tile by position

private:
  void createVertices(const std::vector<Tile::Ptr> &tileGrid);
  void createEdges(int tileLength);

private:
  std::vector<PGVertex::Ptr> mVertices;
  int mNumEdges;
};