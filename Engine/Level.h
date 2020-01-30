#pragma once

#include <vector>
#include "TileMap.h"
#include "Vec2.h"
#include "Rect.h"
#include "Timer.h"

class Level
{
public:
	enum class TileType
	{
		Wall,
		Floor
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

	void Update( float dt );
	void Draw( TileMap& map ) const;

	void Load( const std::vector<int>& tiles );

	TileType GetTile( const Vei2& pos ) const;
	// Return random spot on ground.
	Vei2 GetValidSpot() const;
private:
	void DrawRect( const RectI& rect );
private:
	static constexpr int size = TileMap::size;
	std::vector<Tile> tiles;
	// static constexpr int deviation = 20;
	Timer tileChange = 0.5f;
};