#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
  Entity();

  // This draw method contains the boilerplate code that I didn't
  // want to put in the draw methods of each subclass of Entity. Thus,
  // subclasses should put draw logic in drawSprite() (making me wonder
  // if draw() shouldn't be virtual).
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  virtual void drawSprite(sf::RenderTarget& target, sf::RenderStates states)
    const = 0;
  virtual void update(sf::Time dt) = 0;
};