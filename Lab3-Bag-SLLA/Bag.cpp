#include "Bag.h"
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
    maxCap = MAX_CAPACITY;
    firstEmpty = 0;
    sizeBagNow = 0;
    head = -1;
    initializeNodes();
}

void Bag::initializeNodes() {
    // Initialize all nodes and set up the free space linked list
    for (int i = 0; i < maxCap - 1; i++) {
        nodes[i].next = i + 1;
    }
    nodes[maxCap - 1].next = -1; // End of the free list
}

int Bag::getNextFreePos() {
    if (firstEmpty == -1) {
        throw exception();
    }
    int newFreePos = firstEmpty;
    firstEmpty = nodes[firstEmpty].next;
    return newFreePos;
}

void Bag::add(TElem elem) {
    if (firstEmpty == -1) {
        throw exception();  // No space left
    }

    int pos = getNextFreePos();  // Get the next free position
    nodes[pos].elem = elem;  // Store the element

    if (head == -1) {
        // If the list is empty, set the new element as head
        nodes[pos].next = -1;
        head = pos;
    } else {
        // Insert the new element at the beginning of the list
        nodes[pos].next = head;
        head = pos;
    }

    sizeBagNow++;  // Increase the size of the bag
}

bool Bag::remove(TElem elem) {
    int prev = -1;
    int current = head;  // Start from the head

    while (current != -1) {
        if (nodes[current].elem == elem) {
            // Element found
            if (prev == -1) {
                // Removing the first element (head)
                head = nodes[current].next;
            } else {
                // Bypass the current node
                nodes[prev].next = nodes[current].next;
            }

            // Free the position
            nodes[current].next = firstEmpty;
            firstEmpty = current;  // Update the first empty position
            sizeBagNow--;
            return true;  // Element removed
        }
        prev = current;
        current = nodes[current].next;
    }

    return false;  // Element not found
}


bool Bag::search(TElem elem) const {
    int current = head;  // Start searching from the beginning
    while (current != -1) {
        if (nodes[current].elem == elem) {
            return true;  // Element found
        }
        current = nodes[current].next;  // Move to the next node
    }
    return false;  // Element not found
}

int Bag::nrOccurrences(TElem elem) const {
    int count = 0;
    int current = head;  // Start from the head
    while (current != -1) {
        if (nodes[current].elem == elem) {
            count++;
        }
        current = nodes[current].next;  // Move to the next node
    }
    return count;  // Return count of occurrences
}

int Bag::size() const {
    return sizeBagNow; // Return the size of the bag
}

bool Bag::isEmpty() const {
    return sizeBagNow == 0; // Check if the bag is empty
}

Bag::~Bag() {
    // Destructor does not need to do anything for static arrays
}
