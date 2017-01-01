#include <Game/World.hpp>
#include <Utility/Utility.hpp>
#include <Tile/TileMapConstants.hpp>
#include <Tile/DefaultTile.hpp>
#include <Game/Wall.hpp>

#include <SFML/Window/Event.hpp>

#include <iostream>


const int World::WorldWidthInTiles = 40;
const int World::WorldHeightInTiles = 20;

const float World::BorderWidth = 10.f;

const sf::Time World::TimePerPathfindingUpdate = sf::seconds(5);


World::World(sf::RenderWindow &window)
  : mWindow(window)
  , mIsPaused(false)
  , mTextures()   // ignore the passed in texture holder
  , mBackgroundSprite()
  , mPlayer()
  , mCoin1()
  , mCoin2()
  , mEnemies()
  , mTileLength()
  , mTileGrid()
  , mWallTiles()
  , mGraph()
  , mTimeSinceLastPathfinding(TimePerPathfindingUpdate) // So pathfinding gets
                                                // updated on first frame.
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

  setUpEnemies();

  createJunkWallTiles();
  mGraph = PathfindingGraph(mTileGrid);
} // World()

void World::setUpEnemies()
{
  // For now, just create two junk enemies
  Hunter* enemy1 = new Hunter();
  enemy1->setPosition(sf::Vector2f(180, 320));
  mEnemies.push_back(std::unique_ptr<Hunter>(enemy1));
  Hunter* enemy2 = new Hunter();
  enemy2->setPosition(sf::Vector2f(40, 40));
  mEnemies.push_back(std::unique_ptr<Hunter>(enemy2));
}

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

  // Draw each enemy
  for (const auto& enemy : mEnemies)
    mWindow.draw(*enemy);
}

void World::update(sf::Time dt)
{
  handleCollisions();

  updateEntities(dt);
  // mBackgroundSprite.setPosition(mPlayer.getPosition());
}

void World::updateEnemiesPathfinding(bool resetPaths)
{
  if (resetPaths)
    mGraph.setSearchEnd(mPlayer.getPosition(), (int) mPlayer.getLength());

  // For each enemy, set the start point(s) on the graph and run
  // the pathfinding algorithm. Retrieve the path, and store that
  // path with the enemy.
  for (auto &enemy : mEnemies)
  {
    if (resetPaths)
    {
      // Generate a new path and give it to the enemy
      mGraph.setSearchStart(enemy->getPosition(), enemy->getLength());
      int pathEndingVertexId = mGraph.performAStarSearch();
      enemy->setPath(mGraph.generatePath(pathEndingVertexId));

      mGraph.clearSearchStartVertices();
    }

    // Aim enemy at its current waypoint
    auto nextVertexIndex = enemy->getNextPathIndex();
    auto waypointPosition =
      mGraph.getVertex(nextVertexIndex)->getCenterPosition();
    enemy->setWaypoint(waypointPosition);
  }

  if (resetPaths)
    mGraph.clearSearchEndVertices();
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


void World::addWallsToTileMap(std::string & tileMap, int numTilesPerRow,
  const std::vector<sf::IntRect> &wallData, int tileLength)
{
  for (const auto& wd : wallData)
  {    
    // Map the wall data to appropriate tile(s), editing the
    // tile map accordingly. Since the wall is rectangular,
    // we can traverse it as if it were a 2d array.
    for (int rowIndexOffset = 0; rowIndexOffset < wd.height;
      ++rowIndexOffset)
    {
      for (int colIndexOffset = 0; colIndexOffset < wd.width;
        ++colIndexOffset)
      {
        // Determine which part of the tile map to edit
        int effectiveRowIndex = wd.top + rowIndexOffset;
        int effectiveColIndex = wd.left + colIndexOffset;
        int effectiveIndexToEdit =
          (effectiveRowIndex * numTilesPerRow) + effectiveColIndex;

        // Edit the tile map
        tileMap.at(effectiveIndexToEdit) = 'w';
      } // for each col
    } // for each row
  } // for each wall data
} // addWallsToTileMap()


void World::loadTextures()
{
  mTextures.load(Textures::Background, "Media/background.jpg");
}

void World::createWalls(const std::vector<sf::IntRect> &wallData)
{
  // For each wall data, create a corresponding wall object
  for (const auto& wd : wallData)
  {
    mWalls.push_back(std::unique_ptr<Wall>(
      new Wall(wd.left * mTileLength,
        wd.top * mTileLength, wd.width * mTileLength,
        wd.height * mTileLength)));
  }
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
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "wwwwwwwwwww0wwwwwwww00000000000000000000";
  tileMap += "0000000000w0w000000w00000000000000000000";
  tileMap += "0000000000w0w000000w00000000000000000000";
  tileMap += "0000000000w0w000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000wwwwwwwww000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000w00000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  tileMap += "0000000000000000000000000000000000000000";
  */

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

  std::vector<sf::IntRect> wallData;
  wallData.push_back(sf::IntRect(5, 3, 2, 4));
  wallData.push_back(sf::IntRect(20, 2, 1, 16));
  wallData.push_back(sf::IntRect(18, 2, 1, 7));
  createWalls(wallData);

  World::addWallsToTileMap(tileMap, WorldWidthInTiles, wallData, mTileLength);
  World::createGrid(mTileGrid, area, mTileLength, tileMap, mWallTiles);
}

void World::updateEnemies(sf::Time dt)
{
  // Determine whether to reset enemies' paths
  mTimeSinceLastPathfinding += dt;
  bool shouldResetPaths = false;
  if (mTimeSinceLastPathfinding >= TimePerPathfindingUpdate)
  {
    mTimeSinceLastPathfinding -= TimePerPathfindingUpdate;
    shouldResetPaths = true;
  }

  updateEnemiesPathfinding(shouldResetPaths);

  // Update each enemy individually
  for (auto &enemy : mEnemies)
    enemy->update(dt);
}

void World::updateEntities(sf::Time dt)
{
  mPlayer.update(dt);
  updateEnemies(dt);
}

void World::handleCollisions()
{
  checkCollisionsWithWalls();
} // handleCollisions()

void World::checkCollisionsWithWalls()
{
  sf::IntRect intersectionRect;

  // For each wall, check if player collides with it, and if so,
  // store related data.
  for (const auto& wall : mWalls)
  {
    if (wall->entityCollidesWithWall(
      mPlayer.getBoundingRect(), intersectionRect))
      mPlayer.addWallIntersectionData(intersectionRect);
  }
}
