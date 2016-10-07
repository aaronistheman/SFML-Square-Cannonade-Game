#include <Game/World.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/Window/Event.hpp>

World::World(sf::RenderWindow &window, const TextureHolder &textures)
  : mWindow(window)
  , mIsPaused(false)
  , mPlayer()
  , mCoin1()
  , mCoin2()
{
  mPlayer.setPosition(sf::Vector2f(15, 15));

  mCoin1.setPosition(sf::Vector2f(30, 30));
  mCoin2.setPosition(sf::Vector2f(85, 20));
}

void World::draw()
{
  mWindow.draw(mPlayer);
  mWindow.draw(mCoin1);
  mWindow.draw(mCoin2);
}

void World::update(sf::Time dt)
{
  mPlayer.update(dt);
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