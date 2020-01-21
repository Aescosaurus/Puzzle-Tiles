#include "Arrow.h"

Arrow::Arrow( const Vei2& pos,const Vei2& vel )
	:
	pos( pos ),
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
}

void Arrow::Destroy()
{
	destroyed = true;
}

Vei2 Arrow::GetPos()
{
	return( pos );
}

bool Arrow::IsDestroyed() const
{
	return( destroyed );
}
