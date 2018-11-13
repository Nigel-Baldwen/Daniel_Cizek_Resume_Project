#include "pch.h"
#include "GameObjects/BoundingBoxTest.h"

BoundingBoxTest::BoundingBoxTest() {}

// axisOverlapTest takes in a sorted collection of (axisMin/Max, objectID) pairs
std::list<std::list<int>> BoundingBoxTest::axisOverlapTest(std::list<std::pair<float, int>> sortedPairs)
{
	// Each object ID will appear exactly twice.
	// This will always be a clean division since sortedPairs is always 2k in size.
	int pCLength = sortedPairs.size() / 2;
	
	//Iterator for the sortedPairs list
	std::list<std::pair<float, int>>::iterator i = sortedPairs.begin();
	
	// We will return this list of lists. Each sub list is a set of potential collisions.
	std::list<std::list<int>> potentialCollisions(pCLength, std::list<int>());

	// Add the first element to simplify loop logic.
	(*potentialCollisions.begin()).push_back((*i).second);

	// Special Case: One Object In Scene
	if (pCLength == 1) {
		return potentialCollisions;
	}

	i++; // Incremented once for loop logic & to account for the first element added.

	// Iterator for tracking the first list with no matching min/max pair.
	//	A, B, C, [A - found a match] 
	//	B, C, [B - found a match]
	//	C, <--- Current position of j since no match is yet found for C
	std::list<std::list<int>>::iterator j = potentialCollisions.begin();

	// Iterator tracking the furthest current depth of sublists to be created.
	//	A, B, C, [A - found a match]
	//	B, C, [B - found a match]
	//	C, <--- Current position of j since no match is yet found for C
	//  , <--- Current position of k signifying a spot for a new sublist
	std::list<std::list<int>>::iterator k = potentialCollisions.begin();
	k++;

	// Iterator between j and k.
	std::list<std::list<int>>::iterator l;

	while (i != sortedPairs.end()) {
		l = j; // Prep to use l
		if (j != potentialCollisions.end()) {
			l++;
		}

		// Ensure that we are still inside the list or bad stuff will happen when we ask empty().
		if (j != potentialCollisions.end() && !(*j).empty() && (*(*j).begin()) == (*i).second) {
			j++; // Matching ID Found, Jth sublist complete
			if (k != potentialCollisions.end()) {
				k++; // Setup the next iteration
			}
			goto EXITLOOP;
		}

		// Check to remove interior overlaps.
		while (l != potentialCollisions.end() && !((*l).empty())) {
			if ((*(*l).begin()) = (*i).second) {
				std::swap((*j), (*l));  // Swap complete list with incomplete list.
				j++;
				goto EXITLOOP;
			}
			l++;
		}

		l = j;

		// Adding the latest element to existing collision lists and making a new list.
		while (l != potentialCollisions.end() && l != k) { 
			(*l).push_back((*i).second);
			l++;
		}
		
		if (k != potentialCollisions.end()) {
			k++;
		}
	EXITLOOP:
		i++;
	}

	return potentialCollisions;
}

