#include "Tile.h"

Tile::Tile() {
  hidden = true;
  flag = false;
  for (int i = 0; i < 8; ++i) {
    neighbors[i] = nullptr;
  }
}

void Tile::countAdjacent() {
  int count = 0;
  
  for (int i = 0; i < 8; ++i) {
        
    // Check for adjacent nodes that exist and are mines
    if (neighbors[i] == nullptr) { continue; }
      
    if (neighbors[i]->mine) {
      count += 1;
    }
      
  }

  adjacent = count;
}

void Tile::reveal() {
  // Reveal if not already revealed
  // NOTE: this function will never be called on a mine
  if (hidden) {
    hidden = false;
  } else {
    return;
  }

  flag = false;

  // Reveal adjacent if no mines nearby
  if (adjacent == 0) {
    for (int i = 0; i < 8; ++i) {
      if (neighbors[i] != nullptr) {
	neighbors[i]->reveal();
      }
    }
  }
  
}
