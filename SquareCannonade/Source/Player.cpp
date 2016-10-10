#include <Game/Player.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

const float Player::PlayerSpeed = 100.f;

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
  if (mIsMovingLeft)
    movement.x -= PlayerSpeed;
  if (mIsMovingRight)
    movement.x += PlayerSpeed;
  if (mIsMovingUp)
    movement.y -= PlayerSpeed;
  if (mIsMovingDown)
    movement.y += PlayerSpeed;
  move(movement * dt.asSeconds());
}

void Player::drawSprite(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}