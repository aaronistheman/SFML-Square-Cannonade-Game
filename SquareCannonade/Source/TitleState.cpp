#include <States/TitleState.hpp>
#include <States/GameState.hpp>
#include <Utility/Utility.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(sf::RenderWindow &window, const FontHolder &fonts,
  const TextureHolder &textures)
  : State(window)
  , mInstruction1("", fonts.get(Fonts::Main))
  , mInstruction2("", fonts.get(Fonts::Main))
  , mInstruction3("", fonts.get(Fonts::Main))
{
  mInstruction1.setString("Collect coins and dodge obstacles with arrow keys.");
  centerOrigin(mInstruction1);
  mInstruction1.setPosition(window.getView().getSize() / 2.f);

  mInstruction2.setString("Pause with the P key.");
  centerOrigin(mInstruction2);
  mInstruction2.setPosition(window.getView().getSize() / 2.f
    + sf::Vector2f(0.f, 30.f));

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

void TitleState::update(sf::Time dt)
{

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