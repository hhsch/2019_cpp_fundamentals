#include "Chassis.h"

Chassis::Chassis(std::string _size, std::string _quality)
  {
    size = _size;
    quality = _quality;
    num_wheels = num_wheels_for_size(size);
  }
  
Chassis::Chassis()
  {
    size = "medium";
    quality = "fair";
    num_wheels = num_wheels_for_size(size);
  }

Chassis::Chassis(std::string _size)
  {
    size = _size;
    quality = "fair";
    num_wheels = num_wheels_for_size(size);
  }

int Chassis::getNumWheels()
  {
    return num_wheels;
  }

int Chassis::num_wheels_for_size(std::string _size)
  {
    if (_size.compare("small") == 0) { return 3; }
    else if (_size.compare("medium") == 0) { return 4; }
    else { return 6; }
  }
