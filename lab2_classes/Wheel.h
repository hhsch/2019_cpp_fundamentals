#ifndef WHEEL_H
#define WHEEL_H

#include <string>

class Wheel
{
 public:
  std::string condition;
  float mileage_left;
  
  Wheel(std::string);
  Wheel();

 private:
  /* Finds the default number of miles a given wheel can go */
  float mileage_for_condition(std::string);
};

#endif // WHEEL_H
