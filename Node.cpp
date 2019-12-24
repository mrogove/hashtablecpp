#include <string>
#include <stdexcept>

#include "Node.hpp"

Node::Node(){
  throw std::runtime_error("Not Implemented");
}

Node::Node(std::string word, int freq){
  this->word = word;
  this->freq = freq;
  this->hashVal = -1;
  this->next = nullptr;}

Node::Node(const Node& other){
  this->word = other.getWord();
  this->freq = other.getFreq();
  this->hashVal = other.getHashVal();
  this->next = other.getNext();}

Node& Node::operator=(const Node& other){
  if(&other != this){
    this->word = other.getWord();
	this->freq = other.getFreq();
	this->hashVal = other.getHashVal();
	this->next = other.getNext();
  }
  return *this;
}

Node::~Node(){}

int Node::getFreq() const{return this->freq;}

std::string Node::getWord() const{return this->word;}

unsigned int Node::getHashVal() const{return this->hashVal;}

Node* Node::getNext() const{return this->next;}

void Node::setNext(Node* next){this->next = next;}

void Node::setHashVal(unsigned int hashVal){this->hashVal = hashVal;}

std::string Node::toString() const{
  return(getWord()+" "+std::to_string(getFreq()));
}

