#pragma once

#include <Utility/ResourceIdentifiers.hpp>
#include <Utility/ResourceHolder.hpp>
#include <Game/Player.hpp>
#include <Game/Coin.hpp>
#include <Game/Hunter.hpp>
#include <Tile/Tile.hpp>
#include <Tile/WallTile.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

class World
{
public:
  World(sf::RenderWindow &window);
  
  void setUpBackgroundTexture(const Player& player);

  // const std::vector<WallTile::Ptr>& getWallTiles() const;

  virtual void draw();
  virtual void update(sf::Time dt);
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

private:
  void loadTextures();

  // For testing
  void createJunkWallTiles();

private:
  static const int TileLength;

  // Visible width of the holes/edges surrounding the play area
  static const float BorderWidth;


private:
  sf::RenderWindow&   mWindow;
  bool mIsPaused;

  // This class's own texture holder. Not shared with an external class
  // (e.g. Application, GameState).
  TextureHolder mTextures;

  sf::Sprite mBackgroundSprite;

  Player mPlayer;

  // These should eventually be placed in a container
  Coin mCoin1;
  Coin mCoin2;
  Hunter mEnemy1;

  std::vector<Tile::Ptr> mTileGrid;
  std::vector<WallTile*> mWallTiles;
};