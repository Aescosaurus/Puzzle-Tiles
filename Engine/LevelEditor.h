#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"

class LevelEditor
{
public:
	LevelEditor( const Keyboard& kbd,const Mouse& mouse );

	void Update();
	void Draw( TileMap& tilemap ) const;
private:
	Color Tile2Color( char tile ) const;
private:
	const Keyboard& kbd;
	const Mouse& mouse;

	static constexpr int size = TileMap::size;
	const std::vector<char> items;

	std::vector<char> tiles;
	Vei2 mousePos = Vei2::Zero();
	char selectedTile = '1';
};