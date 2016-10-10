#pragma once

#include <Utility/ResourceIdentifiers.hpp>
#include <Utility/ResourceHolder.hpp>
#include <Game/Player.hpp>
#include <Game/Coin.hpp>
#include <Game/Hunter.hpp>
#include <Game/Tile.hpp>
#include <Game/WallTile.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

class World
{
public:
  World(sf::RenderWindow &window, const TextureHolder &textures);

  virtual void draw();
  virtual void update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();

public: // Public static methods
  // @param area is the area in which tiles can be created
  static void createGrid(std::vector<Tile::Ptr> &tileGrid,
    const sf::IntRect &area, int tileLength);

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

  TextureHolder mTextures;

  sf::Sprite mBackgroundSprite;

  Player mPlayer;

  // These should eventually be placed in a container
  Coin mCoin1;
  Coin mCoin2;
  Hunter mEnemy1;

  std::vector<Tile::Ptr> mTileGrid;
  std::vector<WallTile::Ptr> mWallTiles;
};