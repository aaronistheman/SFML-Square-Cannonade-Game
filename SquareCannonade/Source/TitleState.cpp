#pragma once

#include <Models/TitleState.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

TitleState::TitleState(sf::RenderWindow &window)
  : mWindow(&window)
  , mText()
{
  if (!mBackgroundTexture.loadFromFile("Media/junk.png"))
    std::cerr << "Uh-oh\n";
  mBackgroundSprite.setTexture(mBackgroundTexture);

  if (!mFont.loadFromFile("Media/Sansation.ttf"))
    std::cerr << "Failed load font\n";
  mText.setFont(mFont);
  mText.setString("Welcome");
  centerOrigin(mText);
  mText.setPosition(window.getView().getSize() / 2.f);
}

void TitleState::draw()
{
  mWindow->draw(mText);
  // mWindow->draw(mBackgroundSprite);
}