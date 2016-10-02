#pragma once

#include <States/TitleState.hpp>

class Controller
{
public:
  void handleRealTimeInput(TitleState &titleState);
  void handleEvent(TitleState &titleState);
};