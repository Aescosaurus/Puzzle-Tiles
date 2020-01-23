#include "Door.h"

Door::Door( const Vei2& pos )
	:
	LevelObject( pos )
{}

void Door::Draw( TileMap& tilemap ) const
{
	tilemap.PutPixel( pos.x,pos.y,Colors::Cyan );
}
