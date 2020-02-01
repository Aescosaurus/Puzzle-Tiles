#include "Shooter.h"
#include "Arrow.h"

Shooter::Shooter( const Vei2& pos,const Vei2& dir )
	:
	LevelObject( pos,style.Generate() ),
	dir( dir )
{}

void Shooter::Update( UpdateInfo& info )
{
	if( refire.Update( info.dt ) )
	{
		refire.Reset();
		info.levelObjects[int( Type::Arrow )].emplace_back(
			std::make_unique<Arrow>( pos,dir ) );
	}
}
