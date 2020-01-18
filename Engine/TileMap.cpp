#include "TileMap.h"
#include "Random.h"

TileMap::TileMap()
{
	int r = int( Random{ 0,255 } );
	int g = int( Random{ 0,255 } );
	int b = int( Random{ 0,255 } );
	const int delta = 20;
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			tiles.emplace_back( Colors::MakeRGB( r,g,b ) );

			r += int( Random{ -delta,delta } );
			g += int( Random{ -delta,delta } );
			b += int( Random{ -delta,delta } );

			if( r < 0 ) r = 0;
			if( r > 255 ) r = 255;
			if( g < 0 ) g = 0;
			if( g > 255 ) g = 255;
			if( b < 0 ) b = 0;
			if( b > 255 ) b = 255;
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
