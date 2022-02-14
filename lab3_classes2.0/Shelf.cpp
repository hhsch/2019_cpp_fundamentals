#include <iostream>
#include <string>
#include "Shelf.h"

Shelf::Shelf(std::string name_, int capacity_)
{
  name = name_;
  capacity = capacity_;
  count = 0;
  food = new Food[capacity];
}

Shelf::Shelf()
{
  name = "";
  capacity = 0;
  count = 0;
  food = nullptr;
}

Shelf::Shelf(const Shelf& shelf)
{
  name = shelf.name;
  capacity = shelf.capacity;
  count = shelf.count;
  food = new Food[capacity];
  for (unsigned int i = 0; i < count; i++)
    food[i] = shelf.food[i];
}

Shelf& Shelf::operator=(const Shelf& shelf)
{
  Shelf tmp(shelf);
  
  std::swap(name, tmp.name);
  std::swap(capacity, tmp.capacity);
  std::swap(count, tmp.count);
  std::swap(food, tmp.food);
  
  return *this;
}

Shelf::~Shelf()
{
  delete[] food;
}

void Shelf::AddFood(const Food *food_)
{
  if (count == capacity) { return; }

  food[count] = *food_;
  count += 1;
}

void Shelf::ShowInventory() const
{
  std::cout << "Food in " << name << std::endl;
  for (unsigned int i = 0; i < count; i++)
    {
      food[i].Display();
    }
}

const Food *Shelf::GetFoodList() const
{
  return food;
}

unsigned int Shelf::GetCapacity() const
{
  return capacity;
}

unsigned int Shelf::GetCount() const
{
  return count;
}

const char *Shelf::GetName() const
{
  return (const char *) name.c_str();
}
