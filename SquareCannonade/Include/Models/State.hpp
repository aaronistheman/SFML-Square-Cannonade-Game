#pragma once

#include <SFML/Window/Event.hpp>

namespace sf {
  class RenderWindow;
}

class State
{
protected:
  sf::RenderWindow* mWindow;

public:
  State(sf::RenderWindow& window);

  virtual void draw() = 0;
  virtual bool handleEvent(const sf::Event& event) = 0;
};