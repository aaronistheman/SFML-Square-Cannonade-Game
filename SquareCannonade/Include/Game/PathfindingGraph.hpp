#pragma once

#include <Tile/Tile.hpp>

#include <vector>

struct PathfindingGraphVertex
{
  // set of references to reachable vertices
  // reference to associated tile
};
typedef PathfindingGraphVertex PGVertex;

class PathfindingGraph
{
public:
  explicit PathfindingGraph(const std::vector<Tile::Ptr> &tileGrid);

  int getNumVertices() const;
  int getNumEdges() const;
};