#ifndef ABQ_H
#define ABQ_H

#include <algorithm>

/* Rewrite without shifting, using cyclic queue */
/* Much MUCH faster */
template <class T>
class ABQ
{
public:
  ABQ()
  {
    capacity = 1;
    head = 0;
    tail = 0;
    queue = new T[capacity];
    scale = 2.0;
    total_resizes = 0;
  }

  ABQ(int cap)
  {
    capacity = cap;
    head = 0;
    tail = 0;
    queue = new T[capacity];
    scale = 2.0;
    total_resizes = 0;
  }

  ABQ(int cap, float scale_factor)
  {
    capacity = cap;
    head = 0;
    tail = 0;
    queue = new T[capacity];
    scale = scale_factor;
    total_resizes = 0;
  }

  ABQ(const ABQ &d)
  {
    capacity = d.getMaxCapacity();
    head = d.getHead();
    tail = d.getHead() + d.getSize();
    scale = d.getScale();
    total_resizes = 0;
    queue = new T[capacity];
    for (unsigned int i = 0; i < d.getSize(); i++)
      queue[i] = d.getData()[d.getHead() + i];
    tail = d.getSize();
    head = 0;
  }

  ABQ &operator=(const ABQ &d)
  {
    ABQ tmp(d);

    std::swap(capacity, tmp.getMaxCapacity());
    std::swap(head, tmp.getHead());
    std::swap(tail, tmp.getHead() + tmp.getSize());
    std::swap(queue, tmp.getData());
    std::swap(scale, tmp.getScale());
    total_resizes = 0; // Keeps resizes at the per-object level

    return *this;
  }

  /* Creates the cyclic aspect of the array */
  T &operator[](unsigned int index)
  {
    return queue[index % capacity];
  }

  ~ABQ()
  {
    delete[] queue;
  }

  void enqueue(T data)
  {
    if (getSize() == capacity)
      {
	T *tmp = new T[(int) (capacity * scale)];
	for (unsigned int i = 0; i < getSize(); i++)
	  tmp[i] = queue[getHead() + i];
	tail = getSize();
	head = 0;
	std::swap(queue, tmp);
	capacity = (int) (capacity * scale);
	delete[] tmp;

	total_resizes += 1;
      }

    queue[tail] = data;
    tail += 1;
  }

  T dequeue()
  {
    if (getSize() == 0)
      throw -1;

    T dequeued = queue[head];
    head += 1;

    if (getSize() < (capacity / scale))
      {
	T *tmp = new T[(int) (capacity / scale)];
	for (unsigned int i = 0; i < getSize(); i++)
	  tmp[i] = queue[getHead() + i];
	tail = getSize();
	head = 0;
	std::swap(queue, tmp);
	capacity = (int) (capacity / scale);
	delete[] tmp;

	total_resizes += 1;
      }

    return dequeued;
  }

  T peek()
  {
    if (getSize() == 0)
      throw -1;

    T peeked = queue[head];

    return peeked;
  }
  
  unsigned int getSize()
  {
    return tail - head;
  }

  unsigned int getMaxCapacity()
  {
    return capacity;
  }

  T *getData()
  {
    return queue;
  }

  unsigned int getScale()
  {
    return scale;
  }

  unsigned int getTotalResizes()
  {
    return total_resizes;
  }

  /* Need to get head for orientation */
  unsigned int getHead()
  {
    return head;
  }

private:
  T *queue;
  unsigned int head;
  unsigned int tail;
  unsigned int capacity;
  float scale;
  unsigned int total_resizes;
};

#endif // ABQ_H
