1.Name​: Michael Rogove.
2.Date​: 2019-08-04.
3.Summary​: This program implements and then orchestrates a HashTable to read in a given file, and allow users to interact with the Hashtable, putting, getting, and/or removing data from the Table. Crucially, the table should resize itself.

4.Files​: Node.cpp, Node.hpp, HashTable.cpp, HashTable.hpp, LinkedList.cpp, LinkedList.hpp, Makefile, main.cpp, test.cpp.

5.Instructions​: To build and execute test file:
`make testfile`

Then, run:
`./test`

For valgrind, run:
`make memory`

To run main file, simply do:
`make build`

and then using a given filename:
`./database ./dataset_small.tsv`
and interact with it like so:
`g: word` to get a given word
`p: word frequency` to add given data to the HashTable
`r: word` to remove the word, and
`q:` to quit the program.

6.References​:

I almost exclusively used the work and references from labs (lab8 for hasher) and past projects to execute this.

I ended up rewriting the hash algorithm and got massive results from it, borrowed from this:
https://www.programmingalgorithms.com/algorithm/djb-hash?lang=C%2B%2B

The reason this was so much more efficient was not just the distribution (which was a factor of about 5 better), but because it ran /quickly/, where my function was just not as fast!

Like in P4, these were really useful:
- Stack Overflow on Arrays of Pointers (1): https://stackoverflow.com/questions/620843/how-do-i-create-an-array-of-pointers
- Stack Overflow on Arrays of Pointers (2): https://stackoverflow.com/questions/47925124/c-dynamic-array-of-pointers

And this as a file i/o user interaction reference:
http://www.cplusplus.com/doc/tutorial/files/

7.Post evaluation on planning​: 
I really struggled with this project, mostly out of fear of the file i/o. Comp11 was a long time ago for me.

This was one of those things where I was just on my own (not able to attend office hours this week unfortunately), and I came up with a satisfactory if not satisfying approach (cin).

But what bugged me (and my project) was intializing the LinkedList array. I got jumpy, and always intialized by looping back through the (newly created) arrays (including in resizes), and setting each value to nullptr. This probably saved a lot of space in local minima, but didn't actually do me any good, and I believed it to be a source of runtime complexity (forcing me into additional O(4n) loops).

However, once ingested (at ~4-4.5 minutes before the hasher rewrite), the responsiveness was very snappy, which I was really happy with. I just wish I could have refactored the array of LinkedLists implementation satisfactorily. That design "non-choice" early on put me in a position I didn't want to be in. In sum: my bottlenecks were array resizing (multiple O(n) operations, perhaps not all necessary in all functions), and the hasher algorithm (before rewrite). Even with the less effective old hsahing algorithm (which scored ~250 in lab8), with its more frequent collisions, the hashtable was still _really_ fast, with time complexity of O([t+]c) for `:g`, where c is the length of chain at index given by hasher, with its (constant) time complexity of t.

I experimented with various loadfactors, settling on 1.0 as being satisfactory for resize. Refactoring at .7 wasn't really giving me many benefits.