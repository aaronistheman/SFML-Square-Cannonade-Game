#pragma once

#include <Tile/Tile.hpp>

#include <vector>



struct PathfindingGraphVertex
{
  typedef std::unique_ptr<PathfindingGraphVertex> Ptr;

  // set of references to reachable vertices

  // set of references to vertices reachable with edge weight 10
  // set of references to vertices reachable with edge weight 14
  
  Tile* tile; // each vertex is associated with one tile
};
typedef PathfindingGraphVertex PGVertex;



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