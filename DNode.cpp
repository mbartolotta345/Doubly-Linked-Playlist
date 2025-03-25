#include "dnode.hpp"
#include "Song.hpp"

// Default constructor
DNode::DNode() {
    song = new Song();
    prev = nullptr;
    next = nullptr;
}

// Parameterized constructor
DNode::DNode(string s, string a, int lenmin, int lensec) {
    song = new Song(s, a, lenmin, lensec);
    prev = nullptr;
    next = nullptr;
}