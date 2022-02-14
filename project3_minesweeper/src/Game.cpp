#include <SFML/Graphics.hpp>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <string>
#include <fstream>
#include "Game.h"

Game::Game() {
  win = false;
  loss = false;
  debug = false;
  
  SetTiles(tiles);
}

void Game::SetTiles(Tile *tiles) {
  // Reset tiles
  for (int i = 0; i < TILEHEIGHT; ++i) {
    for (int j = 0; j < TILEWIDTH; ++j) {
      
      tiles[i*TILEWIDTH + j].hidden = true;
      tiles[i*TILEWIDTH + j].flag = false;
      tiles[i*TILEWIDTH + j].mine = false;
      
    }
  }
  
  // Add mines to tiles by choosing random tile and placing without repetition
  srand(time(NULL));

  mines = MAXMINES;
  flags = 0;
  for (int i = 0; i < MAXMINES; ++i) {
    int y = rand() % TILEHEIGHT;
    int x = rand() % TILEWIDTH;

    // If mine already there, subtract one so not counted as placing a mine
    // This works okay as long as there are not too many mines
    if (tiles[y*TILEWIDTH + x].mine) {
      --i;
    } else {
      tiles[y*TILEWIDTH + x].mine = true;
    }
  }

  // Connect tiles
  for (int i = 0; i < TILEHEIGHT; ++i) {
    for (int j = 0; j < TILEWIDTH; ++j) {

      // Check by case if neighbor is present
      // First row
      if (i != 0) {
	if (j != 0) { tiles[i*TILEWIDTH + j].neighbors[0] = &tiles[(i-1)*TILEWIDTH + (j-1)]; }
	tiles[i*TILEWIDTH + j].neighbors[1] = &tiles[(i-1)*TILEWIDTH + j];
	if (j != TILEWIDTH - 1) { tiles[i*TILEWIDTH + j].neighbors[2] = &tiles[(i-1)*TILEWIDTH + (j+1)]; }
      }

      // Second row
      if (j != 0) { tiles[i*TILEWIDTH + j].neighbors[3] = &tiles[i*TILEWIDTH + (j-1)]; }
      if (j != TILEWIDTH - 1) { tiles[i*TILEWIDTH + j].neighbors[4] = &tiles[i*TILEWIDTH + (j+1)]; }

      // Third row
      if (i != TILEHEIGHT - 1) {
	if (j != 0) { tiles[i*TILEWIDTH + j].neighbors[5] = &tiles[(i+1)*TILEWIDTH + (j-1)]; }
	tiles[i*TILEWIDTH + j].neighbors[6] = &tiles[(i+1)*TILEWIDTH + j];
	if (j != TILEWIDTH - 1) { tiles[i*TILEWIDTH + j].neighbors[7] = &tiles[(i+1)*TILEWIDTH + (j+1)]; }
      }

      // Count how many mines are near
      tiles[i*TILEWIDTH + j].countAdjacent();
    }
  }

}

void Game::SetTiles(Tile *tiles, std::string filename) {
  // Reset tiles
  for (int i = 0; i < TILEHEIGHT; ++i) {
    for (int j = 0; j < TILEWIDTH; ++j) {
      
      tiles[i*TILEWIDTH + j].hidden = true;
      tiles[i*TILEWIDTH + j].flag = false;
      tiles[i*TILEWIDTH + j].mine = false;
      
    }
  }
  
  // Mines placed according to file
  mines = 0;
  flags = 0;

  std::ifstream file(filename);

  for (int i = 0; i < TILEHEIGHT*TILEWIDTH; ++i) {
    char ismine;
    file >> ismine;
    
    if (ismine == '1') {
      tiles[i].mine = true;
      ++mines;
    }
    
  }
  
  // Connect tiles
  for (int i = 0; i < TILEHEIGHT; ++i) {
    for (int j = 0; j < TILEWIDTH; ++j) {

      // Check by case if neighbor is present
      // First row
      if (i != 0) {
	if (j != 0) { tiles[i*TILEWIDTH + j].neighbors[0] = &tiles[(i-1)*TILEWIDTH + (j-1)]; }
	tiles[i*TILEWIDTH + j].neighbors[1] = &tiles[(i-1)*TILEWIDTH + j];
	if (j != TILEWIDTH - 1) { tiles[i*TILEWIDTH + j].neighbors[2] = &tiles[(i-1)*TILEWIDTH + (j+1)]; }
      }

      // Second row
      if (j != 0) { tiles[i*TILEWIDTH + j].neighbors[3] = &tiles[i*TILEWIDTH + (j-1)]; }
      if (j != TILEWIDTH - 1) { tiles[i*TILEWIDTH + j].neighbors[4] = &tiles[i*TILEWIDTH + (j+1)]; }

      // Third row
      if (i != TILEHEIGHT - 1) {
	if (j != 0) { tiles[i*TILEWIDTH + j].neighbors[5] = &tiles[(i+1)*TILEWIDTH + (j-1)]; }
	tiles[i*TILEWIDTH + j].neighbors[6] = &tiles[(i+1)*TILEWIDTH + j];
	if (j != TILEWIDTH - 1) { tiles[i*TILEWIDTH + j].neighbors[7] = &tiles[(i+1)*TILEWIDTH + (j+1)]; }
      }

      // Count how many mines are near
      tiles[i*TILEWIDTH + j].countAdjacent();
    }
  }

}

