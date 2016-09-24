#include <SFML/Graphics.hpp>

#include <Game/Test.hpp>
#include <Game/Test2.hpp>
#include <Controllers/Controller.hpp>

#include <iostream>

void testPlayer()
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
      /*else if (event.type == sf::Event::KeyPressed)
      {
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
      }*/
    }

    sf::Vector2f position = player.getPosition();
    float change = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      position.x -= change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      position.x += change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      position.y -= change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      position.y += change;
    player.setPosition(position);

    window.clear();
    window.draw(player);
    window.display();
  }
}

int main()
{
  /*
  handleRealTimeInput(currentState);
  handleEvent(currentState);
  */

  Controller controller;
  controller.handleRealTimeInput();
  controller.handleEvent();

  int a;
  std::cin >> a;

  return 0;
}