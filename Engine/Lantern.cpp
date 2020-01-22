#include "Lantern.h"

Lantern::Lantern( const Vei2& pos )
	:
	LevelObject( pos ),
	style( Colors::MakeRGB( 240,190,110 ),10,false,pos,0.8f )
{}

void Lantern::Draw( TileMap& map ) const
{
	map.PutPixel( pos.x,pos.y,Colors::Orange );

	if( lit )
	{
		// map.DrawLightCircle( pos.x,pos.y,5,
		// 	Colors::MakeRGB( 240,190,110 ),0.5f );
		map.DrawLightCircle( pos.x,pos.y,5,style );
	}
}

void Lantern::Light()
{
	lit = true;
}
