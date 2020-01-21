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

	const auto testMove = Vec2( vel ).GetNormalized() * speed * dt;
	const auto testX = Vei2( pos + testMove.X() );
	const auto testY = Vei2( pos + testMove.Y() );
	if( level.GetTile( testX ) != Level::TileType::Wall )
	{
		pos += testMove.X();
	}
	if( level.GetTile( testY ) != Level::TileType::Wall )
	{
		pos += testMove.Y();
	}

	if( mouse.LeftIsPressed() )
	{
		arrows.emplace_back( Arrow{ pos,mouse.GetPos() } );
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