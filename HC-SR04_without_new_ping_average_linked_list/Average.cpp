#include "Average.h"
#include "Arduino.h"
#include <stddef.h>

Node::Node(int value){
  this->value = value;
  this->next = nullptr;
};

Average::Average(size_t size){
  this->average = 0;
  this->total = 0;
  this->size = size;
  this->head = new Node(0);
  Node* current = this->head;

  for(int i=1; i<size; i++){
    current->next = new Node(0);
    this->tail = current->next;
    current = current->next;
  }
};

void Average::append(int newVal){
  Node* temp = head->next;
  total -= head->value;
  delete head;
  head = temp;
  
  tail->next = new Node(newVal);
  tail = tail->next;
  total += newVal;
};

int Average::get(){
  return total / size;
};

void Average::printArray(){
  Node* current = head;
  while(current){
    Serial.print(current->value);
    Serial.print(',');
    current = current->next;
  }
  Serial.println();
};