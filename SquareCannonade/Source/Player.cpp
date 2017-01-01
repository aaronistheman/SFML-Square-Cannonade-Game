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

void Player::resolveWallCollisions()
{
  auto playerRect = getBoundingRect();

  // For each wall-collision-to-resolve, apply the correct restriction
  // on the player's movement.
  for (const auto& intersection : mIntersectionsWithWalls)
  {
    /**
     * The following code is based on code from my Tanks game from just
     * over two years ago.
     */

    // If all of the following hold:
    // 1) player's bottom is south of intersection's top
    // 2) player's top is north of intersection's bottom
    // 3) intersection rectangle is taller than wide
    if ((playerRect.top + playerRect.height) > intersection.top
      && playerRect.top < (intersection.top + intersection.height)
      && intersection.height > intersection.width)
    {
      // if the player's left side "dictates" the intersection
      if (playerRect.left == intersection.left)
        mCanMoveLeft = false;

      // if the player's right side "dictates" the intersection
      if ((playerRect.left + playerRect.width)
        == (intersection.left + intersection.width))
        mCanMoveRight = false;
    }

    // If all of the following hold:
    // 1) player's right is to right of intersection's left
    // 2) player's left is to left of intersection's right
    // 3) intersection rectangle is wider than tall
    if ((playerRect.left + playerRect.width) > intersection.left
      && playerRect.left < (intersection.left + intersection.width)
      && intersection.width > intersection.height)
    {
      // if the player's top side "dictates" the intersection
      if (playerRect.top == intersection.top)
        mCanMoveUp = false;

      // if the player's bottom side "dictates" the intersection
      if ((playerRect.top + playerRect.height)
        == (intersection.top + intersection.height))
        mCanMoveDown = false;
    }
  } // for each intersection

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
