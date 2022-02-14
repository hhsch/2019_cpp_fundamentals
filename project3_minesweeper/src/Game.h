#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Tile.h"

// Metadata
#define HEIGHT 600
#define WIDTH 800
#define TILEHEIGHT 16
#define TILEWIDTH 25
#define MAXMINES 50

// Game modes
#define PLAYING -1
#define RESET_NORMAL 0
#define RESET_1 1
#define RESET_2 2
#define RESET_3 3

class Game {
public:
  Game();
  void Draw(sf::RenderWindow &window);
  void Left(double x, double y);
  void Right(double x, double y);

  Tile tiles[TILEHEIGHT * TILEWIDTH];

private:
  bool debug;
  bool win;
  bool loss;
  int mines;
  int flags;

  void SetTiles(Tile *tiles);
  void SetTiles(Tile *tiles, std::string filename);
};
