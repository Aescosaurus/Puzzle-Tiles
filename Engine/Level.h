#pragma once

#include <vector>
#include "TileMap.h"
#include "Vec2.h"
#include "Rect.h"

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
		void RandomizeColor();
	public:
		TileType type;
		Color c;
	};
public:
	Level();

	void Draw( TileMap& map ) const;

	TileType GetTile( const Vei2& pos ) const;
	// Return random spot on ground.
	Vei2 GetValidSpot() const;
private:
	void DrawRect( const RectI& rect );
private:
	static constexpr int size = TileMap::size;
	std::vector<Tile> tiles;
	static constexpr int deviation = 20;
};