#pragma once

struct Node{
  int value;
  Node* next;
  Node* prev;
  Node(int value);
};

enum {
  READING_GESTURE,
  IDLE,
  CLEARING
};

class Queue{
public:
  int state;
  Queue(int max);
  ~Queue();
  void push(int val);
  int pop();
  void printDirection(int number);
  void print();
  bool isFull();
  bool isEmpty();
  int length;
  int maxLength;
  unsigned long lastTimeActive;
private:
  Node* head;
  Node* tail;
};