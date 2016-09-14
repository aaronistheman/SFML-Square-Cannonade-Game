#include <SFML/Graphics.hpp>

#include <Game/Test.hpp>
#include <Game/Test2.hpp>

int main()
{
  Test test;
  test.print();

  Test2 test2;
  test2.print();

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Blue);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}