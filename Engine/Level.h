#pragma once

#include <vector>
#include "TileMap.h"
#include "Vec2.h"

class Level
{
public:
	enum class TileType
	{
		Floor,
		Wall
	};
private:
	class Tile
	{
	public:
		TileType type;
		Color c;
	};
public:
	Level();

	void Draw( TileMap& map ) const;

	TileType GetTile( const Vei2& pos ) const;
private:
	static constexpr int size = TileMap::size;
	std::vector<Tile> tiles;
};