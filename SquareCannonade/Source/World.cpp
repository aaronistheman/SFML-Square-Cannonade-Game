#include <Game/World.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Window/Event.hpp>

const int World::TileLength = 30;
const float World::BorderWidth = 10.f;

World::World(sf::RenderWindow &window, const TextureHolder &textures)
  : mWindow(window)
  , mIsPaused(false)
  , mBackgroundSprite()
  , mPlayer()
  , mCoin1()
  , mCoin2()
  , mTileGrid()
{
  sf::Vector2u windowSize = mWindow.getSize();

  // Ensure window can be completely divided into equally-sized tiles
  assert(windowSize.x % TileLength == 0);
  assert(windowSize.y % TileLength == 0);

  loadTextures();

  mPlayer.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));

  // Set up background texture to repeat
  sf::Texture& backgroundTexture = mTextures.get(Textures::Background);
  backgroundTexture.setRepeated(true);
  mBackgroundSprite.setTexture(backgroundTexture);
  mBackgroundSprite.setTextureRect(
    sf::IntRect(0, 0, windowSize.x, windowSize.y));
  centerOrigin(mBackgroundSprite);
  mBackgroundSprite.setPosition(mPlayer.getPosition());

  mCoin1.setPosition(sf::Vector2f(30, 30));
  mCoin2.setPosition(sf::Vector2f(85, 20));

  mEnemy1.setPosition(sf::Vector2f(180, 320));

  createJunkWallTiles();
} // World()

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
  const sf::IntRect &area, int tileLength)
{
  assert(tileGrid.size() == 0); // no existing tiles
  assert(tileLength > 0);

  // area has to be entirely divisible into equally-sized tiles
  assert(area.width % tileLength == 0);
  assert(area.height % tileLength == 0);

  for (int y = 0; y < area.height; y += tileLength) // for each grid row
  {
    for (int x = 0; x < area.width; x += tileLength) // for each tile in row
    {
      tileGrid.push_back(Tile::Ptr(
        new Tile(x, y, tileLength, tileLength)));
    } 
  } // for each row of the grid
} // createGrid()

void World::loadTextures()
{
  mTextures.load(Textures::Background, "Media/background.jpg");
}

void World::createJunkWallTiles()
{
  mWallTiles.push_back(WallTile::Ptr(new WallTile(60, 0, 30, 30)));
}