#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
  // Initialize window
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hunter's Minesweeper");
  window.setVerticalSyncEnabled(true); // Might make things look smoother

  // Mode that game will be played in
  int mode = PLAYING;

  // Init main game object
  Game game;

  // Load first screen
  game.Draw(window);

  // Main event loop
  while (window.isOpen()) {

    sf::Event event;

    while (window.waitEvent(event)) {
      // Event handler
      switch (event.type) {
      case sf::Event::Closed:
	window.close();
	break;

      case sf::Event::MouseButtonReleased:
	if (event.mouseButton.button == sf::Mouse::Left) {
	  game.Left(event.mouseButton.x, event.mouseButton.y);
	  game.Draw(window);
	}

	if (event.mouseButton.button == sf::Mouse::Right) {
	  game.Right(event.mouseButton.x, event.mouseButton.y);
	  game.Draw(window);
	}
	break;
	
      default:
	break;
      }
    }
    
  } // End of event loop

  return 0;
}
