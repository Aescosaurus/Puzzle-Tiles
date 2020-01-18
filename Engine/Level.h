#pragma once

#include <vector>
#include "TileMap.h"

class Level
{
public:
	Level();

	void Draw( TileMap& map ) const;
private:
	static constexpr int size = TileMap::size;
	std::vector<Color> tiles;
};