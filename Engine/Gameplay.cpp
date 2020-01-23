#include "Gameplay.h"
#include "ChiliUtils.h"
#include <fstream>

Gameplay::Gameplay( const Keyboard& kbd,TileMap& tilemap )
	:
	kbd( kbd ),
	tilemap( tilemap ),
	guy( Vei2{ 0,0 },level ),
	door( Vei2{ 0,0 } )
{
	Load( "Levels/Level1.txt" );
	// enemies.emplace_back( Enemy{ Vei2{ 5,5 } } );
	// for( int i = 0; i < 4; ++i )
	// {
	// 	lanterns.emplace_back( Lantern{ level.GetValidSpot() } );
	// }
}

void Gameplay::Update()
{
	const auto dt = ft.Mark();
	guy.Update( kbd,dt );

	auto& arrows = guy.GetArrows();

	const auto& playerPos = guy.GetPos();
	for( auto& enemy : enemies )
	{
		enemy.Update( playerPos,dt );

		for( auto& arrow : arrows )
		{
			if( arrow.GetPos() == enemy.GetPos() )
			{
				arrow.Destroy();
				enemy.Destroy();
				// tilemap.DrawLightRect( 0,0,
				// 	TileMap::size,TileMap::size,
				// 	Colors::White,0.9f );
			}
		}
	}

	for( auto& lantern : lanterns )
	{
		for( auto& arrow : arrows )
		{
			if( arrow.GetPos() == lantern.GetPos() )
			{
				arrow.Destroy();
				lantern.Light();
			}
		}
	}
	// TODO: Put stuff from game into functions in each object.
	// TODO: Abstract collision checking into level.canmove?
	// TODO: Upgrade everything applicable to use colormap.
	// TODO: Level Objects are only visible if light is on them.

	const auto isDestroyed = std::mem_fn( &LevelObject::IsDestroyed );
	chili::remove_erase_if( arrows,isDestroyed );
	chili::remove_erase_if( enemies,isDestroyed );
}

void Gameplay::Draw()
{
	level.Draw( tilemap );
	guy.Draw( tilemap );

	for( const auto& enemy : enemies )
	{
		enemy.Draw( tilemap );
	}

	for( const auto& lantern : lanterns )
	{
		lantern.Draw( tilemap );
	}
}

void Gameplay::Load( const std::string& levelName )
{
	std::ifstream in{ levelName };
	assert( in.good() );

	std::vector<int> tiles;

	Vei2 pos = Vei2::Zero();
	for( char c = in.get(); in.good(); c = in.get() )
	{
		int floorVal = -1;
		switch( c )
		{
		case '0':
			floorVal = 0;
			break;
		case 'p':
			guy.SetPos( pos );
			floorVal = 1;
			break;
		case 'd':
			door.SetPos( pos );
			floorVal = 1;
			break;
		case 'l':
			lanterns.emplace_back( Lantern{ pos } );
			floorVal = 1;
			break;
		case '1':
			floorVal = 1;
			break;
		case '\n':
			pos.x = -1;
			++pos.y;
			break;
		default:
			assert( false );
		}
		if( floorVal != -1 ) tiles.emplace_back( floorVal );
		++pos.x;
	}

	level.Load( tiles );
}
