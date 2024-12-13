#pragma once
#include <utility>
//DO NOT INCLUDE BAGITERATOR
//DO NOT CHANGE THIS PART

#define NULL_TELEM -111111
#define NULL_TPAIR pair<TElem, TFreq>(-111111, 0)

typedef int TElem;
typedef int TFreq;
typedef std::pair <TElem, TFreq> TPair;
const int MAX_CAPACITY = 300;  // why is resize breaking it!!!

class BagIterator;
class Bag {
    
private:
	//TODO - Representation
    //array of type sllaNode;
    struct sllaNode {
        TPair elem; //elem of type telem = int type
        int next; //pointer to next of type int[index_pointer]
    };

    sllaNode * nodes; //array with max cap of 3000
    
    int maxCap; //maxcap var for resizing later the default:3000 array
    int head; //head of SLL tracker int[]
    int firstEmpty; //keep track of first free spotxx
    int sizeBagNow;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

    void initnodes();
    void resize();
    void updateFirstEmpty() ;
	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
