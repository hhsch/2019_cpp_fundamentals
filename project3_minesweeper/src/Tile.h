#pragma once

struct Tile {
  Tile();
  void reveal();
  void countAdjacent();
  
  bool hidden; // If is hidden
  bool mine; // If is a mine
  bool flag; // For right-clicking
  int adjacent; // Number of adjacent mines
  Tile *neighbors[8]; // Array of (Tile *) 
};
