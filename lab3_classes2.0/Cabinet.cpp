#include <iostream>
#include <string>
#include "Cabinet.h"

Cabinet::Cabinet(std::string name_, int capacity_)
{
  name = name_;
  capacity = capacity_;
  count = 0;
  shelf = new Shelf[capacity];
}

Cabinet::~Cabinet()
{
  delete[] shelf;
}

Cabinet::Cabinet(const Cabinet& cabinet)
{
  name = cabinet.name;
  capacity = cabinet.capacity;
  count = cabinet.count;
  shelf = new Shelf[capacity];
  for (unsigned int i = 0; i < count; i++)
    shelf[i] = cabinet.shelf[i];
}

Cabinet& Cabinet::operator=(const Cabinet& cabinet)
{
  Cabinet tmp(cabinet);
  
  std::swap(name, tmp.name);
  std::swap(capacity, tmp.capacity);
  std::swap(count, tmp.count);
  std::swap(shelf, tmp.shelf);
  
  return *this;
}

void Cabinet::AddShelf(const Shelf *shelf_)
{
  if (count == capacity) { return; }

  shelf[count] = *shelf_;
  count += 1;
}

void Cabinet::ShowInventory() const
{
  std::cout << "Inventory of " << name << std::endl;
  for (unsigned int i = 0; i < count; i++)
    {
      shelf[i].ShowInventory();
      std::cout << std::endl;
    }
  printf("Average price of food: $%.2f\n", GetAveragePrice());
}

float Cabinet::GetAveragePrice() const
{
  unsigned int total_food = 0;
  float total_price = 0;

  for (unsigned int i = 0; i < count; i++)
    {
      const Food *food = shelf[i].GetFoodList();
      unsigned int num_foods = shelf[i].GetCount();

      for (unsigned int j = 0; j < num_foods; j++)
        {
 	  total_price += food[j].GetPrice();
        }
      total_food += num_foods;
    }

  return total_price / total_food;
}
