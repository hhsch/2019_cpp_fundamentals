#ifndef ABS_H
#define ABS_H

#include <algorithm>

template <class T>
class ABS
{
public:
  /* Memory management */
  ABS()
  {
    capacity = 1;
    size = 0;
    stack = new T[capacity];
    scale = 2.0;
    total_resizes = 0;
  }

  ABS(int cap)
  {
    capacity = cap;
    size = 0;
    stack = new T[capacity];
    scale = 2.0;
    total_resizes = 0;
  }

  ABS(int cap, float scale_factor)
  {
    capacity = cap;
    size = 0;
    stack = new T[capacity];
    scale = scale_factor;
    total_resizes = 0;
  }

  ABS(const ABS &d)
  {
    capacity = d.getMaxCapacity();
    size = d.getSize();
    scale = d.getScale();
    total_resizes = 0;
    stack = new T[capacity];
    for (unsigned int i = 0; i < size; i++)
      stack[i] = d.getData[i];
  }

  ABS &operator=(const ABS &d)
  {
    ABS tmp(d);

    std::swap(capacity, tmp.getMaxCapacity());
    std::swap(size, tmp.getSize());
    std::swap(stack, tmp.getData());
    std::swap(scale, tmp.getScale());
    total_resizes = 0; // Resizes are per-object

    return *this;
  }

  ~ABS()
  {
    delete[] stack;
  }

  /* Data operations */
  void push(T data)
  {
    if (size == capacity)
      {
	T *tmp = new T[(int) (capacity * scale)];
	for (unsigned int i = 0; i < size; i++)
	  tmp[i] = stack[i];
	std::swap(stack, tmp);
	capacity = (int) (capacity * scale);
	delete[] tmp;

	total_resizes += 1;
      }

    stack[size] = data;
    size += 1;
  }
    
  T pop()
  {
    if (size == 0)
      throw -1;

    T popped = stack[size - 1];
    size -= 1;
    
    if (size < (capacity / scale))
      {
	T *tmp = new T[(int) (capacity / scale)];
	for (unsigned int i = 0; i < size; i++)
	  tmp[i] = stack[i];
	std::swap(stack, tmp);
	capacity = (int) (capacity / scale);
	delete[] tmp;
	
	total_resizes += 1;
      }

    return popped;
  }

  T peek()
  {
    if (size == 0)
      throw -1;

    T peeked = stack[size - 1];

    return peeked;
  }

  /* Accessors */
  unsigned int getSize()
  {
    return size;
  }

  unsigned int getMaxCapacity()
  {    
    return capacity;
  }

  T *getData()
  {
    return stack;
  }

  unsigned int getScale()
  {
    return scale;
  }
  
  unsigned int getTotalResizes()
  {
    return total_resizes;
  }
  
private:
  T *stack;
  unsigned int size;
  unsigned int capacity;
  float scale;
  unsigned int total_resizes;
};

#endif // ABS_H
