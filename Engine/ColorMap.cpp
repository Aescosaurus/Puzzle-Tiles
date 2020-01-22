#include "ColorMap.h"

void ColorMap::Draw( const Vei2& pos,TileMap& tilemap ) const
{
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			// tilemap.PutPixel( pos.x + x,pos.y + y,
			// 	colors[y * width + x] );
			tilemap.PutLight( pos.x + offset.x + x,
				pos.y + offset.y + y,
				colors[y * width + x],lights[y * width + x] );
		}
	}
}

ColorMap ColorMap::CreateCircle( int radius,const ColorStyle& cs,
	float fallOff )
{
	ColorMap temp;
	temp.width = radius * 2 + 1;
	temp.height = radius * 2 + 1;
	temp.offset = -Vei2{ radius,radius };
	temp.colors.reserve( temp.width * temp.height );
	temp.lights.reserve( temp.width * temp.height );
	const auto diffSq = radius * radius;
	const Vei2 center = Vei2{ radius,radius };
	for( int y = 0; y < temp.height; ++y )
	{
		for( int x = 0; x < temp.width; ++x )
		{
			const auto xDiff = x - center.x;
			const auto yDiff = y - center.y;
			const auto curDiff = xDiff * xDiff + yDiff * yDiff;
			float light = 0.0f;
			if( curDiff <= diffSq )
			{
				light = 1.0f;
				light -= float( curDiff ) * fallOff;
			}
			// temp.lights[y * temp.width + x] = light;
			// temp.colors[y * temp.width + x] = cs.Generate();
			temp.lights.emplace_back( light );
			temp.colors.emplace_back( cs.Generate() );
		}
	}
	return( temp );
}
