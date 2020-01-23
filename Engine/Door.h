#pragma once

#include "LevelObject.h"

class Door
	:
	public LevelObject
{
public:
	Door( const Vei2& pos );

	void Draw( TileMap& tilemap ) const override;
};