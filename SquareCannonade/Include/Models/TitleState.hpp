#pragma once

namespace sf
{
  class RenderWindow;
}

class TitleState // : public sf::Drawable
{
  sf::RenderWindow* mWindow;

public:
  TitleState(sf::RenderWindow &window);

  virtual void draw();
};