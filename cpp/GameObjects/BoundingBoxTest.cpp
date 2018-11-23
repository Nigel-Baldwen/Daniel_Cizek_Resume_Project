#include "pch.h"
#include "GameObjects/BoundingBoxTest.h"

BoundingBoxTest::BoundingBoxTest() {}

// axisOverlapTest takes in a sorted collection of (axisMin/Max, objectID) pairs
std::list<std::pair<GameObject^, GameObject^>> BoundingBoxTest::axisOverlapTest(std::list<std::pair<float, GameObject^>> sortedPairs, Simple3DGame::Axes axis)
{
	// Each object ID will appear exactly twice.
	// This will always be a clean division since sortedPairs is always 2k in size.
	int pCLength = sortedPairs.size() / 2;
	
	//Iterator for the sortedPairs list
	std::list<std::pair<float, GameObject^>>::iterator i = sortedPairs.begin();
	
	// Each sub list is a set of potential collisions.
	std::list<GameObject^> potentialCollisions;

	// Add the first element to simplify loop logic.
	potentialCollisions.push_back((*i).second);

	// Special Case: One Object In Scene
	if (pCLength == 1) {
		return objectsRequiringFurtherTesting;
	}

	i++; // Incremented once for loop logic & to account for the first element added.

	// Iterator for tracking the first GameObject^ with no matching min/max pair.
	//	A, B, C, [A - found a match] 
	//	B, C, [B - found a match]
	//	C, <--- Current position of j since no match is yet found for C
	std::list<GameObject^>::iterator j = potentialCollisions.begin();

	// Iterator tracking just past the furthest current depth of previously proccessed GameObject^s.
	//	A, B, C, [A - found a match]
	//	B, C, [B - found a match]
	//	C, <--- Current position of j since no match is yet found for C
	//	, <--- Open Spot
	//  , <--- Current position of k signifying the spot after the first empty sublist
	std::list<GameObject^>::iterator k = potentialCollisions.begin();
	k++;
	k++;

	// Iterator between j and k.
	std::list<GameObject^>::iterator l;

	while (i != sortedPairs.end()) {
		l = j; // Prep to use l
		if (j != potentialCollisions.end()) {
			l++;
		}

		// Ensure that we are still inside the list and that there is actually a handle at j
		if (j != potentialCollisions.end() && (*j) != nullptr && (*j)->Equals((*i).second)) {
			j++; // Matching ID Found, Jth sublist complete
			goto EXITLOOP;
		}

		// Check to remove interior overlaps.
		while (l != potentialCollisions.end() && (*l) != nullptr) {
			if ((*l)->Equals((*i).second)) {
				std::swap((*j), (*l));  // Swap the match with the currently unmatched element.
				j++;
				goto EXITLOOP;
			}
			l++;
		}

		l = j;

		// TODO :: Consider swapping this logic to a foreach List in PC { ... }
		// followed by a simple push_back call to make the fresh last list

		// Adding the latest element to existing collision lists and starting a fresh list.
		while (l != potentialCollisions.end() && l != k) { 
			// Additional step to set collision flags on objects
			if ((*l) != nullptr) {
				switch (axis)
				{
				case Simple3DGame::Axes::X_Axis:
					// We have to update both objects because while we may have seen these two
					// in A --> B order this time, next time we may see them in B --> A order.
					(*l)->UpdateOverlapFlags(Simple3DGame::Axes::X_Axis, (*i).second);
					(*i).second->UpdateOverlapFlags(Simple3DGame::Axes::X_Axis, (*l));
					break;
				case Simple3DGame::Axes::Y_Axis:
					// As above
					(*l)->UpdateOverlapFlags(Simple3DGame::Axes::Y_Axis, (*i).second);
					(*i).second->UpdateOverlapFlags(Simple3DGame::Axes::Y_Axis, (*l));
					break;
				default: // Must be Z_Axis
					// Now we only need to 'update' one object since there are no further tests
					// against the pair until detailed collision testing...which is what this
					// bounding box testing qualifies the pair for in the first place!
					// NB: We are guaranteed at this point, by the two above switch cases, that
					// [ A->UOF(B) == True IFF B->UOF(A) == True ] so we can check in either order.
					// UpdateOverlapFlags returns true IFF XYZ overlap occurs.
					if ((*l)->UpdateOverlapFlags(Simple3DGame::Axes::Z_Axis, (*i).second)) {
						// At this point, we are assured that the two objects have XYZ overlap.
						// Add them to the return list so that Simple3DGame can process them.
						objectsRequiringFurtherTesting.emplace_back((*l), (*i).second);
					}
					break;
				}
			}
			else { // Only need to create new lists TODO :: Change to a list of GameObject^ instead of a list of lists
				potentialCollisions.push_back((*i).second);
			}
			l++;
		}
		
		if (k != potentialCollisions.end()) {
			k++;
		}
	EXITLOOP:
		i++;
	}

	return objectsRequiringFurtherTesting;
}

