#include <stdexcept>
#include <iostream>
#include <string>

#include "Node.hpp"
#include "LinkedList.hpp"
/******************************
M ROGOVE
2019-08-04
Please see specification document for further detail

LinkedList.cpp
contents of array for hash table.
handles all Node mem
*******************************/

//constructors
LinkedList::LinkedList(){
  this->head = nullptr;
  this->size = 0;
}

//not implemented
LinkedList::LinkedList(const LinkedList& other){
  throw std::runtime_error("Not Implemented");
}
//not implemented
LinkedList& LinkedList::operator=(const LinkedList& other){
  throw std::runtime_error("Not Implemented");
}

LinkedList::~LinkedList(){
  while(this->head != nullptr) {
    Node* pickoff = this->head;
    this->head = pickoff->getNext();
    delete pickoff;
  }
  if (this->head == nullptr){
    delete head;
  }
}

void LinkedList::addToFront(Node* node){
  if (this->head == nullptr){
    this->head = node;
  } else {
    Node* whereHeadLooks = this->head;
    node->setNext(whereHeadLooks);

    this->head = node;
  }
  this->size++;
}

void LinkedList::removeFront(){
  if(this->head == nullptr){return;}
  Node* current = this->head;
  this->head = current->getNext();

  delete current;
  this->size--;
}

bool LinkedList::removeWord(std::string word){
  Node* pointerToDelete;
  Node* current = this->head;
  Node* prev;

  if(this->head == nullptr){return false;}//empty list, implicitly.
  //what if it's the head?
  if(this->head->getWord()==word){
    pointerToDelete = this->head;
    this->head = this->head->getNext();
    delete pointerToDelete;
  }
  else{
    prev = current; //it's head now
    current = this->head->getNext();

    while(current!=nullptr && current->getWord()!=word){
      prev = current;
      current = current->getNext();
    }

    if(current != nullptr){//implicitly, let's delete current.
      pointerToDelete = current;
      prev->setNext(current->getNext());
      delete pointerToDelete;
    } else{return false;}
  }
  this->size--;//implicitly we succeeded
  return true;//and return
}

Node* LinkedList::findWord(std::string word) const{
  // std::cout <<"word is "<<word<<std::endl;
  if(this->head == nullptr){return nullptr;}//empty list, implicitly.
  Node* current = this->head;
  while(current!=nullptr){
    if(current->getWord()!=word){
      current = current->getNext();
    } 
    else{return current;}
  }
  //implicitly, we return current since we don't match:
  //this should never be reached:
  return nullptr;
}

int LinkedList::getSize() const{
  return this->size;
}

bool LinkedList::isEmpty() const {
  if(this->head == nullptr){return true;}
  return false;
}

Node* LinkedList::at(int ith) const {
  return at(this->head,0,ith);
}

Node* LinkedList::at(Node* current, int tracking, int ith) const {
  if(tracking == ith){return current;}//base case
  else{return at(current->getNext(),tracking+1,ith);}
}

std::string LinkedList::toString() const{
  std::string aggcombo = "";
    aggcombo.append("|(front)->");
  if (this->head == nullptr) {//if this is the tail, append terminator.
    aggcombo.append("_|");
  } else {
    Node* current = this->head;
    while (current->getNext() != nullptr) {
      aggcombo.append("["+current->toString()+"]"); //add next value.
      aggcombo.append("->");  //and arrow thingy
      current = current->getNext();
    };
    aggcombo.append("["+current->toString()+"]"); //add next value.
  }
  aggcombo.append("|"); //add terminator once we're at nullptr.
  return aggcombo;
}
