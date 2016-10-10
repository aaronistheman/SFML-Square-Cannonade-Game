#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

class Hunter : public Entity
{
public:
  Hunter();

  virtual void update(sf::Time dt);
  virtual void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const;

  virtual void setWaypoint(const sf::Vector2f& waypoint);

private:
  static const float HunterSpeed;

  sf::RectangleShape mSprite;

  sf::Vector2f mWaypoint;
};