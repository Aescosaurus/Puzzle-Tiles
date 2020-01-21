#include "Enemy.h"

Enemy::Enemy( const Vei2& pos )
	:
	pos( pos )
{}

void Enemy::Update( const Vei2& playerPos,float dt )
{
	if( moveTimer.Update( dt ) )
	{
		moveTimer.Reset();
		const auto diff = playerPos - pos;
		if( std::abs( diff.x ) > std::abs( diff.y ) )
		{
			if( diff.x > 0 ) ++pos.x;
			else --pos.y;
		}
		else
		{
			if( diff.y > 0 ) ++pos.y;
			else --pos.y;
		}
	}
}

void Enemy::Draw( TileMap& map ) const
{
	map.PutPixel( pos.x,pos.y,Colors::Red );
}

void Enemy::Destroy()
{
	destroyed = true;
}

const Vei2& Enemy::GetPos() const
{
	return( pos );
}

bool Enemy::IsDestroyed() const
{
	return( destroyed );
}
