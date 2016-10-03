#include <States/GameState.hpp>
#include <Utility/Utility.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(sf::RenderWindow &window, const TextureHolder &textures)
  : State(window)
  , mWorld(window, textures)
{
}

void GameState::draw()
{
  mWorld.draw();
}

bool GameState::handleEvent(const sf::Event& event)
{
  return mWorld.handleEvent(event);
}

void GameState::handleRealTimeInput()
{
  mWorld.handleRealTimeInput();
}