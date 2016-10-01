#include <SFML/Graphics.hpp>

#include <Game/Test.hpp>
#include <Game/Test2.hpp>
#include <Controllers/Controller.hpp>
#include <Models/TitleState.hpp>
#include <Models/GameState.hpp>

int main()
{
  /*
  handleRealTimeInput(currentState);
  handleEvent(currentState);
  */

  sf::RenderWindow window(sf::VideoMode(1200, 600), "Square Cannonade");

  State* state = new TitleState(window);
  // delete state;
  // state = new GameState(window);
  // TitleState titleState(window);

  /*
  Controller controller;
  controller.handleRealTimeInput(titleState);
  controller.handleEvent(titleState);
  */

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      bool keepState = state->handleEvent(event);
      if (!keepState)
      {
        // Delete the TitleState,
        // then point the current state at a new GameState
        delete state;
        state = new GameState(window);
      }
      else
        state->handleRealTimeInput();

      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    state->draw();
    window.display();
  }

  return 0;
}