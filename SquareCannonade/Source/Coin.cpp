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

void Coin::drawSprite(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}