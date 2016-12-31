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

  /*
  void setCanMoveLeft(bool b);
  void setCanMoveRight(bool b);
  void setCanMoveDown(bool b);
  void setCanMoveUp(bool b);
  */

  void update(sf::Time dt);
  void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const;

  void addWallCollisionData(sf::IntRect wallRect);

private: // private methods

  // Removes all restrictions regarding the directions in which the player
  // can move.
  void    removeMovementRestrictions();

  void    resolveWallCollisions();
  void    movePlayer(sf::Time dt);

private:
  static const float PlayerLength;
  static const float PlayerSpeed;

  sf::RectangleShape mSprite;   // player is square

  bool mIsMovingLeft;
  bool mIsMovingRight;
  bool mIsMovingDown;
  bool mIsMovingUp;

  bool mCanMoveLeft;
  bool mCanMoveRight;
  bool mCanMoveDown;
  bool mCanMoveUp;

  // Contains data on unresolved collisions with walls.
  std::vector<sf::IntRect>   mWallCollisionData;
};