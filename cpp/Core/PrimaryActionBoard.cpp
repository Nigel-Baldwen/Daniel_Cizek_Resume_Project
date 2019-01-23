#include "pch.h"
#include "Core/PrimaryActionBoard.h"
#include <random>

using namespace PABTileEnums;

void PrimaryActionBoard::Initialize(int clmns, int rws)
{
	columns = clmns;
	rows = rws;
	for (int i = 0; i < rows; i++) {
		primaryActionBoard.push_back(std::vector<PABTile>(columns));
	}
}

void PrimaryActionBoard::RefreshBoard()
{
	for each (std::vector<PABTile> interiorVector in primaryActionBoard)
	{
		for each (PABTile tile in interiorVector) // TODO :: Maybe we replace this with std::fill
		{
			tile.SetTileType(PABTileEnums::PABTileTypeEnum::BLANK);
		}
	}

	// Get a list of all coordinate pairs (R,C) for randomizing in the next step.
	int tileCount = rows * columns;
	std::vector<int> tileSelector(tileCount);
	
	// Create a list of ints ranging from 0-tileCount
	for (int i = 0; i < tileCount; i++) {
		tileSelector[i] = i;
	}

	// Randomize list order
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(tileSelector.begin(), tileSelector.end(), std::default_random_engine((unsigned int) seed));


	// Generate gravity directions on the board.
	for each (int tileLoc in tileSelector)
	{
		int r = tileLoc / rows;
		int c = tileLoc % columns;

		if (primaryActionBoard[r][c].TileHasGravity()) {
			continue;
		}

		GeneratePathHeadToTailTillEdge(r, c);
	}

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 7); // guaranteed unbiased
	
	for each (std::vector<PABTile> tileVector in primaryActionBoard)
	{
		for each (PABTile tile in tileVector) {
			tile.SetTileType(static_cast<PABTileTypeEnum>(uni(rng)));
		}
	}
}

void PrimaryActionBoard::GeneratePathHeadToTailTillEdge(int r, int c) {

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 3); // guaranteed unbiased
	auto random_integer = uni(rng);

	// Pick a direction for the next iteration to go preferring open directions
	// Set Gravity in the opposite direction
	// repeat until you hit an edge

	bool keepGenerating = true;


	do { // The loop for generating gravity tile by tile. We change either r or c until we hit an edge
		
		random_integer = uni(rng);
		
		for (int i = 0; i < 12; i++) { // Enables us to sequentially check all four directions for smoothly
			// Check the edge in the direction
			// if gravity in that direction is not
			// set, we want to generate in that direction

			// We prefer edges followed by open tiles followed lastly by set tiles

			switch (random_integer)
			{
			case 0: // Left
				if (c - 1 < 0) { // Edge; Preferred
					// Set Gravity to point away from the edge, thus ending the path
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::RIGHT);
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				else if (i > 3 && i < 8 && !primaryActionBoard[r][c - 1].TileHasGravity()) {
					// Tile has no gravity so we should point our tail to it.
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::RIGHT);
					c -= 1;
					goto ExitForLoop;
				}
				else if (i > 7 && primaryActionBoard[r][c-1].GetTileGravity() != PABTileGravEnum::LEFT) { // All Surrounding Tiles Had Gravity Set
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::RIGHT); // Point Tail At Tile To Left
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				break;
			case 1: // Up
				if (r - 1 < 0) { // Edge; Preferred
					// Set Gravity to point away from the edge, thus ending the path
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::DOWN);
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				else if (i > 3 && i < 8 && !primaryActionBoard[r - 1][c].TileHasGravity()) {
					// Tile has no gravity so we should point our tail to it.
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::DOWN);
					r -= 1;
					goto ExitForLoop;
				}
				else if (i > 7 && primaryActionBoard[r - 1][c].GetTileGravity() != PABTileGravEnum::UP) { // All Surrounding Tiles Had Gravity Set
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::DOWN); // Point Tail At Tile Above 
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				break;
			case 2: // Right
				if (c + 1 > columns) { // Edge; Preferred
					// Set Gravity to point away from the edge, thus ending the path
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::LEFT);
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				else if (i > 3 && i < 8 && !primaryActionBoard[r][c + 1].TileHasGravity()) {
					// Tile has no gravity so we should point our tail to it.
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::LEFT);
					c += 1;
					goto ExitForLoop;
				}
				else if (i > 7 && primaryActionBoard[r][c + 1].GetTileGravity() != PABTileGravEnum::RIGHT) { // All Surrounding Tiles Had Gravity Set
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::LEFT); // Point Tail At Tile To Right
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				break;
			default: // Down
				if (r + 1 < 0) { // Edge; Preferred
						// Set Gravity to point away from the edge, thus ending the path
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::UP);
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				else if (i > 3 && i < 8 && !primaryActionBoard[r + 1][c].TileHasGravity()) {
					// Tile has no gravity so we should point our tail to it.
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::UP);
					r += 1;
					goto ExitForLoop;
				}
				else if (i > 7 && primaryActionBoard[r + 1][c].GetTileGravity() != PABTileGravEnum::DOWN) { // All Surrounding Tiles Had Gravity Set
					primaryActionBoard[r][c].SetTileGravity(PABTileGravEnum::UP); // Point Tail At Tile Below
					keepGenerating = false; // Path Ended, Stop Generating
					goto ExitForLoop;
				}
				break;
			}
			random_integer = (random_integer + 1) % 4;
		}
	ExitForLoop:;
	} while (keepGenerating);
}
