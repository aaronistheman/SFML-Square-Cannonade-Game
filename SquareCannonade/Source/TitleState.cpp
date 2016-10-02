#include <States/TitleState.hpp>
#include <States/GameState.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

TitleState::TitleState(sf::RenderWindow &window)
  : State(window)
  , mInstruction1()
  , mInstruction2()
  , mInstruction3()
{
  if (!mBackgroundTexture.loadFromFile("Media/junk.png"))
    std::cerr << "Uh-oh\n";
  mBackgroundSprite.setTexture(mBackgroundTexture);

  if (!mFont.loadFromFile("Media/Sansation.ttf"))
    std::cerr << "Failed load font\n";

  mInstruction1.setFont(mFont);
  mInstruction1.setString("Collect coins and dodge obstacles with arrow keys.");
  centerOrigin(mInstruction1);
  mInstruction1.setPosition(window.getView().getSize() / 2.f);

  mInstruction2.setFont(mFont);
  mInstruction2.setString("Pause with the P key.");
  centerOrigin(mInstruction2);
  mInstruction2.setPosition(window.getView().getSize() / 2.f
    + sf::Vector2f(0.f, 30.f));

  mInstruction3.setFont(mFont);
  mInstruction3.setString("Continue with Enter key.");
  centerOrigin(mInstruction3);
  mInstruction3.setPosition(window.getView().getSize() / 2.f
    + sf::Vector2f(0.f, 60.f));
}

void TitleState::draw()
{
  mWindow->draw(mInstruction1);
  mWindow->draw(mInstruction2);
  mWindow->draw(mInstruction3);
  // mWindow->draw(mBackgroundSprite);
}

bool TitleState::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Return)
    {
      return false;
    }
  }
}

void TitleState::handleRealTimeInput()
{
  return;
}