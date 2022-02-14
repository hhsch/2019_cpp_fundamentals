#ifndef CABINET_H
#define CABINET_H

#include <string>
#include "Shelf.h"

class Cabinet
{
 public:
  Cabinet(std::string, int);
  ~Cabinet();
  Cabinet(const Cabinet&);
  Cabinet& operator=(const Cabinet&);

  void AddShelf(const Shelf *);
  void ShowInventory() const;

  float GetAveragePrice() const;

 private:
  std::string name;
  Shelf *shelf;
  unsigned int capacity;
  unsigned int count;
};

#endif // CABINET_H
