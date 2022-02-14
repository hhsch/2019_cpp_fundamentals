#ifndef FOOD_H
#define FOOD_H

#include <string>

class Food
{
 public:
  Food();
  Food(std::string, std::string, int, float, int);
  void Display() const;
  std::string GetYearTypeName() const;
  float GetPrice() const;

 private:
  std::string type;
  std::string name;
  int exp_year;
  float price;
  int calories;
};

#endif // FOOD_H
