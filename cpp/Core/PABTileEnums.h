#pragma once

namespace PABTileEnums {

	/*
	Original Puzzle Quest + Puzzle Quest 2 both feature
	8 tile types, plus one wildcard base, for a total of
	up to 9 distinct base types of tiles on the board at once.

	Puzzle Quest 1 & 2 are different in that 1 features four mana
	colors and 2 five. 1 features gold on the base board and 2
	replaces it with action points. The experience tile of 1 becomes
	the purple mana tile of 2.

	Puzzle Quest 2 replaces the on board gold generation of 1 with
	a looting mini-game that is a separate consideration.
	*/

	enum class PABTileTypeEnum
	{
		BLUE, RED, GREEN, YELLOW, PURPLE, WILDCARD,
		GOLD, DAMAGE, POSITIVEPERSUASION, NEGATIVEPERSUASION,
		SUMMON, DISEASE, BLOCKED, BLANK
	};

	enum class PABTileGravEnum
	{
		LEFT, RIGHT, UP, DOWN, NONE
	};
}