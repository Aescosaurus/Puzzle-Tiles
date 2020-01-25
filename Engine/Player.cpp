#include "Player.h"

Player::Player( const Vei2& pos,const Level& level )
	:
	LevelObject( pos ),
	level( level )
{}

void Player::Update( UpdateInfo& info )
{
	auto vel = Vei2::Zero();
	if( info.kbd->KeyIsPressed( 'W' ) ) --vel.y;
	if( info.kbd->KeyIsPressed( 'S' ) ) ++vel.y;
	if( info.kbd->KeyIsPressed( 'A' ) ) --vel.x;
	if( info.kbd->KeyIsPressed( 'D' ) ) ++vel.x;

	if( vel != Vei2::Zero() )
	{
		// TODO: Let player move on top of door.
		if( canMove && level.GetTile( pos + vel ) !=
			Level::TileType::Wall && CheckPos( pos + vel,info ) )
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
	if( info.kbd->KeyIsPressed( VK_UP ) ) --shotVel.y;
	if( info.kbd->KeyIsPressed( VK_DOWN ) ) ++shotVel.y;
	if( info.kbd->KeyIsPressed( VK_LEFT ) ) --shotVel.x;
	if( info.kbd->KeyIsPressed( VK_RIGHT ) ) ++shotVel.x;
	if( refire.Update( info.dt ) && shotVel != Vei2::Zero() )
	{
		refire.Reset();
		// arrows.emplace_back( Arrow{ pos,shotVel } );
		arrows.emplace_back( std::make_unique<Arrow>(
			pos,shotVel ) );
	}

	// for( auto& arrow : arrows )
	// {
	// 	arrow->Update( dt );
	// }
}

void Player::Draw( TileMap& map ) const
{
	map.PutPixel( int( pos.x ),int( pos.y ),Colors::White );

	for( const auto& arrow : arrows )
	{
		arrow->Draw( map );
	}
}

// void Player::SetPos( const Vei2& pos )
// {
// 	this->pos = pos;
// }
// 
// const Vei2& Player::GetPos() const
// {
// 	return( pos );
// }

PLevelObjectArr& Player::GetArrows()
{
	return( arrows );
}
