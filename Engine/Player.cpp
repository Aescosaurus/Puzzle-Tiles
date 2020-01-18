#include "Player.h"

Player::Player( const Vei2& pos,const Level& level )
	:
	pos( pos ),
	flashlight( level )
{}

void Player::Update( const Keyboard& kbd,const Mouse& mouse,float dt )
{
	auto vel = Vei2::Zero();
	if( kbd.KeyIsPressed( 'W' ) ) --vel.y;
	if( kbd.KeyIsPressed( 'S' ) ) ++vel.y;
	if( kbd.KeyIsPressed( 'A' ) ) --vel.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++vel.x;

	pos += Vec2( vel ).GetNormalized() * speed;

	flashlight.Update( pos,Vec2( mouse.GetPos() ) );
}

void Player::Draw( TileMap& map ) const
{
	map.PutPixel( int( pos.x ),int( pos.y ),Colors::White );
}

void Player::DrawFlashlight( TileMap& map ) const
{
	flashlight.Draw( map );
}
