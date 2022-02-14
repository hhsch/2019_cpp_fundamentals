#ifndef CHASSIS_H
#define CHASSIS_H

#include <string>

class Chassis
{
 public:
  std::string size;
  std::string quality;
  int num_wheels;
  
  Chassis();
  Chassis(std::string);
  Chassis(std::string, std::string);
  int getNumWheels();

 private:
  /* Returns number of wheels a given chassis should have */
  int num_wheels_for_size(std::string);
};

#endif // CHASSIS_H
