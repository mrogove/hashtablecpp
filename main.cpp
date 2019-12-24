#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "HashTable.hpp"
#include "LinkedList.hpp"
#include "Node.hpp"
/******************************
M ROGOVE
2019-08-04
Please see specification document for further detail

main.cpp
checks and reads in given file, allows user to interact.

*******************************/
/***********************
  helper functions for main()
***********************/
/*
//ingestFile

given a filename and a declared HashTable, goes to town ingesting
lines and adding to our HashTable. HashTable handles all resizing.
*/
bool ingestFile(HashTable* table, std::string filename){
  std::ifstream inputfile;
  std::string inputstring; //declare str
  // std::cout << filename << std::endl;
  inputfile.open(filename);

  if(inputfile.fail()){//if file opening failed
    std::cout << "Error" << std::endl;
    return false;
  }
  //let's get one line:
  else if(inputfile.is_open()){
    while(std::getline(inputfile,inputstring)){
      std::istringstream is(inputstring);
      std::string word;
      int freq;
      is >> word >> freq;
      //TODO: comment this out
      // std::cout << "word is: "<<word<<" freq is "<<freq<<std::endl;
      table->add(table->convert(word,freq));
      // std::cout << table->toString()<<std::endl;
    }
    inputfile.close();
  }
  return true;
}

//getcmd
void getCmd(HashTable* table, std::string word){
  Node* node = table->getData(word);	
  if(node==nullptr){std::cout<<"Not found"<<std::endl;}
  else{std::cout<<node->toString()<<std::endl;}
}

//putcmd
void putCmd(HashTable* table, std::string newWord, int newFreq){
  //check input
  if(newFreq<0){
    std::cout<<"Invalid"<<std::endl;
  }
  else{
    table->add(table->convert(newWord,newFreq));
    std::cout<<"Added"<<std::endl;
  }
}

//removecmd
void removeCmd(HashTable* table, std::string removalWord){
  if(table->removeWord(removalWord)){std::cout<<"Deleted"<<std::endl;}
  else{std::cout<<"Not found"<<std::endl;}
}

/**********************
	Main itself
**********************/
int main(int argc, char* argv[]){
  if(argc != 2){
    std::cout << "Error" << std::endl;}
  else{//variable prep
  	std::string filename = argv[1]; //filename from input
  	HashTable* table = new HashTable();

  	if(ingestFile(table,filename)==false){return 0;}
  	//now, start loop for input.
  	std::string userCmd = "";

  	//TODO: extract these as functions?
  	while(userCmd!=":q"){
  	  std::cin >> userCmd;
  	  
  	  if(userCmd == ":g"){
  	  	std::string searchWord = "";
  		std::cin >> searchWord;
  	  	getCmd(table, searchWord);
  	  }

  	  else if(userCmd == ":p"){
  	  	std::string newWord;
  	  	int newFreq;
  	  	std::cin >> newWord;
  	  	std::cin >> newFreq;
  	  	putCmd(table, newWord, newFreq);
  	  }

  	  else if(userCmd == ":r"){
  	  	std::string removalWord;
  	  	std::cin >> removalWord;
  	  	removeCmd(table, removalWord);
  	  }
  	  //need a handler for whitelist. not a great approach :/
  	  else if(userCmd != ":g" && userCmd != ":q" 
  	  		&& userCmd != ":p" && userCmd != ":r"){
  	  	// std::cout<<"I am acting on \'"<<userCmd<<'\''<<std::endl;
  	  	std::cout<<"Unknown command"<<std::endl;
  	  }
  	}

    delete table;
  }
  return 0;
}