#pragma once

#include <Models/State.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace sf
{
  class RenderWindow;
}

class GameState : public State
{
  sf::Text mDummyText;
  sf::Font mDummyFont;
public:
  GameState(sf::RenderWindow &window);

  virtual void draw();
  virtual void handleEvent(const sf::Event& event);
};