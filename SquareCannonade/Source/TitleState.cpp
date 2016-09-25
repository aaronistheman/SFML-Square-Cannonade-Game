#pragma once

#include <Models/TitleState.hpp>

#include <iostream>

TitleState::TitleState(sf::RenderWindow &window)
  : mWindow(&window)
{
}

void TitleState::draw()
{
  std::cout << "TitleState::draw()\n";
}