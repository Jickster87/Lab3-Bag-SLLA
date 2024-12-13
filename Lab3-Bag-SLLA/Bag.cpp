#include "Bag.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
    maxCap = MAX_CAPACITY; //maxCap = 3000 (from MAX_CAP)
    firstEmpty = 0; //first empty spot index[0] in array
    sizeBagNow = 0;
    head = -1;
    nodes = new sllaNode[maxCap];
    initnodes();
}

void Bag::initnodes(){
    for (int i=0; i < maxCap; i++) {
        nodes[i].elem = NULL_TPAIR;
        //set all next to increment to point to next index in array
        //except the last one which is -1
        if (i < maxCap-1) {
            nodes[i].next = i+1;
        } else {
            nodes[i].next = -1;
        }
    }
}

void Bag::updateFirstEmpty() {
    for (int i = 0; i < maxCap; i++) {
        if (nodes[i].elem.second == 0) {
            firstEmpty = i;
            return;
        }
    }
    firstEmpty = maxCap; // No empty slot found
}

void Bag::resize() {
    int oldCap = maxCap;
    maxCap *= 2; // double the capacity
    sllaNode* newNodes = new sllaNode[maxCap]; // allocate new array
    // First, copy over the old nodes
    for (int i = 0; i < oldCap; i++) {
        newNodes[i] = nodes[i];
    }
    // Now initialize the rest of the new array (from oldCap to maxCap-1)
    for (int i = oldCap; i < maxCap; i++) {
        newNodes[i].elem = NULL_TPAIR;
        if (i < maxCap - 1) {
            newNodes[i].next = i + 1;
        } else {
            newNodes[i].next = -1;
        }
    }
    firstEmpty = oldCap;
    delete[] nodes;
    nodes = newNodes;

}

void Bag::add(TElem elem) {
    if (firstEmpty == -1) { //waisted 2hrs here because was resizing when firstEmpty was maxCap(could mean it's at the end of the array but some slots still available and not -1(no spaces left)
        resize();
    }
    
    //I. element exists
    //search and increment
    int nomad = head;
    while (nomad != -1) {
        if (nodes[nomad].elem.first == elem) {
            nodes[nomad].elem.second += 1;
            sizeBagNow++;
            return;
        }
        nomad = nodes[nomad].next; // change the nomad value from head to next val in array
    }
    
    //II. element is new
    //add in firstEmpty spot
    int newPos = firstEmpty;
    firstEmpty = nodes[firstEmpty].next; // change first empty to next node
    
    nodes[newPos].elem = std::make_pair(elem, 1);
    nodes[newPos].next = head; //point back to next elem if exists or end of list if this is first element added in the array
    head = newPos; // increment style change of head val
    
    
    //update and increments
    //updateFirstEmpty(); //NOTE4me: hmm why dont' i need this anymore will firstEmpty always work accordingly ??
    sizeBagNow++;
}

bool Bag::remove(TElem elem) {
    // Case 1: Empty bag
    if (head == -1) {
        return false;
    }

    int current = head;
    int prev = -1;

    // Find the node with the given element
    while (current != -1 && nodes[current].elem.first != elem) {
        prev = current;
        current = nodes[current].next;
    }

    // Case 2: Element not found
    if (current == -1) {
        return false;
    }

    // We found the element at 'current'
    // Check frequency
    if (nodes[current].elem.second > 1) {
        // Just decrement frequency if more than one occurrence
        nodes[current].elem.second--;
        sizeBagNow--;
        return true;
    } else {
        // Frequency is exactly 1, remove the node entirely
        sizeBagNow--;

        // Case 3: Removing the head node
        if (current == head) {
            head = nodes[current].next;
        } else {
            // Case 4: Removing a middle or last node
            nodes[prev].next = nodes[current].next;
        }

        // Add the removed node back to the free list
        nodes[current].elem = NULL_TPAIR;
        nodes[current].next = firstEmpty;
        firstEmpty = current;

        return true;
    }
}


bool Bag::search(TElem elem) const {
    
    int nomad = head;
    while (nomad != -1 && nodes[nomad].elem.first != elem) {
        nomad = nodes[nomad].next;
    }
    if (nomad != -1) {
        return true;
    } else {
        return false;
    }
}

int Bag::nrOccurrences(TElem elem) const {
    int current = head;
    while (current != -1) {
        if (nodes[current].elem.first == elem) {
            return nodes[current].elem.second; // directly return frequency
        }
        current = nodes[current].next;
    }
    return 0; // element not found
}

int Bag::size() const {
    return sizeBagNow; // Return the size of the bag
}

bool Bag::isEmpty() const {
    return sizeBagNow == 0; // Check if the bag is empty
}

Bag::~Bag() {
    delete[] nodes;
}
