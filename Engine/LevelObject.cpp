#include "LevelObject.h"

LevelObject::LevelObject( const Vei2& pos )
	:
	pos( pos )
{}

void LevelObject::Draw( TileMap& map ) const
{
	map.PutPixel( pos.x,pos.y,Colors::Magenta );
}

void LevelObject::Destroy()
{
	destroyed = true;
}

void LevelObject::SetPos( const Vei2& pos )
{
	this->pos = pos;
}

const Vei2& LevelObject::GetPos() const
{
	return( pos );
}

bool LevelObject::IsDestroyed() const
{
	return( destroyed );
}

bool LevelObject::CheckPos( const Vei2& pos,const UpdateInfo& info ) const
{
	if( info.player->GetPos() == pos ) return( false );
	if( info.door->GetPos() == pos ) return( false );

	if( !IsEmpty( pos,info.arrows ) ) return( false );
	if( !IsEmpty( pos,info.lanterns ) ) return( false );
	if( !IsEmpty( pos,info.basicGates ) ) return( false );

	return( true );
}

bool LevelObject::IsEmpty( const Vei2& pos,PLevelObjectArr* arr ) const
{
	for( auto& item : *arr )
	{
		if( item->GetPos() == pos ) return( false );
	}
	return( true );
}
