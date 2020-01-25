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

	void Update( UpdateInfo& info ) override;
	void Draw( TileMap& map ) const override;
private:
	void Light();
private:
	bool lit = false;
	static constexpr ColorStyle style = { Colors::MakeRGB( 240,190,110 ),10 };
	ColorMap colMap;
};