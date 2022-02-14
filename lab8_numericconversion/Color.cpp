#include <string>

#include "Color.h"

void Color::SetValue(int value) {
  R = (value & RMASK) >> RSHIFT;
  G = (value & GMASK) >> GSHIFT;
  B = (value & BMASK) >> BSHIFT;

  hexValue = "0x";
  hexValue += byteToHex(R);
  hexValue += byteToHex(G);
  hexValue += byteToHex(B);
}

void Color::SetName(const char *name) {
  this->name = std::string(name);
}

unsigned char Color::GetR() const {
  return R;
}

unsigned char Color::GetG() const {
  return G;
}

unsigned char Color::GetB() const {
  return B;
}

std::string Color::GetHexValue() const {
  return hexValue;
}

std::string Color::GetName() const {
  return name;
}

bool Color::operator<(Color &rhs) {
  return name < rhs.name;
}

std::string Color::byteToHex(unsigned char byte) {
  std::string hex = "";

  unsigned char highbyte = (byte & 0xf0) >> 4;
  unsigned char lowbyte = byte & 0x0f;

  if (highbyte <= 9) {
    highbyte += '0';
  } else {
    highbyte += ('A' - 10);
  }

  if (lowbyte <= 9) {
    lowbyte += '0';
  } else {
    lowbyte += ('A' - 10);
  }
  
  hex += std::string( 1, highbyte );
  hex += std::string( 1, lowbyte );

  return hex;
}
