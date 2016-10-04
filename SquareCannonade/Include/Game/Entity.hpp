#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
  Entity();

  virtual void update(sf::Time dt) = 0;
};