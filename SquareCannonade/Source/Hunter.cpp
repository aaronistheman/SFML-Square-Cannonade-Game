#include <Game/Hunter.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>


const float Hunter::HunterLength = 30.f;
const float Hunter::HunterSpeed = 100.f;

Hunter::Hunter()
  : mSprite(sf::RectangleShape(sf::Vector2f(HunterLength, HunterLength)))
  , mWaypoint()
  , mCurrentPath(nullptr)
  , mCurrentPathIndex(0)
{
  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Red);
}

float Hunter::getLength() const
{
  assert(mSprite.getSize().x == mSprite.getSize().y);
  return mSprite.getSize().x;
}

void Hunter::setPath(std::unique_ptr<std::vector<unsigned int>>& path)
{
  mCurrentPath = std::move(path);
  mCurrentPathIndex = 1;
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

void Hunter::drawSprite(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}

unsigned int Hunter::getNextPathIndex() const
{
  return mCurrentPath->at(mCurrentPathIndex);
}

void Hunter::setWaypoint(const sf::Vector2f& waypoint)
{
  mWaypoint = waypoint;
}

void Hunter::setWaypoint(const sf::Vector2i & waypoint)
{
  setWaypoint(sf::Vector2f(waypoint.x, waypoint.y));
}

