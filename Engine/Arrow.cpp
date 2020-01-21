#include "Arrow.h"

Arrow::Arrow( const Vei2& pos,const Vei2& vel )
	:
	LevelObject( pos ),
	vel( vel )
{}

void Arrow::Update( float dt )
{
	if( moveSpeed.Update( dt ) )
	{
		moveSpeed.Reset();
		pos += vel;
	}
}

void Arrow::Draw( TileMap& tilemap ) const
{
	tilemap.PutPixel( int( pos.x ),int( pos.y ),Colors::Yellow );

	// tilemap.DrawLightRect( pos.x - 1,pos.y - 1,3,3,
	// 	Colors::MakeRGB( 190,190,120 ),0.5f );
	tilemap.DrawLightCircle( pos.x,pos.y,2,
		Colors::MakeRGB( 200,200,140 ),0.5f );
}
