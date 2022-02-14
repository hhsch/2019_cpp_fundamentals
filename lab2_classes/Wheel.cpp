#include "Wheel.h"

Wheel::Wheel(std::string _condition)
  {
    condition = _condition;
    mileage_left = mileage_for_condition(condition);
  }

Wheel::Wheel()
  {
    condition = "fair";
    mileage_left = mileage_for_condition(condition);
  }

float Wheel::mileage_for_condition(std::string _condition)
  {
    if (_condition.compare("poor") == 0) { return 5000; }
    else if (_condition.compare("fair") == 0) { return 10000; }
    else { return 20000; }
  }
