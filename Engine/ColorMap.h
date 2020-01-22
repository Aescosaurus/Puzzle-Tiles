#pragma once

#include <vector>
#include "Colors.h"
#include "TileMap.h"
#include "ColorStyle.h"

class ColorMap
{
public:
	void Draw( const Vei2& pos,TileMap& tilemap ) const;

	// static ColorMap CreateRect( int width,int height,const ColorStyle& cs );
	static ColorMap CreateCircle( int radius,const ColorStyle& cs,
		float fallOff );
private:
	static constexpr int tileSize = TileMap::tileSize;
	int width;
	int height;
	Vei2 offset;
	std::vector<Color> colors;
	std::vector<float> lights;
};