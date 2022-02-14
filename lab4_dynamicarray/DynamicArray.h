#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <stdexcept>

template <class T>
class DynamicArray
{
public:
  /* Accessors */
  unsigned int GetCapacity() const
  {
    return capacity;
  }

  unsigned int GetSize() const
  {
    return size;
  }

  const T *GetData() const
  {
    return data;
  }

  const T &operator[](unsigned int index) const
  {
    if (size == 0 || (size - 1) < index)
      throw std::runtime_error("Error! Invalid index");

    return data[index];
  }

  T &operator[](unsigned int index)
  {
    if (size == 0 || (size - 1) < index)
      throw std::runtime_error("Error! Invalid index");

    return data[index];
  }

  const T &At(unsigned int index) const
  {
    if (size == 0 || (size - 1) < index)
      throw std::runtime_error("Error! Invalid index");

    return data[index];
  }

  T &At(unsigned int index)
  {
    if (size == 0 || (size - 1) < index)
      throw std::runtime_error("Error! Invalid index");

    return data[index];
  }

  /* Mutators */
  void Add(const T &newData)
  {
    if (size == capacity)
      {
	Resize(capacity + 1);
	Add(newData);
      }
    else
      {
	data[size] = newData;
	size += 1;
      }
  }

  void Resize(unsigned int newSize)
  {
    std::cout << "Resizing... old capacity: " << capacity;
    std::cout << " New capacity: " << newSize << std::endl;

    T *tmp = new T[newSize];
    size = size < newSize ? size : newSize;
    capacity = newSize;
    for (unsigned int i = 0; i < size; i++)
      tmp[i] = data[i];
    delete[] data;
    data = tmp;
  }

  void Remove(unsigned int index)
  {
    if (size == 0 || (size - 1) < index)
      throw std::runtime_error("Error! Invalid index");

    for (unsigned int i = index; i < (size - 1); i++)
      data[i] = data[i+1];
    size -= 1;
  }

  /* Memory management */
  DynamicArray()
  {
    data = nullptr;
    size = 0;
    capacity = 0;
  }

  DynamicArray(unsigned int cap)
  {
    data = new T[cap];
    size = 0;
    capacity = cap;
  }

  DynamicArray(const DynamicArray &d)
  {
    data = new T[d.GetCapacity()];
    size = d.GetSize();
    capacity = d.GetCapacity();
    for (unsigned int i = 0; i < size; i++)
     data[i] = d.GetData()[i];
  }

  DynamicArray &operator=(const DynamicArray &d)
  {
    delete[] data;
    data = new T[d.GetCapacity()];
    size = d.GetSize();
    capacity = d.GetCapacity();
    for (unsigned int i = 0; i < size; i++)
      data[i] = d.GetData()[i];

    return *this;
  }

  ~DynamicArray()
  {
    delete[] data;
  }

private:
  T *data;
  unsigned int size;
  unsigned int capacity;
};

#endif // DYNAMIC_ARRAY_H
