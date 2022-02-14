#include <iostream>
#include <cmath>
#include "Vehicle.h"

Vehicle::Vehicle(Chassis _chassis)  
  {
    chassis = _chassis;
    max_wheels = chassis.getNumWheels();
    current_wheels = 0;
    wheels = new Wheel[max_wheels];
  }

Chassis Vehicle::getChassis()
  {
    return chassis;
  }
  
void Vehicle::addWheel(Wheel _wheel)
  {
    /* Check to make sure we don't have too many wheels */
    if (current_wheels < max_wheels)
    {
      wheels[current_wheels] = _wheel;
      current_wheels += 1;  
    }
    else
      std::cout << "You've already added all the wheels!\n";
  }

bool Vehicle::isBuilt()
  {
    /* If we have all the wheels we're done */
    if (current_wheels == max_wheels) { return true; }
    else { return false; }
  }

float Vehicle::price()
  {
    if (current_wheels < max_wheels) { return 0; }

    /* Keep track of quality multipliers */
    float chassis_m = 1;
    float wheels_m = 1;
    
    if (chassis.quality.compare("poor") == 0) { chassis_m = 5; }
    else if (chassis.quality.compare("fair") == 0) { chassis_m = 8; }
    else if (chassis.quality.compare("good") == 0) { chassis_m = 12; }

    for (int i = 0; i < max_wheels; i++)
      {
        if (wheels[i].condition.compare("poor") == 0) { wheels_m *= 1.5; }
        else if (wheels[i].condition.compare("fair") == 0) { wheels_m *= 1.8; }
        else if (wheels[i].condition.compare("good") == 0) { wheels_m *= 2.2; }
      }

    return 500 * chassis_m * wheels_m;
  }

void Vehicle::Display()
  {
    // 'printf' for float formatting, cout otherwise 
    std::cout << "Vehicle:" << std::endl;
    /* Truncate price to fix rounding error on zybooks */
    printf("\tPrice: %.1f\n", std::trunc(10 * price()) / 10);
    std::cout << "Chassis:" << std::endl;
    std::cout << "\tSize: " << chassis.size << std::endl;
    std::cout << "\tQuality: " << chassis.quality << std::endl;
    std::cout << "\tNumber of Wheels: " << current_wheels << std::endl;
    for (int i = 0; i < current_wheels; i++)
      {
	std::cout << "Wheel " << i+1 << ":" << std::endl;
	printf("\tMileage Left: %.1f\n", wheels[i].mileage_left);
	std::cout << "\tCondition: " << wheels[i].condition << std::endl;
      }
    std::cout << std::endl;
  }

void Vehicle::Drive(int _distance)
  {
    /* First make sure we're built */
    if (!isBuilt())
      {
	std::cout << "Vehicle not built. Literally un-driveable" << std::endl;
	return;
      }
    
    int actual_distance = _distance;
    bool breakdown = false;
    
    /* Make sure all the wheels can go the full distance, otherwise
     * go as far as we can */
    for (int i = 0; i < max_wheels; i++)
      {
	if (wheels[i].mileage_left < actual_distance)
	  {
	    actual_distance = wheels[i].mileage_left;
	    breakdown = true;
	  }
      }

    /* Deduct the mileage off the wheels
     * and update their condition */
    for (int i = 0; i < max_wheels; i++)
      {
	wheels[i].mileage_left -= actual_distance;
	if (5000 < wheels[i].mileage_left && wheels[i].mileage_left <= 10000)
	  wheels[i].condition = "fair";
	else if (wheels[i].mileage_left <= 5000)
	  wheels[i].condition = "poor";
      }

    if (breakdown)
      std::cout << "Broke down! ";

    printf("You've traveled %.1f miles!\n\n", (float) actual_distance);
  }
