#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace sf
{
  class RenderWindow;
}

class TitleState
{
  sf::RenderWindow* mWindow;

  sf::Texture mBackgroundTexture;
  sf::Sprite mBackgroundSprite;
  sf::Text mText;

public:
  TitleState(sf::RenderWindow &window);

  virtual void draw();
};