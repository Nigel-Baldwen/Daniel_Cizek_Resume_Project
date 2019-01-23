#pragma once
#include "Core/PABTileEnums.h"

/*
PrimaryActionBoardTile provides a baseline of functionality and identity
for all elements which may appear on the PrimaryActionBoard such as mana
tiles, summon effects, blocked spaces, wild cards, gold, etc.
*/

class PABTile {

public:
	void InitializeTile(PABTileEnums::PABTileTypeEnum type);
	void InitializeTile(PABTileEnums::PABTileTypeEnum type, PABTileEnums::PABTileGravEnum grav);
	void SetTileGravity(PABTileEnums::PABTileGravEnum grav);
	void SetTileType(PABTileEnums::PABTileTypeEnum type);
	bool TileHasGravity();
	PABTileEnums::PABTileGravEnum GetTileGravity();
	PABTileEnums::PABTileTypeEnum GetTileType();

private:
	PABTileEnums::PABTileGravEnum tileGrav;
	PABTileEnums::PABTileTypeEnum tileType;
};