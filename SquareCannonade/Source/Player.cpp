#include <Game/Player.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Player::Player()
  : mSprite(sf::RectangleShape(sf::Vector2f(30, 30)))
{
  mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = false;

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

void Player::update()
{
  sf::Vector2f position = getPosition();
  float change = 1.f;
  if (mIsMovingLeft)
    position.x -= change;
  if (mIsMovingRight)
    position.x += change;
  if (mIsMovingUp)
    position.y -= change;
  if (mIsMovingDown)
    position.y += change;
  setPosition(position);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Take the positioning of the player object itself, so it can be
  // applied to the player's sprite
  states.transform = getTransform();

  target.draw(mSprite, states);
}