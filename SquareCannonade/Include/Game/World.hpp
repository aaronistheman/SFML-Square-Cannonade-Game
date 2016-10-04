#pragma once

#include <Utility/ResourceIdentifiers.hpp>
#include <Game/Player.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class World
{
public:
  World(sf::RenderWindow &window, const TextureHolder &textures);

  virtual void draw();
  virtual void update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();

private:
  sf::RenderWindow&   mWindow;
  Player mPlayer;
  bool mIsPaused;
};