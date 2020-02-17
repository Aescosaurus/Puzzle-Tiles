#include "AutoShooter.h"
#include "Arrow.h"
#include <cassert>

AutoShooter::AutoShooter( const Vei2& pos )
	:
	LevelObject( pos,style.Generate() ),
	dir( CalcDir( pos ) )
{}

void AutoShooter::Update( UpdateInfo& info )
{
	if( info.player.GetPos() != oldPlayerPos )
	{
		info.levelObjects[int( Type::Arrow )].emplace_back(
			std::make_unique<Arrow>( pos,dir ) );
		info.levelObjects[int( Type::Arrow )].back()
			->Update2( info );
		hitSounds[curSound]->Play( 0.3f );
	}
	oldPlayerPos = info.player.GetPos();
}

Vei2 AutoShooter::CalcDir( const Vei2& pos )
{
	Vei2 vel = Vei2::Zero();

	const int xMod = pos.x % 2;
	const int yMod = pos.y % 2;

	if( yMod == 0 )
	{
		vel.y = xMod * 2 - 1;
		curSound = vel.y;
	}
	else /*if ymod == 1*/
	{
		vel.x = xMod * 2 - 1;
		curSound = vel.x + 2;
	}

	return( vel );
}
