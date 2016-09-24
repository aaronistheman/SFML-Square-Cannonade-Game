#include <SFML/Graphics.hpp>

#include <Game/Test.hpp>
#include <Game/Test2.hpp>

int main()
{
  /*Test test;
  test.print();

  Test2 test2;
  test2.print();*/

  sf::RenderWindow window(sf::VideoMode(1200, 600), "Square Cannonade");

  sf::RectangleShape player(sf::Vector2f(15, 15));
  player.setFillColor(sf::Color::Blue);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::KeyPressed)
      {
        sf::Vector2f position = player.getPosition();
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
          position.x -= 1.f;
          break;
        case sf::Keyboard::Right:
          position.x += 1.f;
          break;
        case sf::Keyboard::Up:
          position.y -= 1.f;
          break;
        case sf::Keyboard::Down:
          position.y += 1.f;
          break;
        }
        player.setPosition(position);
      }
    }

    window.clear();
    window.draw(player);
    window.display();
  }

  return 0;
}