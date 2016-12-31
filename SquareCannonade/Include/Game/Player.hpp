#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>

class Player : public Entity
{
public:
  Player();

  float getLength() const;
  sf::IntRect   getBoundingRect() const;

  // The parameter name was pretty hard to come up with, admittedly :-)
  void setIsMovingLeft(bool b);
  void setIsMovingRight(bool b);
  void setIsMovingUp(bool b);
  void setIsMovingDown(bool b);

  virtual void update(sf::Time dt);
  virtual void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const;

private:
  static const float PlayerLength;
  static const float PlayerSpeed;

  sf::RectangleShape mSprite;   // player is square

  bool mIsMovingLeft;
  bool mIsMovingRight;
  bool mIsMovingDown;
  bool mIsMovingUp;
};