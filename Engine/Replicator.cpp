#include "Replicator.h"
#include "Arrow.h"

Replicator::Replicator( const Vei2& pos )
	:
	LevelObject( pos,style.Generate() )
{}

void Replicator::Update( UpdateInfo& info )
{
	auto& arrowArr = info.levelObjects[int( Type::Arrow )];
	for( auto& arrow : arrowArr )
	{
		if( arrow->GetPos() == pos )
		{
			arrow->Destroy();
			for( int i = 0; i < 4; ++i )
			{
				arrowArr.emplace_back( std::make_unique<Arrow>(
					pos,dirs[i] ) );
				arrowArr.back()->Update( info );
			}
		}
	}
}
