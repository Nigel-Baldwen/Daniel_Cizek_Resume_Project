#include "pch.h"
#include "GameObjects/BoundingBoxTest.h"

BoundingBoxTest::BoundingBoxTest() {}

void BoundingBoxTest::ResetObjectsRequiringFurtherTesting() {
	objectsRequiringFurtherTesting.clear();
}

// axisOverlapTest takes in a sorted collection of (axisMin/Max, objectID) pairs
std::list<std::pair<GameObject^, GameObject^>> BoundingBoxTest::axisOverlapTest(std::list<std::pair<float, GameObject^>> sortedPairs, Axes axis)
{
	// Each object ID will appear exactly twice.
	// This will always be a clean division since sortedPairs is always 2k in size.
	auto pCLength = sortedPairs.size() / 2;
	
	// Special Case: One Object In Scene
	if (pCLength == 1) {
		return objectsRequiringFurtherTesting; // Pretty much a dummy return that should never happen
	}

	//Iterator for the sortedPairs list
	std::list<std::pair<float, GameObject^>>::iterator i = sortedPairs.begin();
	
	// A vector of discovered and completed objects.
	std::vector<GameObject^> potentialCollisions;
	potentialCollisions.reserve(pCLength);

	// Add the first element to simplify loop logic.
	potentialCollisions.push_back((*i).second);

	i++; // Incremented once for loop logic & to account for the first element added.

	//  size_t for tracking the first GameObject^ with no matching min/max pair.
	//	A [A - found a match] 
	//	B [B - found a match]
	//	C <--- Current position of j since no match is yet found for C
	size_t j = 0;

	// size_t tracking just past the furthest current depth of previously proccessed GameObject^s.
	//	A [A - found a match]
	//	B [B - found a match]
	//	C <--- Current position of j since no match is yet found for C
	//	  <--- Open Spot
	//    <--- Current position of k signifying the spot after the first empty sublist
	size_t k = 2;
	
	// size_t between j and k.
	size_t l;

	while (i != sortedPairs.end()) {
		l = j + 1; // Prep to use l

		// Ensure that we are still inside the list and that there is actually a handle at j
		if (j != potentialCollisions.size() && potentialCollisions[j]->Equals((*i).second)) {
			j++; // Matching ID Found, Jth sublist complete
			goto EXITLOOP;
		}

		// Check to remove interior overlaps.
		while (l < potentialCollisions.size()) {
			if (potentialCollisions[l]->Equals((*i).second)) {
				std::swap(potentialCollisions[j], potentialCollisions[l]);  // Swap the match with the currently unmatched element.
				
				if (j != pCLength) {
					j++;
				}
				goto EXITLOOP;
			}
			l++;
		}

		l = j;

		// Adding the latest element to existing collision lists and starting a fresh list.
		while (l != k) {
			// Additional step to set collision flags on objects
			if (l < potentialCollisions.size()) {
				switch (axis)
				{
				case Axes::X_Axis:
					// We have to update both objects because while we may have seen these two
					// in A --> B order this time, next time we may see them in B --> A order.
					potentialCollisions[l]->UpdateOverlapFlags(Axes::X_Axis, (*i).second->GetHashCode());
					(*i).second->UpdateOverlapFlags(Axes::X_Axis, potentialCollisions[l]->GetHashCode());
					break;
				case Axes::Y_Axis:
					// As above
					potentialCollisions[l]->UpdateOverlapFlags(Axes::Y_Axis, (*i).second->GetHashCode());
					(*i).second->UpdateOverlapFlags(Axes::Y_Axis, potentialCollisions[l]->GetHashCode());
					break;
				default: // Must be Z_Axis
					// Now we only need to 'update' one object since there are no further tests
					// against the pair until detailed collision testing...which is what this
					// bounding box testing qualifies the pair for in the first place!
					// NB: We are guaranteed at this point, by the two above switch cases, that
					// [ A->UOF(B) == True IFF B->UOF(A) == True ] so we can check in either order.
					// UpdateOverlapFlags returns true IFF XYZ overlap occurs.
					if (potentialCollisions[l]->UpdateOverlapFlags(Axes::Z_Axis, (*i).second->GetHashCode())) {
						// At this point, we are assured that the two objects have XYZ overlap.
						// Add them to the return list so that Simple3DGame can process them.
						objectsRequiringFurtherTesting.emplace_back(potentialCollisions[l], (*i).second);
					}
					break;
				}
			}
			else { // Enter this element into the list of potential collisions
				potentialCollisions.push_back((*i).second);
			}
			l++;
		}
		
		if (k != pCLength) {
			k++;
		}
	EXITLOOP:
		i++;
	}

	// TODO :: Change to a pointer return.
	// This is too expensive because it uses the copy constructor for this
	// list of pairs which ultimately recreates the list. I suppose the thing
	// that I'll end up doing is creating the list of pairs in simple3dgame and
	// passing in an __OUT__ parameter to this function.
	return objectsRequiringFurtherTesting;
}

