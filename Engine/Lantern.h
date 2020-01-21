#pragma once

#include "LevelObject.h"

class Lantern
	:
	public LevelObject
{
public:
	Lantern( const Vei2& pos );

	void Draw( TileMap& map ) const override;

	void Light();
private:
	bool lit = false;
};