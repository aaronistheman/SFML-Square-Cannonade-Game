#pragma once

/**
 * Based on version written by: Artur Moreira, Henrik Vogelius Hansson, and
 *   Jan Haller
 */

#include <States/TitleState.hpp>
#include <States/GameState.hpp>
#include <Utility/ResourceIdentifiers.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application : private sf::NonCopyable
{
public:
  Application();

  void run();

private:
  void processInput();
  void render();
  void update();

  void  updateStatistics(sf::Time dt);

private:
  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow;
  TextureHolder mTextures;
  FontHolder mFonts;
  State* mState;

  sf::Text				mStatisticsText;
  sf::Time				mStatisticsUpdateTime;
  std::size_t				mStatisticsNumFrames;
};