#pragma once

#include <cstdint>

#define BLUE 0
#define GREEN 1
#define RED 2

#define NCHANNELS 3

typedef struct {
  uint8_t subpixels[NCHANNELS];
  uint8_t &operator[](int index) {
    return subpixels[index];
  }
} Pixel;

class TGA {
 private:
  /*** Data ***/
  // Header
  const uint8_t idLength = 0;
  const uint8_t colorMapType = 0;
  const uint8_t dataTypeCode = 2;
  
  const uint16_t colorMapOrigin = 0;
  const uint16_t colorMapLength = 0;
  const uint8_t colorMapDepth = 0;
  
  const uint16_t xOrigin = 0;
  const uint16_t yOrigin = 0;
  uint16_t width = 1;
  uint16_t height = 1;
  const uint8_t bitsPerPixel = 24;
  const uint8_t imageDescriptor = 0;

  // Pixel data
  Pixel *pixels = nullptr;

  
  /*** Helper methods ***/
  // Access to size
  int size();
  // Convert to and from standardized notation
  static float std(uint8_t subpixel);  
  static uint8_t destd(float std);
  //Mathematical ops
  static uint8_t multiply(uint8_t top, uint8_t bottom);
  static uint8_t subtract(uint8_t top, uint8_t bottom);
  static uint8_t screen(uint8_t top, uint8_t bottom);
  static uint8_t overlay(uint8_t top, uint8_t bottom);
  static uint8_t add(uint8_t top, uint8_t bottom);
  static uint8_t scale(uint8_t top, float factor);
  

 public:
  /*** Methods ***/
  // Constructors
  TGA();
  TGA(char *filename);
  TGA(uint16_t width, uint16_t height);
  TGA(TGA &other);
  ~TGA();

  // Operators
  TGA &operator=(TGA &rhs);
  bool operator==(TGA &rhs);

  // File operations
  void read(char *filename);
  void write(char *outfilename);

  // Image manipulation
  static void Multiply(TGA &top, TGA &bottom, TGA &result);
  static void Subtract(TGA &top, TGA &bottom, TGA &result);
  static void Screen(TGA &top, TGA &bottom, TGA &result);
  static void Overlay(TGA &top, TGA &bottom, TGA &result);
  static void Add(TGA &top, int COLOR, uint8_t amount, TGA &result);
  static void Scale(TGA &top, int COLOR, float factor, TGA &result);
  static void toGrayscale(TGA &top, int COLOR, TGA &result);
  static void fromGrayscale(TGA &top, int COLOR, TGA &result);
  static void Reverse(TGA &top, TGA &result);

  static void EXTRACREDIT(TGA &q1, TGA &q2, TGA &q3, TGA &q4, TGA &output);
};
