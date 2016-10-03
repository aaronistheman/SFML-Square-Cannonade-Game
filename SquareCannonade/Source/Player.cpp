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

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}