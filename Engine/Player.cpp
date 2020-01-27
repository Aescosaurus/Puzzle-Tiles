#include "Player.h"
#include "Lantern.h"

Player::Player( const Vei2& pos,const Level& level,
	PLevelObjectArr& arrows )
	:
	LevelObject( pos,Colors::White,true ),
	level( level ),
	arrows( arrows )
{}

void Player::Update( UpdateInfo& info )
{
	auto vel = Vei2::Zero();
	if( info.kbd.KeyIsPressed( 'W' ) ) --vel.y;
	if( info.kbd.KeyIsPressed( 'S' ) ) ++vel.y;
	if( info.kbd.KeyIsPressed( 'A' ) ) --vel.x;
	if( info.kbd.KeyIsPressed( 'D' ) ) ++vel.x;

	if( vel != Vei2::Zero() )
	{
		if( CanMove( pos + vel,info ) )
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
	if( info.kbd.KeyIsPressed( VK_UP ) ) --shotVel.y;
	if( info.kbd.KeyIsPressed( VK_DOWN ) ) ++shotVel.y;
	if( info.kbd.KeyIsPressed( VK_LEFT ) ) --shotVel.x;
	if( info.kbd.KeyIsPressed( VK_RIGHT ) ) ++shotVel.x;
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
	// map.PutPixel( int( pos.x ),int( pos.y ),Colors::White );
	LevelObject::Draw( map );

	for( const auto& arrow : arrows )
	{
		arrow->Draw( map );
	}
}

bool Player::CanMove( const Vei2& loc,UpdateInfo& info ) const
{
	bool overlapsLight = false;
	for( auto& lantern : info.levelObjects[int( Type::Lantern )] )
	{
		if( ( loc - lantern->GetPos() ).GetLengthSq() <=
			Lantern::lightRadius * Lantern::lightRadius &&
			lantern->IsLit() )
		{
			overlapsLight = true;
			break;
		}
	}

	return( canMove &&
		level.GetTile( loc ) != Level::TileType::Wall &&
		( CheckPos( loc,info ) || loc == info.door.GetPos() ) &&
		overlapsLight );
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

// PLevelObjectArr& Player::GetArrows()
// {
// 	return( arrows );
// }