void Game::Draw(sf::RenderWindow &window) {
  window.clear();

  /*** Draw tiles ***/
  // Prepare textures
  sf::Texture tileHiddenTex;
  tileHiddenTex.loadFromFile("images/tile_hidden.png");
  sf::Sprite tileHidden;
  tileHidden.setTexture( tileHiddenTex );

  sf::Texture tileRevealedTex;
  tileRevealedTex.loadFromFile("images/tile_revealed.png");
  sf::Sprite tileRevealed;
  tileRevealed.setTexture( tileRevealedTex );

  sf::Texture mineTex;
  mineTex.loadFromFile("images/mine.png");
  sf::Sprite mine;
  mine.setTexture( mineTex );

  sf::Texture flagTex;
  flagTex.loadFromFile("images/flag.png");
  sf::Sprite flag;
  flag.setTexture( flagTex );

  sf::Texture oneTex;
  oneTex.loadFromFile("images/number_1.png");
  sf::Sprite one;
  one.setTexture( oneTex );

  sf::Texture twoTex;
  twoTex.loadFromFile("images/number_2.png");
  sf::Sprite two;
  two.setTexture( twoTex );

  sf::Texture threeTex;
  threeTex.loadFromFile("images/number_3.png");
  sf::Sprite three;
  three.setTexture( threeTex );

  sf::Texture fourTex;
  fourTex.loadFromFile("images/number_4.png");
  sf::Sprite four;
  four.setTexture( fourTex );

  sf::Texture fiveTex;
  fiveTex.loadFromFile("images/number_5.png");
  sf::Sprite five;
  five.setTexture( fiveTex );

  sf::Texture sixTex;
  sixTex.loadFromFile("images/number_6.png");
  sf::Sprite six;
  six.setTexture( sixTex );

  sf::Texture sevenTex;
  sevenTex.loadFromFile("images/number_7.png");
  sf::Sprite seven;
  seven.setTexture( sevenTex );

  sf::Texture eightTex;
  eightTex.loadFromFile("images/number_8.png");
  sf::Sprite eight;
  eight.setTexture( eightTex );

  // Set up tiles
  for (int i = 0; i < TILEHEIGHT; ++i) {
    for (int j = 0; j < TILEWIDTH; ++j) {

      // Tile revealed or not
      if (tiles[i*TILEWIDTH + j].hidden) {

	tileHidden.setPosition( sf::Vector2f(32*j, 32*i) );
	window.draw( tileHidden );

	// Display flag
	if (tiles[i*TILEWIDTH + j].flag) {
	  flag.setPosition( sf::Vector2f(32*j, 32*i) );
	  window.draw( flag );
	}

      } else {

	tileRevealed.setPosition( sf::Vector2f(32*j, 32*i) );
	window.draw( tileRevealed );

	// Revealed tile number
	if ( !(tiles[i*TILEWIDTH + j].adjacent == 0) ) {
	  sf::Sprite number;
	  switch (tiles[i*TILEWIDTH + j].adjacent) {
	  case 1: number = one; break;
	  case 2: number = two; break;
	  case 3: number = three; break;
	  case 4: number = four; break;
	  case 5: number = five; break;
	  case 6: number = six; break;
	  case 7: number = seven; break;
	  case 8: number = eight; break;
	  }

	  number.setPosition( sf::Vector2f(32*j, 32*i) );
	  window.draw( number );
	}

      }

      // Debug options
      if (debug) {
	// Mines
	if (tiles[i*TILEWIDTH + j].mine) {
	  mine.setPosition( sf::Vector2f(32*j, 32*i) );
	  window.draw( mine );
	}
      }


      /*** Draw numbers and reset options ***/
      sf::Texture faceHappyTex;
      faceHappyTex.loadFromFile("images/face_happy.png");
      sf::Sprite faceHappy;
      faceHappy.setTexture( faceHappyTex );

      sf::Texture faceWinTex;
      faceWinTex.loadFromFile("images/face_win.png");
      sf::Sprite faceWin;
      faceWin.setTexture( faceWinTex );

      sf::Texture faceLossTex;
      faceLossTex.loadFromFile("images/face_lose.png");
      sf::Sprite faceLoss;
      faceLoss.setTexture( faceLossTex );

      sf::Texture debugTex;
      debugTex.loadFromFile("images/debug.png");
      sf::Sprite debugTile;
      debugTile.setTexture( debugTex );

      sf::Texture digitTex;
      digitTex.loadFromFile("images/digits.png");
      sf::Sprite digit;
      digit.setTexture( digitTex );

      sf::Texture test1Tex;
      test1Tex.loadFromFile("images/test_1.png");
      sf::Sprite test1;
      test1.setTexture( test1Tex );

      sf::Texture test2Tex;
      test2Tex.loadFromFile("images/test_2.png");
      sf::Sprite test2;
      test2.setTexture( test2Tex );

      sf::Texture test3Tex;
      test3Tex.loadFromFile("images/Test_3.png");
      sf::Sprite test3;
      test3.setTexture( test3Tex );

      // Draw win/loss/playing face
      if (win) {
	faceWin.setPosition(32*(TILEWIDTH / 2 - 1), 32*TILEHEIGHT);
	window.draw( faceWin );
      } else if (loss) {
	faceLoss.setPosition(32*(TILEWIDTH / 2 - 1), 32*TILEHEIGHT);
	window.draw( faceLoss );
      } else {
	faceHappy.setPosition(32*(TILEWIDTH / 2 - 1), 32*TILEHEIGHT);
	window.draw( faceHappy );
      }

      // Draw debug option
      debugTile.setPosition(32*(TILEWIDTH / 2 + 4), 32*TILEHEIGHT);
      window.draw( debugTile );

      // Preset boards
      test1.setPosition(32*(TILEWIDTH / 2 + 7), 32*TILEHEIGHT);
      window.draw( test1 );
      test2.setPosition(32*(TILEWIDTH / 2 + 9), 32*TILEHEIGHT);
      window.draw( test2 );
      test3.setPosition(32*(TILEWIDTH / 2 + 11), 32*TILEHEIGHT);
      window.draw( test3 );

      // Remaining mine count
      int count = mines - flags;

      // Hundreds place
      if (count < 0) {
	digit.setTextureRect( sf::IntRect(21*10, 0, 21*11 - 1, 31) );	
	count = -count;
      }	else {
	digit.setTextureRect( sf::IntRect(21*(count/100), 0, 21, 32) );
	count = count - 100*(count / 100);
      }
      digit.setPosition(0, 32*TILEHEIGHT);
      window.draw( digit );

      // Tens place
      digit.setTextureRect( sf::IntRect(21*(count/10), 0, 21, 32) );
      count = count - 10*(count / 10);
      digit.setPosition(21, 32*TILEHEIGHT);
      window.draw( digit );

      // Ones place
      digit.setTextureRect( sf::IntRect(21*count, 0, 21, 32) );
      digit.setPosition(42, 32*TILEHEIGHT);
      window.draw( digit );

    }
  }

  window.display();
}

