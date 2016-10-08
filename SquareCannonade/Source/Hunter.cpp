#include <Game/Hunter.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Hunter::Hunter()
  : mSprite(sf::RectangleShape(sf::Vector2f(30.f, 30.f)))
{
  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Red);
}

void Hunter::update(sf::Time dt)
{
}

void Hunter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Take the positioning of the enemy object itself, so it can be
  // applied to its sprite
  states.transform = getTransform();

  target.draw(mSprite, states);
}