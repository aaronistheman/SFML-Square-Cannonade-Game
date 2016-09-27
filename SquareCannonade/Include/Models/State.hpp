#pragma once

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
};