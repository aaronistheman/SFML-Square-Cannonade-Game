#include <Application.hpp>
#include <States/GameState.hpp>
#include <States/TitleState.hpp>

Application::Application()
  : mWindow(sf::VideoMode(1200, 600), "Square Cannonade")
  , mTextures()
  , mFonts()
{
  mTextures.load(Textures::Test, "Media/junk.png");

  mFonts.load(Fonts::Main, "Media/Sansation.ttf");

  mState = new TitleState(mWindow, mFonts, mTextures);
}

void Application::run()
{
  while (mWindow.isOpen())
  {
    processInput();
    render();
  }
} // run()

void Application::processInput()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    bool keepState = mState->handleEvent(event);
    if (!keepState)
    {
      // Delete the TitleState,
      // then point the current state at a new GameState
      delete mState;
      mState = new GameState(mWindow, mTextures);
    }
    else
      mState->handleRealTimeInput();

    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
} // processInput()

void Application::render()
{
  mWindow.clear();
  mState->draw();
  mWindow.display();
} // render()