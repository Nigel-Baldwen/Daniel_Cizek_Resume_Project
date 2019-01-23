#include "pch.h"
#include "Core/PABTile.h"

using namespace PABTileEnums;

void PABTile::InitializeTile(PABTileEnums::PABTileTypeEnum type)
{
	tileType = type;
	tileGrav = PABTileEnums::PABTileGravEnum::NONE;
}

void PABTile::InitializeTile(PABTileEnums::PABTileTypeEnum type, PABTileEnums::PABTileGravEnum grav)
{
	tileType = type;
	tileGrav = grav;
}

void PABTile::SetTileGravity(PABTileEnums::PABTileGravEnum grav)
{
	tileGrav = grav;
}

void PABTile::SetTileType(PABTileEnums::PABTileTypeEnum type)
{
	tileType = type;
}

bool PABTile::TileHasGravity()
{
	return tileGrav != PABTileEnums::PABTileGravEnum::NONE;
}

PABTileEnums::PABTileGravEnum PABTile::GetTileGravity()
{
	return tileGrav;
}

PABTileEnums::PABTileTypeEnum PABTile::GetTileType()
{
	return tileType;
}
