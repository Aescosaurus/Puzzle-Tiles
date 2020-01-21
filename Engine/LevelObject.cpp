#include "LevelObject.h"

LevelObject::LevelObject( const Vei2& pos )
	:
	pos( pos )
{}

void LevelObject::Destroy()
{
	destroyed = true;
}

const Vei2& LevelObject::GetPos()
{
	return( pos );
}

bool LevelObject::IsDestroyed() const
{
	return( destroyed );
}
