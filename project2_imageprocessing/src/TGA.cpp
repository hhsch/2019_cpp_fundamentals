#include <fstream>
#include <cstdint>
#include <algorithm> // std::swap

#include "TGA.h"

TGA::TGA() {
  pixels = new Pixel[size()];
}

TGA::TGA(char *filename) {
  read(filename);
}

TGA::TGA(uint16_t _width, uint16_t _height) {
  width = _width;
  height = _height;
  pixels = new Pixel[size()];
}

TGA::TGA(TGA &other) {
  width = other.width;
  height = other.height;

  pixels = new Pixel[size()];
  for (int i = 0; i < (size()); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      pixels[i][j] = other.pixels[i][j];
    }
  }
}

TGA::~TGA() {
  delete[] pixels;
}

TGA &TGA::operator=(TGA &rhs) {
  TGA tmp(rhs);

  std::swap(width, tmp.width);
  std::swap(height, tmp.height);
  std::swap(pixels, tmp.pixels);

  return *this;
}

bool TGA::operator==(TGA &rhs) {
  if (width != rhs.width) {
    return false;
  } else if (height != rhs.height) {
    return false;
  }

  for (int i = 0; i < (size()); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      if (pixels[i][j] != rhs.pixels[i][j]) {
	return false;
      }
    }
  }

  return true;
}

void TGA::read(char *filename) {
  // Clear old image if present
  delete[] pixels;

  std::ifstream file;
  file.open(filename);

  // Get dimensions of new image
  file.seekg(12);
  file.read((char *) &width, sizeof(width));
  file.read((char *) &height, sizeof(height));

  pixels = new Pixel[size()];

  // Skip to image data
  file.seekg(18);

  // Fill array with pixel data
  for (int i = 0; i < (size()); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      file.read((char *) &pixels[i][j], sizeof(pixels[i][j]));
    }
  }

  file.close();
}

void TGA::write(char *filename) {
  std::ofstream file;
  file.open(filename, std::ofstream::binary);

  // Write header
  file.write((char *) &idLength, sizeof(idLength));
  file.write((char *) &colorMapType, sizeof(colorMapType));
  file.write((char *) &dataTypeCode, sizeof(dataTypeCode));

  file.write((char *) &colorMapOrigin, sizeof(colorMapOrigin));
  file.write((char *) &colorMapLength, sizeof(colorMapLength));
  file.write((char *) &colorMapDepth, sizeof(colorMapDepth));

  file.write((char *) &xOrigin, sizeof(xOrigin));
  file.write((char *) &yOrigin, sizeof(yOrigin));
  file.write((char *) &width, sizeof(width));
  file.write((char *) &height, sizeof(height));
  file.write((char *) &bitsPerPixel, sizeof(bitsPerPixel));
  file.write((char *) &imageDescriptor, sizeof(imageDescriptor));

  // Write pixel data
  for (int i = 0; i < (size()); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      file.write((char *) &pixels[i][j], sizeof(pixels[i][j]));
    }
  }

  file.close();
}

void TGA::Multiply(TGA &top, TGA &bottom, TGA &result) {
  if (top.size() != bottom.size()) {
    return;
  }

  // Local result
  TGA tmp(top.width, top.height);

  // Copy pixel data
  for (int i = 0; i < tmp.size(); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      tmp.pixels[i][j] = multiply(top.pixels[i][j], bottom.pixels[i][j]);
    }
  }

  result = tmp;
}

void TGA::Subtract(TGA &top, TGA &bottom, TGA &result) {
  if (top.size() != bottom.size()) {
    return;
  }

  TGA tmp(top.width, top.height);

  for (int i = 0; i < tmp.size(); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      tmp.pixels[i][j] = subtract(top.pixels[i][j], bottom.pixels[i][j]);
    }
  }

  result = tmp;
}

void TGA::Screen(TGA &top, TGA &bottom, TGA &result) {
  if (top.size() != bottom.size()) {
    return;
  }

  TGA tmp(top.width, top.height);

  for (int i = 0; i < tmp.size(); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      tmp.pixels[i][j] = screen(top.pixels[i][j], bottom.pixels[i][j]);
    }
  }

  result = tmp;
}

