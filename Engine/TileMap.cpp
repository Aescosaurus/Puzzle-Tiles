#include "TileMap.h"
#include "Random.h"

TileMap::TileMap()
{
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			tiles.emplace_back( Colors::Black );
		}
	}
}

void TileMap::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			gfx.DrawRect( padding + x * tileSize,y * tileSize,
				tileSize,tileSize,
				tiles[y * size + x] );
		}
	}
}

void TileMap::PutPixel( int x,int y,Color c )
{
	tiles[y * size + x] = c;
}

void TileMap::Reset()
{
	for( auto& tile : tiles )
	{
		tile = Colors::Black;
	}
}

Color TileMap::GetPixel( int x,int y ) const
{
	return( tiles[y * size + x] );
}
