#pragma once

#include <SFML/Window/Event.hpp>

namespace sf {
  class RenderWindow;
}

class State
{
protected:
  sf::RenderWindow* mWindow; // isn't destroyed by State

public:
  State(sf::RenderWindow& window);

  virtual void draw() = 0;
  virtual void update(sf::Time dt) = 0;
  virtual bool handleEvent(const sf::Event& event) = 0;
  virtual void handleRealTimeInput() = 0;
};