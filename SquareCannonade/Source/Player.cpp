#include <Game/Player.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Player::Player()
  : mSprite(sf::RectangleShape(sf::Vector2f(30, 30)))
{
  mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = false;

  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Blue);
}

void Player::setIsMovingLeft(bool b)
{
  mIsMovingLeft = b;
}

void Player::setIsMovingRight(bool b)
{
  mIsMovingRight = b;
}

void Player::setIsMovingUp(bool b)
{
  mIsMovingUp = b;
}

void Player::setIsMovingDown(bool b)
{
  mIsMovingDown = b;
}

void Player::update(sf::Time dt)
{
  sf::Vector2f movement;
  float change = 1.f;
  if (mIsMovingLeft)
    movement.x -= change;
  if (mIsMovingRight)
    movement.x += change;
  if (mIsMovingUp)
    movement.y -= change;
  if (mIsMovingDown)
    movement.y += change;
  move(movement);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Take the positioning of the player object itself, so it can be
  // applied to the player's sprite
  states.transform = getTransform();

  target.draw(mSprite, states);
}