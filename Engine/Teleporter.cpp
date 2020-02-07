#include "Teleporter.h"

Teleporter::Teleporter( const Vei2& pos )
	:
	LevelObject( pos,style.Generate() )
{}

void Teleporter::Update( UpdateInfo& info )
{
	for( auto& arrow : info.levelObjects[int( Type::Arrow )] )
	{
		if( arrow->GetPos() == pos )
		{
			auto& teleporters = info.levelObjects[int( Type::Teleporter )];
			// for( auto& tele : info.levelObjects[int( Type::Teleporter )] )
			// for( int i = 0; i < int( teleporters.size() ); ++i )
			for( int i = 0; i < int( teleporters.size() ); ++i )
			{
				const auto& tele = teleporters[i];
				if( tele.get() == this )
				{
					++i;
					if( i >= int( teleporters.size() ) ) i = 0;
					arrow->SetPos( teleporters[i]->GetPos() );
					break;
				}
			}
		}
	}
}
