#include <iostream>
#include <string>
#include "Food.h"

Food::Food(std::string type_,
	   std::string name_,
	   int exp_year_,
	   float price_,
	   int calories_)
{
  type = type_;
  name = name_;
  exp_year = exp_year_;
  price = price_;
  calories = calories_;
}

Food::Food()
{
  type = "";
  name = "";
  exp_year = 0;
  price = 0;
  calories = 0;
}

void Food::Display() const
{
  std::cout << GetYearTypeName() << "\t$" << price << "\t" << calories << " cal" << std::endl;
}

std::string Food::GetYearTypeName() const
{
  std::string ytn = std::to_string(exp_year) + "\t" + type + " " + name;
  return ytn;
}

float Food::GetPrice() const
{
  return price;
}
