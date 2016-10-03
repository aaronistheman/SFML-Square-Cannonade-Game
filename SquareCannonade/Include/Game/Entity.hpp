#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
  Entity();

  virtual void update() = 0;
};