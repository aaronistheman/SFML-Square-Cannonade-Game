#include <Game/Hunter.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

const float Hunter::HunterSpeed = 100.f;

Hunter::Hunter()
  : mSprite(sf::RectangleShape(sf::Vector2f(30.f, 30.f)))
  , mWaypoint()
{
  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Red);
}

void Hunter::update(sf::Time dt)
{
  sf::Vector2f movement;
  sf::Vector2f current = getPosition();

  if (current.x < mWaypoint.x) // if goal is to the right
    movement.x += HunterSpeed;
  else if (current.x > mWaypoint.x) // if goal is to the left
    movement.x -= HunterSpeed;

  if (current.y < mWaypoint.y) // if goal is downward
    movement.y += HunterSpeed;
  else if (current.y > mWaypoint.y) // if goal is upward
    movement.y -= HunterSpeed;

  move(movement * dt.asSeconds());
}

void Hunter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Take the positioning of the enemy object itself, so it can be
  // applied to its sprite
  states.transform = getTransform();

  target.draw(mSprite, states);
}

void Hunter::setWaypoint(const sf::Vector2f& waypoint)
{
  mWaypoint = waypoint;
}