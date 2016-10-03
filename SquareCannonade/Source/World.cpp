#include <Game/World.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/Window/Event.hpp>

World::World(sf::RenderWindow &window, const TextureHolder &textures)
  : mWindow(window)
  , mPlayer(textures.get(Textures::Test))
  , mIsPaused(false)
{
  mPlayer.setPosition(sf::Vector2f(15, 15));
}

void World::draw()
{
  mWindow.draw(mPlayer);
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
    sf::Vector2f position = mPlayer.getPosition();
    float change = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      position.x -= change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      position.x += change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      position.y -= change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      position.y += change;
    mPlayer.setPosition(position);
  }

  return;
}