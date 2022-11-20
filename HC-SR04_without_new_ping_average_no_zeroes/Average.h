#pragma once
#include <stddef.h>

struct Node{
  int value;
  Node* next;
  Node(int value);
};

class Average {
public:
  int average;
  Average(size_t size);
  void append(int newVal);
  int get();
  void printArray();
private:
  int zeroCounter;
  bool isZero(int value);
  int total;
  size_t size;
  Node* head;
  Node* tail;
};