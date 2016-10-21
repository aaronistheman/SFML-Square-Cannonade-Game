#pragma once

#include <Tile/Tile.hpp>

#include <vector>


/**
 * Vertex class with adjacency list(s).
 */
struct PathfindingGraphVertex
{
  typedef std::unique_ptr<PathfindingGraphVertex> Ptr;

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

private:
  void createVertices(const std::vector<Tile::Ptr> &tileGrid);
  void createEdges();

private:
  std::vector<PGVertex::Ptr> mVertices;
  int mNumEdges;
};