#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

class Hunter : public Entity
{
public:
  Hunter();

  float getLength() const;

  virtual void update(sf::Time dt);
  virtual void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const;

  // Given waypoint should be a center position
  virtual void setWaypoint(const sf::Vector2f& waypoint);
  virtual void setWaypoint(const sf::Vector2i& waypoint);

private:
  static const float HunterLength;
  static const float HunterSpeed;

private:
  sf::RectangleShape mSprite;

  sf::Vector2f mWaypoint;
};