void Game::Left(double x, double y) {
  // Find clicked tile
  int xtile = (int) (x / 32);
  int ytile = (int) (y / 32);

  // Handle click inside mine area
  if (ytile*TILEWIDTH + xtile < TILEWIDTH*TILEHEIGHT) {
    // Do nothing if game is over
    if (win || loss) {
      return;
    }
    
    // Check if flagged
    if (tiles[ytile*TILEWIDTH + xtile].flag) {
      return;
    }

    // Check if it's a mine
    if (tiles[ytile*TILEWIDTH + xtile].mine) {
      loss = true;
      return;
    }

    tiles[ytile*TILEWIDTH + xtile].reveal();

    // Check for win
    win = true;
    for (int i = 0; i < TILEHEIGHT*TILEWIDTH; ++i) {
      // If there are any tiles hidden that are not mines
      if (!tiles[i].mine && tiles[i].hidden) {
	win = false;
      }
    }
    
    return;
  }

  // Handle reset/debug clicks
  if (y >= 512 && y < 576) {
    // Normal reset
    if (x >= 352 && x < 416) {
      win = false;
      loss = false;
      SetTiles(tiles);
      return;
    } else if (x >= 512 && x < 586) {
      debug = !debug;
    } else if (x >= 618 && x < 682) {
      win = false;
      loss = false;
      SetTiles(tiles, "boards/testboard1.brd");
    } else if (x >= 682 && x < 746) {
      win = false;
      loss = false;
      SetTiles(tiles, "boards/testboard2.brd");
    } else if (x >= 746) {
      win = false;
      loss = false;
      SetTiles(tiles, "boards/testboard3.brd");
    }
  }
  
}

void Game::Right(double x, double y) {
  int xtile = (int) (x / 32);
  int ytile = (int) (y / 32);

  if (ytile*TILEWIDTH + xtile >= TILEWIDTH*TILEHEIGHT) {
    return;
  }

  if (!win && !loss) {
    if (tiles[ytile*TILEWIDTH + xtile].flag) {
      --flags;
    } else {
      ++flags;
    }
    
    tiles[ytile*TILEWIDTH + xtile].flag = !tiles[ytile*TILEWIDTH + xtile].flag;
  }
}
