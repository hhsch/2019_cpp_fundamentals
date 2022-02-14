#ifndef SHELF_H
#define SHELF_H

#include <string>
#include "Food.h"

class Shelf
{
 public:
  Shelf();
  Shelf(std::string, int);
  ~Shelf();
  Shelf(const Shelf&);
  Shelf& operator=(const Shelf&);
    
  void AddFood(const Food *);
  void ShowInventory() const;

  const Food *GetFoodList() const;
  unsigned int GetCapacity() const;
  unsigned int GetCount() const;
  const char *GetName() const;

 private:
  std::string name;
  Food *food;
  unsigned int capacity;
  unsigned int count;
};

#endif // SHELF_H
