#pragma once

#include <Models/TitleState.hpp>

class Controller
{
public:
  void handleRealTimeInput(TitleState &titleState);
  void handleEvent(TitleState &titleState);
};