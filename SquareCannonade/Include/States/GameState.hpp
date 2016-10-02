#pragma once

#include <States/State.hpp>
#include <Utility/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>
namespace sf
{
  class RenderWindow;
}

class GameState : public State
{
  // sf::Text mDummyText;
  // sf::Font mDummyFont;
  sf::Sprite mPlayer;
  bool mIsPaused;
public:
  GameState(sf::RenderWindow &window, const TextureHolder &textures);

  virtual void draw();
  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();
};