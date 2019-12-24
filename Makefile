testfile :
	clang++ -std=c++11 -g -O0 test.cpp Node.cpp LinkedList.cpp HashTable.cpp -o test
memory :
	valgrind --leak-check=full --show-leak-kinds=all ./test
build :
	clang++ -std=c++11 -g -O0 main.cpp Node.cpp LinkedList.cpp HashTable.cpp -o database