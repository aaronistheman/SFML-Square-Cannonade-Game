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
  createGrid();

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
} // World()

void World::createGrid()
{
  mTileGrid.push_back(Tile::Ptr(new Tile(30, 30, 30, 30)));
} // createGrid()

void World::draw()
{
  mWindow.draw(mBackgroundSprite);

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

void World::loadTextures()
{
  mTextures.load(Textures::Background, "Media/background.jpg");
}