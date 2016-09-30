#include <Models/GameState.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(sf::RenderWindow &window)
  : State(window)
  , mDummyText()
  , mDummyFont()
{
  if (!mDummyFont.loadFromFile("Media/Sansation.ttf"))
    std::cerr << "Failed load font\n";

  mDummyText.setFont(mDummyFont);
  mDummyText.setString("Welcome to GameState");
  centerOrigin(mDummyText);
  mDummyText.setPosition(window.getView().getSize() / 2.f);
}

void GameState::draw()
{
  mWindow->draw(mDummyText);
}

bool GameState::handleEvent(const sf::Event& event)
{
  return true;
}