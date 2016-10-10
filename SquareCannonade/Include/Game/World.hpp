#pragma once

#include <Utility/ResourceIdentifiers.hpp>
#include <Utility/ResourceHolder.hpp>
#include <Game/Player.hpp>
#include <Game/Coin.hpp>
#include <Game/Hunter.hpp>
#include <Game/Tile.hpp>

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

private:
  void loadTextures();
  void createGrid();

private:
  // Visible width of the holes/edges surrounding the play area
  static const float BorderWidth;

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
};