#include "LevelEditor.h"

LevelEditor::LevelEditor( const Keyboard& kbd,const Mouse& mouse )
	:
	kbd( kbd ),
	mouse( mouse )
{
	tiles.reserve( size * size );
	for( int i = 0; i < size * size; ++i )
	{
		tiles.emplace_back( '0' );
	}
}

void LevelEditor::Update()
{
	mousePos = mouse.GetPos();
	const auto mouseMin = TileMap::padding;
	const auto mouseMax = Graphics::ScreenWidth -
		TileMap::padding - TileMap::tileSize;
	if( mousePos.x < mouseMin ) mousePos.x = mouseMin;
	if( mousePos.x > mouseMax ) mousePos.x = mouseMax;
	mousePos.x -= TileMap::padding;
	mousePos /= TileMap::tileSize;

	if( mouse.LeftIsPressed() )
	{
		tiles[mousePos.y * size + mousePos.x] = selectedTile;
	}
}

void LevelEditor::Draw( TileMap& tilemap ) const
{
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			tilemap.PutPixel( x,y,Tile2Color( tiles[y * size + x] ) );
		}
	}

	tilemap.PutPixel( mousePos.x,mousePos.y,
		Tile2Color( selectedTile ) );
}

Color LevelEditor::Tile2Color( char tile ) const
{
	switch( tile )
	{
	case '0':
		return( Colors::MakeRGB( 0,0,40 ) );
	case '1':
		return( Colors::Gray );
	case 'p':
		return( Colors::White );
	case 'd':
		return( Colors::Cyan );
	case 'l':
		return( Colors::Orange );
	}
}
