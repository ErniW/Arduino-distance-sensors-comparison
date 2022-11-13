#include "queue.h"
#include "arduino.h"

Node::Node(int value){
  this->value = value;
  this->next = nullptr;
  this->prev = nullptr;
}

Queue::Queue(int max){
  this->head = nullptr;
  this->tail = nullptr;
  this->length = 0;
  this->maxLength = max;
  this->lastTimeActive = 0;
}

Queue::~Queue(){
  Node* current = head;

  while(current){
    Node* next = current->next;
    delete current;
    current = next;
  }
}

void Queue::push(int val){
  if(isFull()) {
    Serial.println("Queue full");
    return;
  }

  Node* newNode = new Node(val);

  length++;

  if(isEmpty()){
    head = newNode;
    tail = newNode;
    return;
  }

  tail->next = newNode;
  tail = newNode;
}

int Queue::pop(){
  int value = head->value;
  length--;

  Node* temp = head->next;
  delete head;
  head = temp;
  
  return value;
}

void Queue::printDirection(int number){
  switch (number) {
    case 1:
      Serial.print("LEFT");
      break;
    case 2:
      Serial.print("RIGHT");
      break;
    case 3:
      Serial.print("UP");
      break;
    case 4:
      Serial.print("DOWN");
      break;
    case 5:
      Serial.print("NEAR");
      break;
    case 6:
      Serial.print("FAR");
      break;
    default:
      Serial.print("NONE");
  } 
}

void Queue::print(){

  if(!head){
    Serial.println("Nothing to print!");
    return;
  }

  Node* current = head;

  while(current){
    printDirection(current->value);
    Serial.print(", ");
    current = current->next;
  }
  Serial.println();
}

bool Queue::isFull(){
  return length == maxLength;
}

bool Queue::isEmpty(){
  return head == nullptr;
}