#pragma once

#include <vector>
#include "Graphics.h"

class TileMap
{
public:
	TileMap();

	void Draw( Graphics& gfx ) const;
private:
	static constexpr int size = 20;
	static constexpr int tileSize = Graphics::ScreenHeight / size;
	static constexpr int padding = ( Graphics::ScreenWidth - tileSize * size ) / 2;
	std::vector<Color> tiles;
};