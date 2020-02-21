#include "Gameplay.h"
#include "ChiliUtils.h"
#include <fstream>

Gameplay::Gameplay( const Keyboard& kbd,TileMap& tilemap )
	:
	kbd( kbd ),
	tilemap( tilemap ),
	updateInfo{ kbd,0.0f,level,guy,door,levelObjects },
	levelObjects{ int( LevelObject::Type::Max ) },
	guy( Vei2{ 0,0 },level,levelObjects[int( LevelObject::Type::Arrow )] ),
	door( Vei2{ 0,0 } )
{
	const int saveLevel = ReadSave();
	while( curLevel < saveLevel )
	{
		++curLevel;
		std::ifstream in{ GenerateLevelName() };
		if( !in.good() )
		{
			--curLevel;
			break;
		}
	}
#if NDEBUG
	music->Play( 0.2f );
#endif
	Load( GenerateLevelName() );
}

Gameplay::~Gameplay()
{
	SoundCodex::Purge(); // Errors happen without this.. :(
}

void Gameplay::Update()
{
#if !NDEBUG
	if( kbd.KeyIsPressed( VK_RETURN ) )
	{
		if( canAdvanceLevel )
		{
			Load( GenerateLevelName() );
			canAdvanceLevel = false;
		}
	}
	else canAdvanceLevel = true;
#endif

	if( kbd.KeyIsPressed( 'R' ) )
	{
		--curLevel;
		Load( GenerateLevelName() );
	}

	const auto dt = ft.Mark();
	updateInfo.dt = dt;

	guy.Update( updateInfo );
	level.Update( dt );

	for( int i = 0; i < int( levelObjects.size() ); ++i )
	{
		auto& vec = levelObjects[i];
		for( auto& levelObject : vec )
		{
			levelObject->BaseUpdate( updateInfo );
			if( i != int( LevelObject::Type::Arrow ) )
			{
				for( auto& arrow : levelObjects[int( LevelObject::Type::Arrow )] )
				{
					if( arrow->GetPos() == levelObject->GetPos() )
					{
						arrow->Destroy();
					}
				}
			}
		}
	}

	if( guy.GetPos() == door.GetPos() )
	{
		exitSound->Play();
		Load( GenerateLevelName() );
		WriteSave();
	}

	// For Release:
	// TODO: New lantern sounds.
	// TODO: Puzzle requiring shooting through the door.
	// TODO: Slow fade in from black on the first level.
	// TODO: Last few levels.

	// Maybe in the future:
	// TODO: Instructions on the sidebars (left click/h for help).
	// TODO: Score based on number of moves?
	// TODO: Puzzle using arrows to block enemy movement?
	// TODO: Auto shooters have light indicating direction.
	// TODO: That goes for turrets too.
	// TODO: Player can loop across sides and top/bot of screen.
	// TODO: Lanterns that turn off when you hit them again.
	// TODO: Above but with different light pattern.

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
	for( auto& vec : levelObjects )
	{
		vec.clear();
	}

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
		case 'L':
			levelObjects[int( LevelObject::Type::Lantern )].emplace_back(
				std::make_unique<Lantern>( pos,true ) );
			floorVal = 1;
			break;
		case 'b':
			levelObjects[int( LevelObject::Type::BasicGate )].emplace_back(
				std::make_unique<BasicGate>( pos ) );
			floorVal = 1;
			break;
		case 's':
			levelObjects[int( LevelObject::Type::StepGate )].emplace_back(
				std::make_unique<StepGate>( pos ) );
			floorVal = 1;
			break;
		case 'r':
			levelObjects[int( LevelObject::Type::Replicator )].emplace_back(
				std::make_unique<Replicator>( pos ) );
			floorVal = 1;
			break;
		case 't':
			levelObjects[int( LevelObject::Type::Turret )].emplace_back(
				std::make_unique<Turret>( pos ) );
			floorVal = 1;
			break;
		case 'e': // Like tEleporter.
			levelObjects[int( LevelObject::Type::Teleporter )].emplace_back(
				std::make_unique<Teleporter>( pos ) );
			floorVal = 1;
			break;
		case 'n': // eNemy.
			levelObjects[int( LevelObject::Type::Enemy )].emplace_back(
				std::make_unique<Enemy>( pos ) );
			floorVal = 1;
			break;
		case 'a':
			levelObjects[int( LevelObject::Type::AutoShooter )].emplace_back(
				std::make_unique<AutoShooter>( pos ) );
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

	++curLevel;
}

int Gameplay::ReadSave() const
{
#if !NDEBUG
	return( 99999 ); // Skip to latest level in debug mode.
#else
	std::ifstream in{ "Save/SaveInfo.txt" };
	assert( in.good() );
	std::string info = "";
	for( char c = in.get(); in.good(); c = in.get() )
	{
		if( c != '\n' ) info += c;
	}
	return( std::stoi( info ) );
#endif
}

void Gameplay::WriteSave() const
{
	std::ofstream out{ "Save/SaveInfo.txt" };
	assert( out.good() );
	const auto levelStr = std::to_string( curLevel - 1 );
	out << levelStr;
}

std::string Gameplay::GenerateLevelName() const
{
	return( "Levels/Level" + std::to_string( curLevel ) + ".txt" );
}
