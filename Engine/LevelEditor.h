#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"
#include "ColorMap.h"
#include "Lantern.h"

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
	static constexpr ColorStyle lanStyle = { Colors::Yellow,0 };
	ColorMap colMap = ColorMap::CreateCircle( Lantern::lightRadius,lanStyle,0.2f );
};