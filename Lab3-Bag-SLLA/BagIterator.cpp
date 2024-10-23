#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

BagIterator::BagIterator(const Bag& c) : bag(c) {
    currentIndex = bag.head;  // Start at the head of the list
}

void BagIterator::first() {
    currentIndex = bag.head;  // Reset to the start of the list
}

void BagIterator::next() {
    if (!valid()) {
        throw exception();  // Throw exception if the iterator is invalid
    }
    currentIndex = bag.nodes[currentIndex].next;  // Move to the next valid element
}

bool BagIterator::valid() const {
    return currentIndex != -1;  // Check if the current index is valid
}

TElem BagIterator::getCurrent() const {
    if (!valid()) {
        throw exception();  // Throw exception if invalid
    }
    return bag.nodes[currentIndex].elem;  // Return the current element
}

BagIterator Bag::iterator() const {
    return BagIterator(*this); // Assuming BagIterator constructor accepts a Bag reference
}
