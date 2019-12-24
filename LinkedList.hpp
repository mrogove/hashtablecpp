#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"

class LinkedList{
public:
  LinkedList();
  LinkedList(const LinkedList& other);
  LinkedList& operator=(const LinkedList& other);
  ~LinkedList();

  Node* at(int ith) const;
  void addToFront(Node* node);
  void removeFront();
  int getSize() const;
  bool isEmpty() const;
  std::string toString() const;
  bool removeWord(std::string word);
  Node* findWord(std::string word) const;

private:
  Node* head;
  int size;

  Node* at(Node* current, int tracking, int ith) const;
};

#endif
