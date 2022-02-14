#define RSHIFT 16
#define GSHIFT 8
#define BSHIFT 0

#define RMASK (0xff << RSHIFT)
#define GMASK (0xff << GSHIFT)
#define BMASK (0xff << BSHIFT)

class Color {
 public:
  void SetValue(int value);
  void SetName(const char *name);

  unsigned char GetR() const;
  unsigned char GetG() const;
  unsigned char GetB() const;
  std::string GetHexValue() const;
  std::string GetName() const;

  bool operator<(Color &rhs);

 private:
  unsigned char R;
  unsigned char G;
  unsigned char B;
  std::string hexValue;
  std::string name;

  std::string byteToHex(unsigned char byte);
};
