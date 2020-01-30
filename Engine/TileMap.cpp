#include "TileMap.h"
#include "Random.h"

TileMap::TileMap()
{
	tiles.reserve( size * size );
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			tiles.emplace_back( Colors::Black );
		}
	}
	lightMap.reserve( size * size );
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			lightMap.emplace_back( std::make_pair(
				Colors::Black,globalBrightness ) );
		}
	}
}

void TileMap::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			// gfx.DrawRect( padding + x * tileSize,y * tileSize,
			// 	tileSize,tileSize,
			// 	tiles[y * size + x] );
			// 
			// gfx.DrawRectAlpha( padding + x * tileSize,y * tileSize,
			// 	tileSize,tileSize,
			// 	lightMap[y * size + x].first,
			// 	lightMap[y * size + x].second );
			const auto color = Colors::Interpolate(
				tiles[y * size + x],lightMap[y * size + x].first,
				lightMap[y * size + x].second );
			gfx.DrawRect( padding + x * tileSize,y * tileSize,
				tileSize,tileSize,
				color );
		}
	}
}

void TileMap::PutPixel( int x,int y,Color c )
{
	if( x >= 0 && x < size &&
		y >= 0 && y < size )
	{
		tiles[y * size + x] = c;
	}
}

void TileMap::PutLight( int x,int y,Color c,float val )
{
	if( x >= 0 && x < size &&
		y >= 0 && y < size &&
		val > 0.0f )
	{
		assert( val <= 1.0f );
		auto& item = lightMap[y * size + x];
		item.first = Colors::Interpolate( item.first,c,0.5f );
		item.second = ( item.second + val ) / 2.0f;
	}
}

// void TileMap::DrawLightRect( int x,int y,int width,int height,Color c,float val )
// {
// 	for( int yy = y; yy < y + height; ++yy )
// 	{
// 		for( int xx = x; xx < x + width; ++xx )
// 		{
// 			PutLight( xx,yy,c,val );
// 		}
// 	}
// }
// 
// void TileMap::DrawLightCircle( int x,int y,int size,const ColorStyle& cs )
// {
// 	const auto diffSq = size * size;
// 	for( int yy = y - size; yy <= y + size; ++yy )
// 	{
// 		for( int xx = x - size; xx <= x + size; ++xx )
// 		{
// 			const auto xDiff = xx - x;
// 			const auto yDiff = yy - y;
// 			if( xDiff * xDiff + yDiff * yDiff <= diffSq )
// 			{
// 				PutLight( xx,yy,cs.Generate(),1.0f );
// 			}
// 		}
// 	}
// }

void TileMap::Reset()
{
	for( auto& tile : tiles )
	{
		tile = Colors::Black;
	}
	for( auto& light : lightMap )
	{
		light.first = Colors::Black;
		light.second = globalBrightness;
	}
}

Color TileMap::GetPixel( int x,int y ) const
{
	return( tiles[y * size + x] );
}
