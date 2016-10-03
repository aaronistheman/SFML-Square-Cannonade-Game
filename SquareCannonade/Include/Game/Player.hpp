#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Player : public Entity
{
public:
  Player();

  virtual void update();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::RectangleShape mSprite;

  bool mIsMovingLeft;
  bool mIsMovingRight;
  bool mIsMovingDown;
  bool mIsMovingUp;
};