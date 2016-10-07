#include <Game/Coin.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

Coin::Coin()
  : mSprite(sf::CircleShape(15.f))
{
  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Yellow);
}

void Coin::update(sf::Time dt)
{
}

void Coin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Take the positioning of the coin object itself, so it can be
  // applied to the coin's sprite
  states.transform = getTransform();

  target.draw(mSprite, states);
}