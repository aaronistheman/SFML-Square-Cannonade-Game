#include <States/GameState.hpp>
#include <Utility/Utility.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(sf::RenderWindow &window, const TextureHolder &textures)
  : State(window)
  , mWorld(window, textures)
{
}

void GameState::draw()
{
  mWorld.draw();
}

void GameState::update()
{
  mWorld.update();
}

bool GameState::handleEvent(const sf::Event& event)
{
  return mWorld.handleEvent(event);
}

void GameState::handleRealTimeInput()
{
  mWorld.handleRealTimeInput();
}