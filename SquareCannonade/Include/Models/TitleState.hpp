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

  sf::Font mFont;

  // Instructional texts
  sf::Text mInstruction1;
  sf::Text mInstruction2;
  sf::Text mInstruction3;
public:
  TitleState(sf::RenderWindow &window);

  virtual void draw();
};