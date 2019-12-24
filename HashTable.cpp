#include <iostream>
#include <string>

#include "HashTable.hpp"
#include "LinkedList.hpp"
#include "Node.hpp"
/******************************
M ROGOVE
2019-08-04
Please see specification document for further detail

HashTable.cpp
the real orchestrator/where the magic happens.
Contains array of LinkedList pointers;
handles all LinkedList contents
*******************************/

/*****************************/
//constructors
HashTable::HashTable(){
  this->capacity = 2048; //arbitrary start
  this->listArray = new LinkedList*[capacity];
  this->numWords = 0;
  this->load = 0;//default val

  for(int i = 0; i<this->capacity; i++){
  	listArray[i]=nullptr;
  }
}

//not implemented
HashTable::HashTable(const HashTable& other){
  throw std::runtime_error("Not Implemented");}
HashTable& HashTable::operator=(const HashTable& other){
  throw std::runtime_error("Not Implemented");}

//destructor
HashTable::~HashTable(){
  //iterate through each address
  //if not null, delete LL.
  for(int i = 0; i<this->capacity; i++){
  	if(listArray[i]!=nullptr){
      delete listArray[i];
	}
  }
  delete [] listArray;
}

/*****************************/
//public utilities
int HashTable::getCapacity() const{
  return this->capacity;
}

int HashTable::getNumWords() const{
  return this->numWords;
}
//note: load is typically [0-10]
int HashTable::getLoad() const{
  return this->load;
}

Node* HashTable::getData(std::string word){
  int index = (generateHash(word)%this->capacity);
  // std::cout<<"index is "<<index<<std::endl;
  // std::cout<<"inside findWord and about to assign"<<std::endl;
  if(this->listArray[index]==nullptr){return nullptr;}
  Node* returnNode = this->listArray[index]->findWord(word);
  return returnNode;
}

bool HashTable::removeWord(std::string word){
  int index = (generateHash(word)%this->capacity);
  if(this->listArray[index]==nullptr){return false;}//if uninitialized
  return this->listArray[index]->removeWord(word);
  this->numWords--;
}

//Convert: takes values, creates node, assigns hash
//	can be used in conjunction with add().
Node* HashTable::convert(std::string word, int freq) {
  Node* nodeToReturn = new Node(word, freq);

  nodeToReturn->setHashVal(generateHash(word));
  // std::cout<<nodeToReturn->getHashVal()<<std::endl;
  return nodeToReturn;
}

//add: invokes addToFront on Node, using hash modulo capacity.
void HashTable::add(Node* node){
  recalculateLoad();
  // std::cout<<"loadfactor is now "<<load<<std::endl;
  if(this->load >= 10){resizeArray();}

  int index = node->getHashVal()%this->capacity;

  // std::cout<<"adding to index "<<index<<std::endl;
  if(listArray[index]==nullptr){
  	listArray[index] = new LinkedList();
  }
  std::string word = node->getWord();

  if(listArray[index]->findWord(word)!=nullptr){//if already exists
  	//remove first
  	listArray[index]->removeWord(word);
  }
  listArray[index]->addToFront(node);

  this->numWords++;//increase at end
}

//returns string rep of each list
std::string HashTable::toString() const{
  std::string returnString = "";
  for(int i = 0; i<this->capacity; i++){
  	if(listArray[i]==nullptr){//if null, add dash
  	  returnString+="-\n";
  	}
  	else{ //add the index's LinkedList val
      returnString+=listArray[i]->toString()+"\n";
    }
  } //after loop:
  return returnString;
}

/*****************************/
//private helper functions

//generates hash
// borrowed from djb2, see README
unsigned int HashTable::generateHash(const std::string& key){
  unsigned int returnInt = 5381;

  for (int i = 0; i < key.length(); i++) {
    returnInt = ((returnInt << 5) + returnInt) + int(key.at(i)); /* returnInt * 33 + c */
  }

  return returnInt;
}

//should calculate loadfactor and reassign.
void HashTable::recalculateLoad(){
  this->load = ((this->numWords*10)/(this->capacity));
}

//resize func; resize if load is >= some value
 //1- create new array with same size.
	//recreate all pointers by reference
 //2- loop through old
 //3- use unlinkHead of same
void HashTable::resizeArray(){
  // std::cout<<"resizing........."<<std::endl;
  LinkedList** swapArray = new LinkedList*[capacity];
  // std::cout<<toString()<<std::endl;
  for(int i = 0; i<this->capacity; i++){
  	swapArray[i]=listArray[i];
  }//initialize all values to old array values by reference
  //blow away old connections, doubling capacity.
  this->capacity = this->capacity*2;
  delete [] listArray; //just deletes array!
  this->listArray = new LinkedList*[capacity];//sever references
  for(int i = 0; i<this->capacity; i++){  //and initialize.
  	listArray[i]=nullptr;
  }
  //loop through swap array, using add on "new" array.
  std::string newWord;
  int newFreq;
  for(int x = 0; x<(this->capacity/2); x++){
  	// std::cout<<"I'm at the top of the main loop"<<std::endl;
  	// std::cout<<"I'm checking index "<<x<<": "<<swapArray[x]<<std::endl;
  	while(swapArray[x]!=nullptr){
  	  // std::cout<<"swapping out "<<swapArray[x]->toString()<<std::endl;
  	  //instantiate new node from old
      newWord = swapArray[x]->at(0)->getWord();
      newFreq = swapArray[x]->at(0)->getFreq();
      add(convert(newWord,newFreq));//call this table's add function.
      swapArray[x]->removeFront(); //deletes old node; we're n+1 at all times.

  	  if(swapArray[x]->isEmpty()){//check if empty/head points to nullptr
  	  	// std::cout<<"attempting to delete empty"<<std::endl;
  	  	delete swapArray[x];
  	  	// std::cout<<"attempting to reset empty"<<std::endl;
  	  	swapArray[x] = nullptr;//breaks loop//may revisit
  	  }
  	}
  	// std::cout<<"got through the loop. swapArray[x] is "<<swapArray[x]<<std::endl;
  }
  delete [] swapArray; //should be nothing left to deref.
}