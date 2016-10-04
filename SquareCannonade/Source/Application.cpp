#include <Application.hpp>
#include <States/GameState.hpp>
#include <States/TitleState.hpp>

#include <string>


const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
  : mWindow(sf::VideoMode(1200, 600), "Square Cannonade", sf::Style::Close)
  , mTextures()
  , mFonts()
  , mStatisticsText()
  , mStatisticsUpdateTime()
  , mStatisticsNumFrames(0)
{
  mWindow.setKeyRepeatEnabled(false);

  mTextures.load(Textures::Test, "Media/junk.png");

  mFonts.load(Fonts::Main, "Media/Sansation.ttf");

  mState = new TitleState(mWindow, mFonts, mTextures);

  mStatisticsText.setFont(mFonts.get(Fonts::Main));
  mStatisticsText.setPosition(5.f, 5.f);
  mStatisticsText.setCharacterSize(10u);
}

void Application::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen())
  {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;

    while (timeSinceLastUpdate > TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;

      processInput();
      update(TimePerFrame);
    }

    updateStatistics(dt);
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
  mWindow.draw(mStatisticsText);
  mWindow.display();
} // render()

void Application::update(sf::Time dt)
{
  mState->update(dt);
}

void Application::updateStatistics(sf::Time dt)
{
  mStatisticsUpdateTime += dt;
  mStatisticsNumFrames += 1;
  if (mStatisticsUpdateTime >= sf::seconds(1.0f))
  {
    mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
} // updateStatistics()