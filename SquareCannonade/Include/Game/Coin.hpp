#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/CircleShape.hpp>

class Coin : public Entity
{
public:
  Coin();

  virtual void update(sf::Time dt);
  virtual void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const;

private:
  sf::CircleShape mSprite;
};