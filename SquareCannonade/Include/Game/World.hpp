#pragma once

#include <Utility/ResourceIdentifiers.hpp>
#include <Utility/ResourceHolder.hpp>
#include <Game/Player.hpp>
#include <Game/Coin.hpp>
#include <Game/Hunter.hpp>
#include <Tile/Tile.hpp>
#include <Tile/WallTile.hpp>

#include <Game/PathfindingGraph.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>



class World
{
public:
  World(sf::RenderWindow &window);

  void setUpEnemies();
  
  void setUpBackgroundTexture(const Player& player);

  // const std::vector<WallTile::Ptr>& getWallTiles() const;

  virtual void draw();
  virtual void update(sf::Time dt);

  // Set resetPaths to true to determine new paths for the enemies
  // (by running the pathfinding algorithm).
  virtual void updateEnemiesPathfinding(bool resetPaths);

  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();

public: // Public static methods
  /**
   * @param area is the area in which tiles can be created
   * @param tileMap is string of chars, where each char says the type
   * of a tile (e.g. the fourth char describes the fourth tile)
   */
  static void createGrid(std::vector<Tile::Ptr> &tileGrid,
    const sf::IntRect &area, int tileLength,
    const std::string &tileMap,
    std::vector<WallTile*> &wallTiles);


  /**
   * Throws exception if at least one of the following occur:
   * 1) At least one wall doesn't align with tile boundaries.
   * 2) At least one wall overlaps with another wall.
   */
  static void addWallsToTileMap(std::string &tileMap,
    const std::vector<sf::IntRect> &wallData, int tileLength);


private: // Private methods
  void loadTextures();

  // For testing
  void createJunkWallTiles();

  void updateEnemies(sf::Time dt);
  void updateEntities(sf::Time dt);

private: // Private static variables

  static const int WorldWidthInTiles;
  static const int WorldHeightInTiles;

  // Visible width of the holes/edges surrounding the play area
  static const float BorderWidth;


  static const sf::Time TimePerPathfindingUpdate;


private: // Private member variables
  sf::RenderWindow&   mWindow;
  bool mIsPaused;

  // This class's own texture holder. Not shared with an external class
  // (e.g. Application, GameState).
  TextureHolder mTextures;

  sf::Sprite mBackgroundSprite;

  Player mPlayer;

  Coin mCoin1;
  Coin mCoin2;

  std::vector<std::unique_ptr<Hunter>> mEnemies;

  int mTileLength;
  std::vector<Tile::Ptr> mTileGrid;
  std::vector<WallTile*> mWallTiles;
  PathfindingGraph mGraph;

  sf::Time    mTimeSinceLastPathfinding;
};