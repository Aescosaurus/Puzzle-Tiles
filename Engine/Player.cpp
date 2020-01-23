#include "Player.h"

Player::Player( const Vei2& pos,const Level& level )
	:
	pos( pos ),
	level( level )
{}

void Player::Update( const Keyboard& kbd,float dt )
{
	auto vel = Vei2::Zero();
	if( kbd.KeyIsPressed( 'W' ) ) --vel.y;
	if( kbd.KeyIsPressed( 'S' ) ) ++vel.y;
	if( kbd.KeyIsPressed( 'A' ) ) --vel.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++vel.x;

	if( vel != Vei2::Zero() )
	{
		if( canMove && level.GetTile( pos + vel ) !=
			Level::TileType::Wall )
		{
			if( vel.x != 0 ) pos += vel.X();
			else pos += vel.Y();
			canMove = false;
		}
	}
	else
	{
		canMove = true;
	}

	Vei2 shotVel = Vei2::Zero();
	if( kbd.KeyIsPressed( VK_UP ) ) --shotVel.y;
	if( kbd.KeyIsPressed( VK_DOWN ) ) ++shotVel.y;
	if( kbd.KeyIsPressed( VK_LEFT ) ) --shotVel.x;
	if( kbd.KeyIsPressed( VK_RIGHT ) ) ++shotVel.x;
	if( refire.Update( dt ) && shotVel != Vei2::Zero() )
	{
		refire.Reset();
		arrows.emplace_back( Arrow{ pos,shotVel } );
	}

	for( auto& arrow : arrows )
	{
		arrow.Update( dt );
	}
}

void Player::Draw( TileMap& map ) const
{
	map.PutPixel( int( pos.x ),int( pos.y ),Colors::White );

	for( const auto& arrow : arrows )
	{
		arrow.Draw( map );
	}
}

void Player::SetPos( const Vei2& pos )
{
	this->pos = pos;
}

const Vei2& Player::GetPos() const
{
	return( pos );
}

std::vector<Arrow>& Player::GetArrows()
{
	return( arrows );
}
