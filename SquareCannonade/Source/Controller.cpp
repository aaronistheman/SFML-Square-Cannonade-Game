#include <Controllers/Controller.hpp>

#include <iostream>

void Controller::handleRealTimeInput(TitleState &titleState)
{
  //std::cout << "Controller::handleRealTimeInput()\n";
  titleState.draw();
}

void Controller::handleEvent(TitleState &titleState)
{
  //std::cout << "Controller::handleEvent()\n";
}