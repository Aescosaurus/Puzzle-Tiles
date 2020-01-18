#pragma once

#include <vector>
#include "Graphics.h"

class TileMap
{
public:
	TileMap();

	void Draw( Graphics& gfx ) const;

	void PutPixel( int x,int y,Color c );
	void Reset();

	Color GetPixel( int x,int y ) const;
public:
	static constexpr int size = 20;
private:
	static constexpr int tileSize = Graphics::ScreenHeight / size;
	static constexpr int padding = ( Graphics::ScreenWidth - tileSize * size ) / 2;
	std::vector<Color> tiles;
};