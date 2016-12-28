#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>



class Hunter : public Entity
{
public:
  Hunter();

  float        getLength() const;

  void         setPath(std::unique_ptr<std::vector<unsigned int>>& path);

  virtual void update(sf::Time dt);


  virtual void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const;

  unsigned int        getNextPathIndex() const;

  // Given waypoint should be a center position
  virtual void setWaypoint(const sf::Vector2f& waypoint);
  virtual void setWaypoint(const sf::Vector2i& waypoint);


private:

  void         updateMovement(sf::Time dt);
  void         updateCurrentPathIndex();


private:
  static const float HunterLength;
  static const float HunterSpeed;

  // How close (in one-dimension) the enemy must be to target point before
  // we say the enemy's "reached" the target. Is used so that the enemy
  // doesn't keep going back and forth over a target tile.
  static const float TargetTolerance;

private:
  sf::RectangleShape mSprite;

  sf::Vector2f mWaypoint;

  std::unique_ptr<std::vector<unsigned int>>    mCurrentPath;
  size_t                                        mCurrentPathIndex;
};