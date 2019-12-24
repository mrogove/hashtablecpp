#include <cassert>
#include <iostream>

#include "Node.hpp"
#include "LinkedList.hpp"
#include "HashTable.hpp"
/*
	begin node tests.
*/
void test1(){
  Node* node = new Node("foo",500);

  assert(node->getFreq()==500);
  assert(node->getWord()=="foo");
  assert(node->getHashVal()==-1);
  assert(node->getNext()==nullptr);

  delete node;
}

void test2(){
  Node* node = new Node("foo",50);
  node->setHashVal(12345678);

  assert(node->getHashVal()==12345678);
  assert(node->toString()=="foo 50");
  delete node;
}

void test3(){
  Node* node = new Node("foo",50);
  Node* beef = new Node("bar",77);

  node->setNext(beef);
  assert(beef->getNext()==nullptr);
  assert(node->getNext()->getWord()=="bar");

  delete node;
  delete beef;}
//copy constructor
void test4(){
  Node* node = new Node("foo",50);
  Node* beef = new Node(*node);

  assert(beef->getWord()==node->getWord());

  delete node;
  delete beef;}
//assignment operator
void test4b(){
  Node* node = new Node("foo",50);
  Node* beef = new Node("bar",8);

  *beef = *node;
  assert(node->getWord()==beef->getWord());

  delete beef;
  delete node;}
/******************
 LinkedList tests
*******************/

void test5(){
  Node* node = new Node("foo",50);
  Node* beef = new Node("bar",77);
  Node* samm = new Node("toy",9000);
  Node* blob = new Node("boop",89);

  LinkedList* list = new LinkedList();

  assert(list->getSize()==0);

  list->addToFront(node);
  list->addToFront(beef);
  list->addToFront(samm);

  // assert(list->toStringInReverseOrder()
  //   == "|<-[foo 50]<-[bar 77]<-[toy 9000]");
  assert(list->getSize()==3);

  assert(list->removeWord("foo"));//test head
  assert(list->getSize()==2);
  // assert(list->toStringInReverseOrder()=="|<-[bar 77]<-[toy 9000]");
  list->addToFront(blob);
  assert(list->removeWord("toy"));
  // std::cout<<list->toStringInReverseOrder()<<std::endl;
  assert(list->removeWord("boop"));
  // std::cout<<list->toStringInReverseOrder()<<std::endl;
  assert(list->removeWord("rumplestiltskin")==false);
  assert(list->removeWord("bar"));
  assert(list->removeWord("bar")==false);
  delete list;
}

void test6(){
  Node* node = new Node("foo",50);
  Node* beef = new Node("bar",77);
  Node* samm = new Node("toy",9000);
  Node* blob = new Node("boop",89);

  LinkedList* list = new LinkedList();

  assert(list->getSize()==0);
  // std::cout<<list->toString()<<std::endl;

  list->addToFront(node);
  list->addToFront(beef);
  list->addToFront(samm);
  list->addToFront(blob);
  // std::cout<<list->toString()<<std::endl;
  list->removeFront();
  assert(list->getSize()==3);
  // std::cout<<list->toString()<<std::endl;
  list->removeFront();
  // std::cout<<list->toString()<<std::endl;
  list->removeFront();
  // std::cout<<list->toString()<<std::endl;
  list->removeFront();
  // std::cout<<list->toString()<<std::endl;
  list->removeFront();//hooray no segfault
  // std::cout<<list->toString()<<std::endl;
  delete list;
}

/*****************
  Hash Table test
*****************/
//test default values and destructor when empty
void test7(){
  HashTable* table = new HashTable();

  assert(table->getCapacity()==2048);
  assert(table->getNumWords()==0);

  delete table;
}

void test8(){
  HashTable* table = new HashTable();

  // Node* foo = new Node(*(table->convert("kholrabi",12)));
  //holy cow it works!
  // assert(foo->getHashVal()==6859);
  // delete foo;
  // need to test this with add().

  table->add(table->convert("kholrabi",12));
  table->add(table->convert("brocc",13));
  table->add(table->convert("egg",14));
  table->add(table->convert("eggplant",44));
  table->add(table->convert("dogwood",45));
  table->add(table->convert("canteloupe",66));
  table->add(table->convert("watermelon",900));
  table->add(table->convert("extracalifragilistic",8));
  table->add(table->convert("sailboat",1800));
  table->add(table->convert("radish",11112));
  table->add(table->convert("$0.0022",40));

  // std::cout<<table->toString()<<std::endl;

  assert(table->getData("egg")->toString()=="egg 14");
  assert(table->getData("kholrabi")->toString()=="kholrabi 12");
  table->add(table->convert("kholrabi",8888888));
  // std::cout<<table->toString()<<std::endl;  
  assert(table->removeWord("kholrabi"));
  delete table;
}

void test9(){
  HashTable* table = new HashTable();

  // Node* foo = new Node(*(table->convert("kholrabi",12)));
  //holy cow it works!
  // assert(foo->getHashVal()==6859);
  // delete foo;
  // need to test this with add().

  table->add(table->convert("!",1274158));
  table->add(table->convert("$0.0008",65));
  table->add(table->convert("$0.0015",76));
  table->add(table->convert("$0.0022",40));

  // std::cout<<"trying to print"<<std::endl;
  // std::cout<<table->toString()<<std::endl;

  delete table;

}

int main(){
  test1();
  test2();
  test3();
  test4();
  test4b();
  test5();
  test6();
  test7();
  test8();
  test9();
  return 0;
}
