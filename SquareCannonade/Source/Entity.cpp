#include <Game/Entity.hpp>

Entity::Entity()
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Take the positioning of this object itself, so it can be
  // applied to this object's sprite
  states.transform = getTransform();

  drawSprite(target, states);
}