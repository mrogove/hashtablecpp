#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node{
public:
  Node();
  Node(std::string word, int freq);

  Node(const Node& other);
  Node& operator=(const Node& other);
  ~Node();

  int getFreq() const;
  std::string getWord() const;
  unsigned int getHashVal() const;
  Node* getNext() const;
  void setNext(Node* next);
  void setHashVal(unsigned int hashVal);
  std::string toString() const;

private:
  std::string word; //ascii string
  int freq;
  unsigned int hashVal;
  Node* next;
};

#endif
