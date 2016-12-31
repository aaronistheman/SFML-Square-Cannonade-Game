#include <Game/Player.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>



const float Player::PlayerLength = 30.f;
const float Player::PlayerSpeed = 100.f;

Player::Player()
  : mSprite(sf::RectangleShape(sf::Vector2f(PlayerLength, PlayerLength)))
  // the eight movement booleans are initialized in the constructor's body
  , mIntersectionsWithWalls()
{
  mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = false;
  mCanMoveLeft = mCanMoveRight = mCanMoveDown = mCanMoveUp = true;

  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Blue);
}

float Player::getLength() const
{
  assert(mSprite.getSize().x == mSprite.getSize().y);
  return mSprite.getSize().x;
}

sf::IntRect Player::getBoundingRect() const
{
  // Position is centered because centerOrigin() is called in constructor
  sf::Vector2f centeredPosition = getPosition();

  return sf::IntRect(centeredPosition.x - PlayerLength / 2,
    centeredPosition.y - PlayerLength / 2,
    PlayerLength,
    PlayerLength);
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

/*
void Player::setCanMoveLeft(bool b)
{
  mCanMoveLeft = b;
}

void Player::setCanMoveRight(bool b)
{
  mCanMoveRight = b;
}

void Player::setCanMoveDown(bool b)
{
  mCanMoveDown = b;
}

void Player::setCanMoveUp(bool b)
{
  mCanMoveUp = b;
}
*/

void Player::update(sf::Time dt)
{
  removeMovementRestrictions();
  resolveWallCollisions();

  movePlayer(dt);
}

void Player::drawSprite(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}

void Player::addWallIntersectionData(sf::IntRect intersectionRect)
{
  mIntersectionsWithWalls.push_back(intersectionRect);
}

void Player::removeMovementRestrictions()
{
  mCanMoveLeft = mCanMoveRight = mCanMoveDown = mCanMoveUp = true;
}

#include <iostream>
void Player::resolveWallCollisions()
{
  auto playerRect = getBoundingRect();

  // For each wall-collision-to-resolve, apply the correct restriction
  // on the player's movement.

  std::cout << mIntersectionsWithWalls.size() << '\n';
  mIntersectionsWithWalls.clear();
  return;
  for (const auto& wc : mIntersectionsWithWalls)
  {
    /**
     * The following code is based on code from my Tanks game from just
     * over two years ago.
     */

  }

  mIntersectionsWithWalls.clear();
}

void Player::movePlayer(sf::Time dt)
{
  sf::Vector2f movement;
  if (mIsMovingLeft && mCanMoveLeft)
    movement.x -= PlayerSpeed;
  if (mIsMovingRight && mCanMoveRight)
    movement.x += PlayerSpeed;
  if (mIsMovingUp && mCanMoveUp)
    movement.y -= PlayerSpeed;
  if (mIsMovingDown && mCanMoveDown)
    movement.y += PlayerSpeed;
  move(movement * dt.asSeconds());
}
