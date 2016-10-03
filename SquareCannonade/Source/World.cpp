#include <Game/World.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/Window/Event.hpp>

World::World(sf::RenderWindow &window, const TextureHolder &textures)
  : mWindow(window)
  , mPlayer()
  , mIsPaused(false)
{
  mPlayer.setPosition(sf::Vector2f(15, 15));
}

void World::draw()
{
  mWindow.draw(mPlayer);
}

void World::update()
{
  mPlayer.update();
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