#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>

class Player : public Entity
{
public:
  Player();

  // The parameter name was pretty hard to come up with, admittedly :-)
  void setIsMovingLeft(bool b);
  void setIsMovingRight(bool b);
  void setIsMovingUp(bool b);
  void setIsMovingDown(bool b);

  virtual void update();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::RectangleShape mSprite;

  bool mIsMovingLeft;
  bool mIsMovingRight;
  bool mIsMovingDown;
  bool mIsMovingUp;
};