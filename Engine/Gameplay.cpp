#include "Gameplay.h"
#include "ChiliUtils.h"
#include <fstream>

Gameplay::Gameplay( const Keyboard& kbd,TileMap& tilemap )
	:
	kbd( kbd ),
	tilemap( tilemap ),
	updateInfo{ kbd,0.0f,guy,door,levelObjects },
	levelObjects{ int( LevelObject::Type::Max ) },
	guy( Vei2{ 0,0 },level,levelObjects[int( LevelObject::Type::Arrow )] ),
	door( Vei2{ 0,0 } )
{
	Load( "Levels/_TestLevel.txt" );
}

void Gameplay::Update()
{
	const auto dt = ft.Mark();
	updateInfo.dt = dt;

	guy.Update( updateInfo );

	for( auto& vec : levelObjects )
	{
		for( auto& levelObject : vec )
		{
			levelObject->Update( updateInfo );
		}
	}

	// TODO: Exit loads next level.
	// TODO: Some test levels.

	const auto isDestroyed = std::mem_fn( &LevelObject::IsDestroyed );
	for( auto& vec : levelObjects )
	{
		chili::remove_erase_if( vec,isDestroyed );
	}
}

void Gameplay::Draw()
{
	level.Draw( tilemap );
	guy.Draw( tilemap );
	
	for( auto& vec : levelObjects )
	{
		for( auto& levelObject : vec )
		{
			levelObject->Draw( tilemap );
		}
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
		case 'l':
			levelObjects[int( LevelObject::Type::Lantern )].emplace_back(
				std::make_unique<Lantern>( pos ) );
			floorVal = 1;
			break;
		case 'r':
			levelObjects[int( LevelObject::Type::BasicGate )].emplace_back(
				std::make_unique<BasicGate>( pos,BasicGate::GateType::Red ) );
			floorVal = 1;
			break;
		case 'i':
			levelObjects[int( LevelObject::Type::BasicGate )].emplace_back(
				std::make_unique<BasicGate>( pos,BasicGate::GateType::Pink ) );
			floorVal = 1;
			break;
		case 'u':
			levelObjects[int( LevelObject::Type::BasicGate )].emplace_back(
				std::make_unique<BasicGate>( pos,BasicGate::GateType::Purple ) );
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
