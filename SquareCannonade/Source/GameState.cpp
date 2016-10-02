#include <States/GameState.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(sf::RenderWindow &window)
  : State(window)
  // , mDummyText()
  // , mDummyFont()
  , mPlayer(sf::Vector2f(15, 15))
  , mIsPaused(false)
{
  mPlayer.setFillColor(sf::Color::Blue);
  /*
  if (!mDummyFont.loadFromFile("Media/Sansation.ttf"))
    std::cerr << "Failed load font\n";

  mDummyText.setFont(mDummyFont);
  mDummyText.setString("Welcome to GameState");
  centerOrigin(mDummyText);
  mDummyText.setPosition(window.getView().getSize() / 2.f);
  */
}

void GameState::draw()
{
  // mWindow->draw(mDummyText);
  mWindow->draw(mPlayer);
}

bool GameState::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::P)
      mIsPaused = !mIsPaused;
  }

  return true;
}

void GameState::handleRealTimeInput()
{
  if (!mIsPaused)
  {
    sf::Vector2f position = mPlayer.getPosition();
    float change = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      position.x -= change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      position.x += change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      position.y -= change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      position.y += change;
    mPlayer.setPosition(position);
  }

  return;
}