/**
 * See header file for credits, since I didn't implement
 * all of the below functions.
 */

#include <Utility/Utility.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

void centerOrigin(sf::Text& text)
{
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::RectangleShape& rectangleShape)
{
  sf::FloatRect bounds = rectangleShape.getLocalBounds();
  rectangleShape.setOrigin(std::floor(bounds.width / 2.f),
    std::floor(bounds.height / 2.f));
}