/**
 * See header file for credits, since I didn't implement
 * all of the below functions.
 */

#include <Utility/Utility.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>

void centerOrigin(sf::Text& text)
{
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::Sprite& sprite)
{
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::Shape& shape)
{
  sf::FloatRect bounds = shape.getLocalBounds();
  shape.setOrigin(std::floor(bounds.width / 2.f),
    std::floor(bounds.height / 2.f));
}