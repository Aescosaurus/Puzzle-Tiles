#include "Arrow.h"

Arrow::Arrow( const Vei2& pos,const Vei2& vel )
	:
	LevelObject( pos ),
	vel( vel ),
	cs( Colors::MakeRGB( 200,200,140 ),20,false,pos,0.2f )
{}

void Arrow::Update( float dt )
{
	if( moveSpeed.Update( dt ) )
	{
		moveSpeed.Reset();
		pos += vel;
		cs.pos = pos;
	}
}

void Arrow::Draw( TileMap& tilemap ) const
{
	tilemap.PutPixel( int( pos.x ),int( pos.y ),Colors::Yellow );

	// tilemap.DrawLightCircle( pos.x,pos.y,2,
	// 	Colors::MakeRGB( 200,200,140 ),0.5f );
	tilemap.DrawLightCircle( pos.x,pos.y,2,cs );
}