void TGA::Overlay(TGA &top, TGA &bottom, TGA &result) {
  if (top.size() != bottom.size()) {
    return;
  }

  TGA tmp(top.width, top.height);

  for (int i = 0; i < tmp.size(); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      tmp.pixels[i][j] = overlay(top.pixels[i][j], bottom.pixels[i][j]);
    }
  }

  result = tmp;
}

void TGA::Add(TGA &top, int COLOR, uint8_t amount, TGA &result) {
  TGA tmp = top;

  for (int i = 0; i < tmp.size(); ++i) {
    tmp.pixels[i][COLOR] = add(top.pixels[i][COLOR], amount);
  }

  result = tmp;
}

void TGA::Scale(TGA &top, int COLOR, float factor, TGA &result) {
  TGA tmp = top;

  for (int i = 0; i < tmp.size(); ++i) {
    tmp.pixels[i][COLOR] = scale(top.pixels[i][COLOR], factor);
  }

  result = tmp;
}

void TGA::toGrayscale(TGA &top, int COLOR, TGA &result) {
  TGA tmp(top.width, top.height);

  for (int i = 0; i < tmp.size(); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      tmp.pixels[i][j] = top.pixels[i][COLOR];
    }
  }

  result = tmp;
}

void TGA::fromGrayscale(TGA &top, int COLOR, TGA &result) {
  if (top.size() != result.size()) {
    result = top;
    return;
  }

  for (int i = 0; i < result.size(); ++i) {
    result.pixels[i][COLOR] = top.pixels[i][COLOR];
  }
}

void TGA::Reverse(TGA &top, TGA &result) {
  TGA tmp(top.width, top.height);

  for (int i = 0; i < tmp.size(); ++i) {
    for (int j = 0; j < NCHANNELS; ++j) {
      tmp.pixels[i][j] = top.pixels[(tmp.size() - 1) - i][j];
    }
  }

  result = tmp;
}

void TGA::EXTRACREDIT(TGA &q1, TGA &q2, TGA &q3, TGA &q4, TGA &result) {
  // Copy by hand
  // Write all four at once in the loop, offset by their correct locations
  TGA tmp(q1.width * 2, q1.height * 2);

  for (int i = 0; i < q3.height; ++i) {
    for (int j = 0; j < q3.width; ++j) {
      for (int k = 0; k < NCHANNELS; ++k) {
	tmp.pixels[i*q3.width*2 + j][k] = q3.pixels[i*q3.width + j][k];
	tmp.pixels[i*q3.width*2 + j + q3.width][k] = q4.pixels[i*q4.width + j][k];
	tmp.pixels[(i+q3.height)*q3.width*2 + j][k] = q2.pixels[i*q2.width + j][k];
	tmp.pixels[(i+q3.height)*q3.width*2 + j + q3.width][k] = q1.pixels[i*q1.width + j][k];
      }
    }
  }

  result = tmp;
}

/** Helpers **/
int TGA::size() {
  return ((int) width) * ((int) height);
}

float TGA::std(uint8_t subpixel) {
  return ((float) subpixel) / 255.0;
}

uint8_t TGA::destd(float std) {
  if (std < 0) {
    return (uint8_t) 0;
  } else if (std > 1) {
    return (uint8_t) 255;
  } else {
    return (uint8_t) (std * 255.0 + .5);
  }
}

uint8_t TGA::multiply(uint8_t top, uint8_t bottom) {
  return destd( std(top) * std(bottom) );
}

uint8_t TGA::subtract(uint8_t top, uint8_t bottom) {
  return destd( std(bottom) - std(top) );
}

uint8_t TGA::screen(uint8_t top, uint8_t bottom) {
  return destd( 1 - ((1 - std(top)) * (1 - std(bottom))) );
}

uint8_t TGA::overlay(uint8_t top, uint8_t bottom) {
  if (std(bottom) <= .5) {
    return destd( 2 * std(top) * std(bottom) );
  } else {
    return destd( 1 - (2 * (1 - std(top)) * (1 - std(bottom))) );
  }
}

uint8_t TGA::add(uint8_t top, uint8_t amount) {
  return destd( std(top) + std(amount) );
}

uint8_t TGA::scale(uint8_t top, float factor) {
  return destd( std(top) * factor );
}
