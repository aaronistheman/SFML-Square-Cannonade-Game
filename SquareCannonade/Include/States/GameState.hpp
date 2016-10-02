#pragma once

#include <States/State.hpp>

// #include <SFML/Graphics/Text.hpp>
// #include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
namespace sf
{
  class RenderWindow;
}

class GameState : public State
{
  // sf::Text mDummyText;
  // sf::Font mDummyFont;
  // sf::RectangleShape mPlayer;
  sf::Texture mTexture;
  sf::Sprite mPlayer;
  bool mIsPaused;
public:
  GameState(sf::RenderWindow &window);

  virtual void draw();
  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();
};