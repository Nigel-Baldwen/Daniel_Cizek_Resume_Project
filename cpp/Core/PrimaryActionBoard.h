#pragma once
#include "Core/PABTile.h"

/*
PrimaryActionBoard provides a context for the primary input of the player to take place.
This is the container which represents and manages the data model for the primary action board.
In other words, this is the thing that controls the match 3 experience core to the game.
*/

class PrimaryActionBoard {

	/* Any method with /*Context context*/
	/* Found in its argument list may eventually take an
	input but at this time I have yet to think of what would
	constitute a reasonable context indicator or class, so for
	now we will just assume context-less defaults are good enough.
	*/

public:
	void Initialize(int clmns, int rws /*, Context context*/); // Potentially, we care about which context this board was generated in.

	// Used either to provide an initial condition for the board or to reset state on a locked board.
	void RefreshBoard(/*Context context*/);
	
	// Called by other classes such as the player input processing chain to verify a move as valid and relay that information to the player.
	bool TryMove(int x1, int y1, int x2, int y2);

	

private:
	// State complexity may grow over time, but for now we only need to consider whether or not a tile is selected.
	bool isTileSelected = false;
	int columns, rows;
	std::vector<std::vector<PABTile>> primaryActionBoard;

	void GeneratePathHeadToTailTillEdge(int r, int c);
};