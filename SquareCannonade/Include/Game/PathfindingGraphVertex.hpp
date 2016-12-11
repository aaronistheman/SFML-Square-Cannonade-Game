#pragma once

#include <Tile/Tile.hpp>

#include <vector>
#include <memory>



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
  int previousVertexIndex;   // represents the vertex that comes before
                             // this one in the best path to this vertex
  int movementCost;          // objective distance to get to this vertex from
                             // a start vertex
  int estimatedMovementCost; // estimated distance to get to this vertex
                             // from a start vertex
  ResolutionStatus resolutionStatus;
};
typedef PathfindingGraphVertex PGVertex;