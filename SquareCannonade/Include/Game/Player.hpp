#pragma once

#include <Game/Entity.hpp>

class Player : public Entity
{
public:
  Player();

  virtual void update();

private:
  bool mIsMovingLeft;
  bool mIsMovingRight;
  bool mIsMovingDown;
  bool mIsMovingUp;
};