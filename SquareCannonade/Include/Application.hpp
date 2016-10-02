#pragma once

/**
 * Based on version written by: Artur Moreira, Henrik Vogelius Hansson, and
 *   Jan Haller
 */

#include <Controllers/Controller.hpp>
#include <States/TitleState.hpp>
#include <States/GameState.hpp>
#include <Utility/ResourceIdentifiers.hpp>
#include <Utility/ResourceHolder.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class Application : private sf::NonCopyable
{
  sf::RenderWindow mWindow;
  TextureHolder mTextures;
  FontHolder mFonts;
  State* mState;
public:
  Application();

  void run();
};