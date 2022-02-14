#ifndef VEHICLE_H
#define VEHICLE_H

#include "Chassis.h"
#include "Wheel.h"

class Vehicle
{
 public:
  Chassis chassis;
  int max_wheels;
  int current_wheels;
  Wheel *wheels;

  Vehicle(Chassis);
  
  Chassis getChassis();
  void addWheel(Wheel);
  bool isBuilt();
  float price();
  void Display();
  void Drive(int);
};

#endif // VEHICLE_H
