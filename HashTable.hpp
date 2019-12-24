#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include <iostream>
#include "LinkedList.hpp"
#include "Node.hpp"

class HashTable
{
public:
  HashTable();
  HashTable(const HashTable& other);
  HashTable& operator=(const HashTable& other);
  ~HashTable();

  int getCapacity() const;
  int getNumWords() const;
  int getLoad() const; 
  Node* getData(std::string word);
  std::string toString() const;
  Node* convert(std::string word, int freq);
  void add(Node* node);
  bool removeWord(std::string word);

private:
  LinkedList** listArray;
  int capacity;
  int numWords;
  int load;

  unsigned int generateHash(const std::string& key);
  void recalculateLoad();
  void resizeArray();
};

#endif