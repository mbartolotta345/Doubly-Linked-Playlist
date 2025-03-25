
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
#include <cstdlib> // for srand, rand
#include <ctime>   // for time
using namespace std;

//Check Playlist.cpp for instructions of what to write here and how to test it


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numSongs = 0;
		srand(time(0));
	}
	DLL::DLL(string t, string l, int m, int s){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,l,m,s);
		first = n;
		last = n;
		numSongs=1;
	}



	void DLL::push(string n, string a, int m, int s) {  // does what you'd think
		if (first == NULL) {
			first = new DNode (n,a,m,s);
			last = first;
		}
		else { // List is not empty
			// first does not change
			last->next = new DNode (n,a,m,s);
			last->next->prev = last;
			last = last->next; // update late node to the newly added one
		}

		numSongs++;
	}

	void DLL::printList() {
		DNode *curr = first;
		while (curr != nullptr) {
			cout << curr->song->title << ", ";
			cout << curr->song->artist << "................";
			cout << curr->song->min << ":";
			if (curr->song->sec < 10) {
				cout << 0 << curr->song->sec << endl;
			}
			else {
				cout << curr->song->sec << endl;
			}

			curr = curr->next;
		}
		cout << endl;
	}

	Song* DLL::pop() {
		Song *ret = last->song;
		last->prev->next = nullptr;
		last = last->prev;
		return ret;
	}


	void DLL::moveUp(string s) {
		DNode *curr = first;
		while (curr != nullptr) {
			if (curr->song->title == s) {
				if (curr->prev == nullptr) { // first element in list
					curr->next->prev = nullptr;
					first = curr->next;

					last->next = curr;
					curr->prev = last;
					last = curr;
					curr->next = nullptr;
				}
				else {
					string tempTitle = curr->prev->song->title;
					string tempArtist = curr->prev->song->artist;
					int tempMin= curr->prev->song->min;
					int tempSec =curr->prev->song->sec;

					curr->prev->song->title = curr->song->title;
					curr->prev->song->artist = curr->song->artist;
					curr->prev->song->min = curr->song->min;
					curr->prev->song->sec = curr->song->sec;

					curr->song->title = tempTitle;
					curr->song->artist = tempArtist;
					curr->song->min = tempMin;
					curr->song->sec = tempSec;
				}

				break;
			}
			curr = curr->next;
		}
	}

	void DLL::listDuration(int *tm, int *ts) {
		DNode *curr = first;
		int total_min = 0;
		int total_sec = 0;
		while (curr != nullptr) {
			total_min += curr -> song->min;
			total_sec += curr -> song->sec;

			curr = curr->next;
		}
		*tm = total_min;
		*ts = total_sec;

			}
	void DLL::moveDown(string s) {
		DNode *curr = first;
		while (curr != nullptr) {
			if (curr->song->title == s) {
				if (curr->next == nullptr) { //if it's the last element, swap with previous
					curr->prev->next = nullptr;
					last = curr->prev;

					curr->next = first;
					first->prev = curr;
					first = curr;
					curr->prev = nullptr;
				}
				else {
					// Swap curr and curr->next
					string tempTitle = curr->next->song->title;
					string tempArtist = curr->next->song->artist;
					int tempMin = curr->next->song->min;
					int tempSec = curr->next->song->sec;

					curr->next->song->title = curr->song->title;
					curr->next->song->artist = curr->song->artist;
					curr->next->song->min = curr->song->min;
					curr->next->song->sec = curr->song->sec;

					curr->song->title = tempTitle;
					curr->song->artist = tempArtist;
					curr->song->min = tempMin;
					curr->song->sec = tempSec;
				}

				break;

			}
			curr = curr->next;
		}

	}
	void DLL::makeRandom() {
		if (numSongs <= 1) return;  // No need to shuffle if there's 0 or 1 song.

		DNode* newFirst = nullptr;  // New shuffled list head
		DNode* newLast = nullptr;   // New shuffled list tail

		while (numSongs > 0) {
			int randomIndex = rand() % numSongs;  // Pick a random index

			DNode* selected = first;
			DNode* prev = nullptr;

			// Traverse to the randomly chosen node
			for (int i = 0; i < randomIndex; i++) {
				prev = selected;
				selected = selected->next;
			}

			// Remove selected node from the original list
			if (prev == nullptr) {  // If selecting first node
				first = first->next;
				if (first) first->prev = nullptr;
			} else {
				prev->next = selected->next;
				if (selected->next) {
					selected->next->prev = prev;
				}
			}

			if (selected == last) {
				last = prev;  // Update last if needed
			}

			numSongs--;

			// Add selected node to the new shuffled list
			selected->next = nullptr;
			selected->prev = newLast;
			if (newLast) {
				newLast->next = selected;
			} else {
				newFirst = selected;  // First node in the new list
			}
			newLast = selected;
		}

		// Update first and last pointers
		first = newFirst;
		last = newLast;
		numSongs = 0; // Reset counter, then recount

		// Count nodes to update numSongs correctly
		DNode* temp = first;
		while (temp) {
			numSongs++;
			temp = temp->next;
		}
	}


	int DLL::remove(string s) {
		// note that the int returned is the index - this is standard for a remove, but we won't be using it.
		int index = 0;
		DNode *curr = first;
		while (curr != nullptr) {
			if (curr->song->title == s) {
				cout << "Removing: ";
				cout << curr->song->title << ", ";
				cout << curr->song->artist << "................";
				cout << curr->song->min << ":";
				if (curr->song->sec < 10) {
					cout << 0 << curr->song->sec << endl;
				}
				else {
					cout << curr->song->sec << endl;
				}



				if (curr->next == nullptr) { // last element
					curr->prev->next = nullptr;
					last = curr->prev;
				}
				else if (curr->prev == nullptr) { // first element
					curr->next->prev = nullptr;
					first = curr->next;
				}
				else { //three elements
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
				}
				return index;
			}

			curr = curr->next;
			index++;
		}
		return -1;
	}

DLL::~DLL() {
		DNode *curr = first;
		while (curr != nullptr) {
			DNode *nextNode = curr->next; // Store next node before deleting
			delete curr;                  // Free current node
			curr = nextNode;               // Move to next node
		}
		first = nullptr;
		last = nullptr;
	}
