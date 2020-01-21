#include "Lantern.h"

Lantern::Lantern( const Vei2& pos )
	:
	LevelObject( pos )
{}

void Lantern::Draw( TileMap& map ) const
{
	map.PutPixel( pos.x,pos.y,Colors::Orange );

	if( lit )
	{
		map.DrawLightCircle( pos.x,pos.y,5,
			Colors::MakeRGB( 240,190,110 ),0.5f );
	}
}

void Lantern::Light()
{
	lit = true;
}
