#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <iostream>

using namespace std;

BagIterator::BagIterator(const Bag& c) : bag(c) {
    currentIndex = bag.head;
    currentFreq = 1;
    cerr << "Iterator constructed. Head = " << currentIndex << ", currentFreq = " << currentFreq << "\n";
}

void BagIterator::first() {
    currentIndex = bag.head;
    currentFreq = 1;
    cerr << "Iterator reset to first(). Head = " << currentIndex << ", currentFreq = " << currentFreq << "\n";
   }

void BagIterator::next() {
    if (!valid()) {
        cerr << "next() called on invalid iterator.\n";
        throw exception();
    }

    int nodeFreq = bag.nodes[currentIndex].elem.second;
   // cerr << "next(): currentIndex = " << currentIndex << ", nodeFreq = " << nodeFreq << ", currentFreq = " << currentFreq << "\n";
    if (currentFreq < nodeFreq) {
        // Still have more occurrences of this element to return
        currentFreq++;
        //cerr << "Staying on same node, currentFreq = " << currentFreq << "\n";
    } else {
        // We have returned all occurrences of this element
        currentIndex = bag.nodes[currentIndex].next;
        currentFreq = 1;
        
    }
}

bool BagIterator::valid() const {
    return currentIndex != -1;
}

TElem BagIterator::getCurrent() const {
    if (!valid()) {
        throw exception();
    }
    // Return the current element.
    // The iterator will return this element multiple times if needed,
    // controlled by currentFreq and next().
    return bag.nodes[currentIndex].elem.first;
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}
