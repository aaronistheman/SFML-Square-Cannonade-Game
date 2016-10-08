#pragma once

#include <Game/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

class Hunter : public Entity
{
public:
  Hunter();

  virtual void update(sf::Time dt);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::RectangleShape mSprite;
};