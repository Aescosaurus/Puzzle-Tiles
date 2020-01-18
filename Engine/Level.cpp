#include "Level.h"
#include "Random.h"

Level::Level()
{
	int r = int( Random{ 0,255 } );
	int g = int( Random{ 0,255 } );
	int b = int( Random{ 0,255 } );
	const int delta = 20;
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			tiles.emplace_back( Tile{ TileType::Floor,
				Colors::MakeRGB( r,g,b ) } );
			if( x == 0 || x == size - 1 ||
				y == 0 || y == size - 1 )
			{
				tiles.back().type = TileType::Wall;
			}

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

void Level::Draw( TileMap& map ) const
{
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			map.PutPixel( x,y,tiles[y * size + x].c );
		}
	}
}

Level::TileType Level::GetTile( const Vei2& pos ) const
{
	return( tiles[pos.y * size + pos.x].type );
}
