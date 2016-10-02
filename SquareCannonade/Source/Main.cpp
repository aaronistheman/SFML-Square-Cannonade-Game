#include <Application.hpp>
#include <Game/Test.hpp>
#include <Game/Test2.hpp>

int main()
{
  Application app;
  app.run();
  /*
  sf::RenderWindow window(sf::VideoMode(1200, 600), "Square Cannonade");

  TextureHolder textures;
  textures.load(Textures::Test, "Media/junk.png");

  FontHolder fonts;
  fonts.load(Fonts::Main, "Media/Sansation.ttf");

  State* state = new TitleState(window, fonts, textures);
  */
  /*
  Controller controller;
  controller.handleRealTimeInput(titleState);
  controller.handleEvent(titleState);
  */
  /*
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
        state = new GameState(window, textures);
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
  */
  return 0;
}