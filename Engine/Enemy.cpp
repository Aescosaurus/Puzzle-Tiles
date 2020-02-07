#include "Enemy.h"

Enemy::Enemy( const Vei2& pos )
	:
	LevelObject( pos,style.Generate() )
{}

void Enemy::Update( UpdateInfo& info )
{
	if( info.player.GetPos() != playerPos )
	{
		Update2( info );
	}
}

void Enemy::Update2( UpdateInfo& info )
{
	playerPos = info.player.GetPos();

	const auto testPos = pos + Vei2::Right() * dir;
	if( info.level.GetTile( testPos ) != Level::TileType::Wall &&
		CheckPos( testPos,info ) )
	{
		pos = testPos;
	}
	else
	{
		dir *= -1;
		Update2( info );
	}
}
