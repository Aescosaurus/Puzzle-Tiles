#include "Gameplay.h"
#include "ChiliUtils.h"
#include <fstream>

Gameplay::Gameplay( const Keyboard& kbd,TileMap& tilemap )
	:
	kbd( kbd ),
	tilemap( tilemap ),
	guy( Vei2{ 0,0 },level ),
	arrows( guy.GetArrows() ),
	door( Vei2{ 0,0 } )
{
	updateInfo.arrows = &arrows;
	updateInfo.basicGates = &basicGates;

	Load( "Levels/_TestLevel.txt" );
	// enemies.emplace_back( Enemy{ Vei2{ 5,5 } } );
	// for( int i = 0; i < 4; ++i )
	// {
	// 	lanterns.emplace_back( Lantern{ level.GetValidSpot() } );
	// }
}

void Gameplay::Update()
{
	const auto dt = ft.Mark();
	updateInfo.dt = dt;

	guy.Update( kbd,dt );

	for( auto& arrow : arrows )
	{
		arrow->Update( updateInfo );
	}

	for( auto& lantern : lanterns )
	{
		lantern->Update( updateInfo );
	}

	for( auto& gate : basicGates )
	{
		gate->Update( updateInfo );
	}

	// TODO: Level Objects are only visible if light is on them.
	// TODO: Destroy arrows once they exit the screen.
	// TODO: Optimize DrawRectAlpha but in tilemap.
	// TODO: Exit loads next level.
	// TODO: Player can't walk on top of lanterns and such.

	const auto isDestroyed = std::mem_fn( &LevelObject::IsDestroyed );
	chili::remove_erase_if( arrows,isDestroyed );
	chili::remove_erase_if( lanterns,isDestroyed );
	// chili::remove_erase_if( enemies,isDestroyed );
}

void Gameplay::Draw()
{
	level.Draw( tilemap );
	guy.Draw( tilemap );

	// for( const auto& enemy : enemies )
	// {
	// 	enemy.Draw( tilemap );
	// }

	for( const auto& lantern : lanterns )
	{
		lantern->Draw( tilemap );
	}

	for( const auto& gate : basicGates )
	{
		gate->Draw( tilemap );
	}

	door.Draw( tilemap );
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
		case '1':
			floorVal = 1;
			break;
		case 'p':
			guy.SetPos( pos );
			floorVal = 1;
			break;
		case 'd':
			door.SetPos( pos );
			floorVal = 1;
			break;
		case 'g':
			basicGates.emplace_back( std::make_unique<BasicGate>( pos ) );
			floorVal = 1;
			break;
		case 'l':
			// lanterns.emplace_back( Lantern{ pos } );
			lanterns.emplace_back( std::make_unique<Lantern>( pos ) );
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
