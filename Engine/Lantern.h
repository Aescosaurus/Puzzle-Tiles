#pragma once

#include "LevelObject.h"
#include <vector>
#include "Colors.h"
#include "ColorMap.h"

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
	ColorStyle style;
	ColorMap colMap;
};