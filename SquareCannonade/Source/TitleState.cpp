#pragma once

#include <Models/TitleState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

TitleState::TitleState(sf::RenderWindow &window)
  : mWindow(&window)
  , mText()
{
  if (!mBackgroundTexture.loadFromFile("junk.png"))
    std::cerr << "Uh-oh\n";
  mBackgroundSprite.setTexture(mBackgroundTexture);

  mText.setString("Welcome");
}

void TitleState::draw()
{
  // mWindow->draw(mText);
  mWindow->draw(mBackgroundSprite);
}