#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

template <typename T>
class LinkedList {
public:
  // Data structure
  class Node {
  public:
    Node() {
      next = nullptr;
      prev = nullptr;
    }
    
    Node *next;
    Node *prev;
    T data;
  };

  // Behaviors
  void PrintForward() const {
    if (num_nodes == 0) { return; }
    
    PrintForwardRecursive(head);
  }
  
  void PrintReverse() const {
    if (num_nodes == 0) { return; }
    
    PrintReverseRecursive(tail);
  }
  
  void PrintForwardRecursive(const Node *node) const {
    std::cout << node->data << std::endl;
    
    if (node->next == nullptr) { return; }
    PrintForwardRecursive(node->next);
  }
  
  void PrintReverseRecursive(const Node *node) const {
    std::cout << node->data << std::endl;
    
    if (node->prev == nullptr) { return; }
    PrintReverseRecursive(node->prev);
  }

  // Accessors
  unsigned int NodeCount() const {
    return num_nodes;
  }
  
  void FindAll(std::vector<Node *> &outData, const T &value) const {
    for (Node *node = head; node != nullptr; node = node->next) {
      if (node->data == value) {
	outData.push_back(node);
      }
    }
  }
  
  const Node *Find(const T &data) const {
    return Find(data);
  }
  
  Node *Find(const T &data) {
    for (Node *node = head; node != nullptr; node = node->next)
      if (node->data == data) { return node; }

    return nullptr;
  }

  const Node *GetNode(unsigned int index) const {
    return GetNode(index);
  }
  
  Node *GetNode(unsigned int index) {
    if (num_nodes == 0 || index >= num_nodes) {
      throw std::out_of_range("Out of bounds");
    }

    Node *node = head;
    for (unsigned int i = 0; i < index; i++)
      node = node->next;

    return node;
  }
  
  Node *Head() {
    return head;
  }
  
  const Node *Head() const {
    return Head();
  }
  
  Node *Tail() {
    return tail;
  }
  
  const Node *Tail() const {
    return Tail();
  }

  // Insertion
  void AddHead(const T &data) {
    Node *newNode = new Node;
    newNode->data = data;
    
    newNode->next = head;
    if (head == nullptr) {
      tail = newNode;
    } else {
      head->prev = newNode;
    }

    head = newNode;

    num_nodes += 1;
  }
  
  void AddTail(const T &data) {
    Node *newNode = new Node;
    newNode->data = data;

    newNode->prev = tail;
    if (tail == nullptr) {
      head = newNode;
    } else {
      tail->next = newNode;
    }

    tail = newNode;

    num_nodes += 1;
  }
  
  void AddNodesHead(const T *data, unsigned int count) {
    for (unsigned int i = 1; i <= count; i++)
      AddHead( data[count - i] );
  }
  
  void AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++)
      AddTail( data[i] );
  }
  
  void InsertAfter(Node *node, const T &data) {
    if (node == tail) {
      return AddTail(data);
    }

    Node *newNode = new Node;
    newNode->data = data;

    newNode->next = node->next;
    newNode->prev = node;
    node->next = newNode;
    newNode->next->prev = newNode;

    num_nodes += 1;
  }
    
  void InsertBefore(Node *node, const T &data) {
    if (node == head) {
      return AddHead(data);
    }

    Node *newNode = new Node;
    newNode->data = data;

    newNode->prev = node->prev;
    newNode->next = node;
    node->prev = newNode;
    newNode->prev->next = newNode;

    num_nodes += 1;
  }
  
  void InsertAt(const T &data, unsigned int index) {
    if (index == num_nodes) {
      AddTail(data);
    } else {
      Node *node = GetNode(index);
      InsertBefore(node, data);
    }
  }

  // Removal
  bool RemoveHead() {
    if (num_nodes == 0) { return false; }

    Node *newHead = head->next;
    delete head;
    head = newHead;

    // May be last node
    if (head == nullptr) {
      tail = nullptr;
    } else {
      head->prev = nullptr;
    }

    num_nodes -= 1;
    return true;
  }
  
  bool RemoveTail() {
    if (num_nodes == 0) { return false; }

    Node *newTail = tail->prev;
    delete tail;
    tail = newTail;

    if (tail == nullptr) {
      head = nullptr;
    } else {
      tail->next = nullptr;
    }

    num_nodes -= 1;
    return true;
  }
  
  unsigned int Remove(const T &data) {
    unsigned int count = 0;
    
    for (Node *node = head; node != nullptr;) {
      if (node->data == data) {
	Node *next = node->next;
	Delete(node);
	node = next;
	count += 1;
      } else {
	node = node->next;
      }
    }

    num_nodes -= count;
    return count;
  }
  
  bool RemoveAt(unsigned int index) {
    if (num_nodes == 0 || index >= num_nodes) {
      return false;
    }

    Node *node = GetNode(index);
    Delete(node);
    num_nodes -= 1;
    return true;
  }
  
  void Clear() {
    while (head != nullptr)
      RemoveHead();
  }

  // Operators
  const T &operator[](unsigned int index) const {
    return operator[](index);
  }
  
  T &operator[](unsigned int index) {
    Node *node = GetNode(index);
    return node->data;
  }
  
  bool operator==(const LinkedList<T> &rhs) const {
    if (num_nodes != rhs.num_nodes) { return false; }

    Node *left = head;
    Node *right = rhs.head;
    while (left != nullptr) {
      if (left->data != right->data) { return false; }
      
      left = left->next;
      right = right->next;
    }

    return true;
  }

  LinkedList<T> &operator=(const LinkedList<T> &rhs) {
    LinkedList<T> tmp(rhs);

    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(num_nodes, tmp.num_nodes);

    return *this;
  }

  // Construction
  LinkedList() {
    head = nullptr;
    tail = nullptr;
    num_nodes = 0;
  }
  
  LinkedList(const LinkedList<T> &list) {
    head = nullptr;
    tail = nullptr;
    num_nodes = 0;
    for (Node *node = list.head; node != nullptr; node = node->next) {
      AddTail(node->data);
    }
  }
  
  ~LinkedList() {
    Clear();
  }
  
private:
  // Metadata
  Node *head;
  Node *tail;
  unsigned int num_nodes;

  // Helpers
  // Just deletes node in place
  void Delete(const Node *node) {
    if (node == head) { RemoveHead(); }
    else if (node == tail) { RemoveTail(); }

    node->next->prev = node->prev;
    node->prev->next = node->next;

    delete node;
  }
};
