#include "Player.h"

Player::Player( const Vei2& pos,const Level& level )
	:
	pos( pos ),
	level( level )
{}

void Player::Update( const Keyboard& kbd,const Mouse& mouse,float dt )
{
	auto vel = Vei2::Zero();
	if( kbd.KeyIsPressed( 'W' ) ) --vel.y;
	if( kbd.KeyIsPressed( 'S' ) ) ++vel.y;
	if( kbd.KeyIsPressed( 'A' ) ) --vel.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++vel.x;

	if( vel != Vei2::Zero() )
	{
		if( canMove )
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

	// const auto testMove = Vec2( vel ).GetNormalized() * speed * dt;
	// const auto testX = Vei2( pos + testMove.X() );
	// const auto testY = Vei2( pos + testMove.Y() );
	// if( level.GetTile( testX ) != Level::TileType::Wall )
	// {
	// 	pos += testMove.X();
	// }
	// if( level.GetTile( testY ) != Level::TileType::Wall )
	// {
	// 	pos += testMove.Y();
	// }

	// if( refire.Update( dt ) && mouse.LeftIsPressed() )
	// {
	// 	refire.Reset();
	// 	arrows.emplace_back( Arrow{ pos,mouse.GetPos() } );
	// }
	Vei2 shotVel = Vei2::Zero();
	if( kbd.KeyIsPressed( VK_UP ) ) --shotVel.y;
	if( kbd.KeyIsPressed( VK_DOWN ) ) ++shotVel.y;
	if( kbd.KeyIsPressed( VK_LEFT ) ) --shotVel.x;
	if( kbd.KeyIsPressed( VK_RIGHT ) ) ++shotVel.x;
	if( refire.Update( dt ) && shotVel != Vei2::Zero() )
	{
		refire.Reset();
		arrows.emplace_back( Arrow{ pos,pos + shotVel } );
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