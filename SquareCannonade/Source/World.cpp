#include <Game/World.hpp>
#include <Utility/Utility.hpp>
#include <Tile/TileMapConstants.hpp>
#include <Tile/DefaultTile.hpp>

#include <SFML/Window/Event.hpp>

#include <iostream>


const int World::WorldWidthInTiles = 40;
const int World::WorldHeightInTiles = 20;

const float World::BorderWidth = 10.f;


World::World(sf::RenderWindow &window)
  : mWindow(window)
  , mIsPaused(false)
  , mTextures()   // ignore the passed in texture holder
  , mBackgroundSprite()
  , mPlayer()
  , mCoin1()
  , mCoin2()
  , mEnemy1()
  , mTileLength()
  , mTileGrid()
  , mWallTiles()
  , mGraph()
{
  sf::Vector2u windowSize = mWindow.getSize();

  // Ensure window can be completely divided into *square* tiles
  assert(windowSize.x % WorldWidthInTiles == 0);
  assert(windowSize.y % WorldHeightInTiles == 0);
  assert(windowSize.x / WorldWidthInTiles == windowSize.y / WorldHeightInTiles);

  mTileLength = windowSize.x / WorldWidthInTiles;

  loadTextures();

  mPlayer.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
  setUpBackgroundTexture(mPlayer);

  mCoin1.setPosition(sf::Vector2f(30, 30));
  mCoin2.setPosition(sf::Vector2f(85, 20));

  mEnemy1.setPosition(sf::Vector2f(180, 320));

  createJunkWallTiles();
  mGraph = PathfindingGraph(mTileGrid);
} // World()

void World::setUpBackgroundTexture(const Player& player)
{
  sf::Vector2u windowSize = mWindow.getSize();

  // Set up background texture to repeat
  sf::Texture& backgroundTexture = mTextures.get(Textures::Background);
  backgroundTexture.setRepeated(true);
  mBackgroundSprite.setTexture(backgroundTexture);
  mBackgroundSprite.setTextureRect(
    sf::IntRect(0, 0, windowSize.x, windowSize.y));
  centerOrigin(mBackgroundSprite);
  mBackgroundSprite.setPosition(player.getPosition());
}

/*
const std::vector<WallTile::Ptr>& World::getWallTiles() const
{
  return mWallTiles;
}
*/

void World::draw()
{
  mWindow.draw(mBackgroundSprite);

  // Draw each wall (for some reason, I couldn't use a foreach loop)
  for (size_t i = 0; i < mWallTiles.size(); ++i)
  {
    mWindow.draw(*mWallTiles[i]);
  }
  
  mWindow.draw(mPlayer);
  mWindow.draw(mCoin1);
  mWindow.draw(mCoin2);
  mWindow.draw(mEnemy1);
}

void World::update(sf::Time dt)
{
  mPlayer.update(dt);

  mBackgroundSprite.setPosition(mPlayer.getPosition());

  mEnemy1.setWaypoint(mPlayer.getPosition());
  mEnemy1.update(dt);
}

bool World::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::P)
      mIsPaused = !mIsPaused;
  }

  return true;
}

void World::handleRealTimeInput()
{
  if (!mIsPaused)
  {
    mPlayer.setIsMovingUp(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    mPlayer.setIsMovingDown(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    mPlayer.setIsMovingLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    mPlayer.setIsMovingRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
  }

  return;
}

void World::createGrid(std::vector<Tile::Ptr> &tileGrid,
  const sf::IntRect &area, int tileLength,
  const std::string &tileMap,
  std::vector<WallTile*> &wallTiles)
{
  assert(tileGrid.size() == 0); // no existing tiles
  assert(tileLength > 0);

  // area has to be entirely divisible into equally-sized tiles
  assert(area.width % tileLength == 0);
  assert(area.height % tileLength == 0);

  int numTiles = area.width / tileLength * area.height / tileLength;
  int numTilesPerRow = area.width / tileLength;

  // tile map string must be correct size
  assert(tileMap.size() == numTiles);

  for (int y = 0, rowIndex = 0; y < area.height;
    y += tileLength, rowIndex += 1) // for each grid row
  {
    for (int x = 0, colIndex = 0; x < area.width;
      x += tileLength, colIndex += 1) // for each tile in row
    {
      char tileType = tileMap.at(rowIndex * numTilesPerRow + colIndex);

      // The casts are needed because tileType is of type char, rather
      // than of type TileType
      switch (tileType)
      {
      case (char) TileType::Default:
        tileGrid.push_back(Tile::Ptr(
          new DefaultTile(x, y, tileLength, tileLength)));
        break;

      case (char) TileType::Wall:
        tileGrid.push_back(WallTile::Ptr(
          new WallTile(x, y, tileLength, tileLength)));
        wallTiles.push_back((WallTile*) tileGrid.back().get());
        break;

      default:
        // Invalid tile type
        assert(false);
      }
    } 
  } // for each row of the grid
} // createGrid()

void World::loadTextures()
{
  mTextures.load(Textures::Background, "Media/background.jpg");
}

void World::createJunkWallTiles()
{
  // Poor quality code, since this is just for quick test
  auto area = sf::IntRect(0, 0, mWindow.getSize().x, mWindow.getSize().y);

  /*
  std::string tileMap = "";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";

  std::string tileMap = "";
  tileMap += "00000000000000000000w0000000000000000000";
  tileMap += "0000000000000000000w0w000000000000000000";
  tileMap += "000000000000000000w000w00000000000000000";
  tileMap += "00000000000000000w00000w0000000000000000";
  tileMap += "0000000000000000w0000000w000000000000000";
  tileMap += "000000000000000w000000000w00000000000000";
  tileMap += "00000000000000w00000000000w0000000000000";
  tileMap += "0000000000000w0000000000000w000000000000";
  tileMap += "000000000000w000000000000000w00000000000";
  tileMap += "00000000000w00000000000000000w0000000000";
  tileMap += "0000000000w0000000000000000000w000000000";
  tileMap += "000000000w000000000000000000000w00000000";
  tileMap += "00000000w00000000000000000000000w0000000";
  tileMap += "0000000w0000000000000000000000000w000000";
  tileMap += "0000000000000000000000000000000000w00000";
  tileMap += "00000000000000000000000000000000000w0000";
  tileMap += "000000000000000000000000000000000000w000";
  tileMap += "0000000000000000000000000000000000000w00";
  tileMap += "00000000000000000000000000000000000000w0";
  tileMap += "000000000000000000000000000000000000000w";
  */

  std::string tileMap = "";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";

  World::createGrid(mTileGrid, area, mTileLength, tileMap, mWallTiles);
}