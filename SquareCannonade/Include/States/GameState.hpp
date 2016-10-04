#pragma once

#include <States/State.hpp>
#include <Utility/ResourceIdentifiers.hpp>
#include <Game/World.hpp>

#include <SFML/Graphics/Sprite.hpp>
namespace sf
{
  class RenderWindow;
}

class GameState : public State
{
public:
  GameState(sf::RenderWindow &window, const TextureHolder &textures);

  virtual void draw();
  virtual void update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();

private:
  World   mWorld;
};