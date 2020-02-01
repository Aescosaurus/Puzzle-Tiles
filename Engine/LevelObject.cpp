#include "LevelObject.h"

LevelObject::LevelObject( const Vei2& pos,Color col,bool visible )
	:
	pos( pos ),
	col( col ),
	visible( visible )
{
	flashDuration.Update( 9999.0f );
}

void LevelObject::BaseUpdate( UpdateInfo& info )
{
	Update( info );

	flashDuration.Update( info.dt );
}

void LevelObject::Draw( TileMap& map ) const
{
	// if( visible )
	{
		map.PutPixel( pos.x,pos.y,Colors::Interpolate(
			Colors::White,col,flashDuration.GetPercent() ) );
	}
}

void LevelObject::Destroy()
{
	destroyed = true;
}

void LevelObject::SetPos( const Vei2& pos )
{
	this->pos = pos;
}

void LevelObject::SetVisible()
{
	visible = true;
}

void LevelObject::StartFlash()
{
	flashDuration.Reset();
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
	if( info.player.GetPos() == pos ) return( false );
	if( info.door.GetPos() == pos ) return( false );

	// if( !IsEmpty( pos,info.arrows ) ) return( false );
	// if( !IsEmpty( pos,info.lanterns ) ) return( false );
	// if( !IsEmpty( pos,info.basicGates ) ) return( false );
	for( auto& vec : info.levelObjects )
	{
		for( auto& item : vec )
		{
			if( item->GetPos() == pos ) return( false );
		}
	}

	return( true );
}

bool LevelObject::IsVisible() const
{
	return( visible );
}

bool LevelObject::IsLit() const
{
	return( false );
}
