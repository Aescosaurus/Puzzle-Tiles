#include "Turret.h"
#include "Arrow.h"

Turret::Turret( const Vei2& pos )
	:
	LevelObject( pos,style.Generate() )
{}

void Turret::Update( UpdateInfo& info )
{
	auto& arrowArr = info.levelObjects[int( Type::Arrow )];
	for( auto& arrow : arrowArr )
	{
		if( arrow->GetPos() == pos )
		{
			arrow->Destroy();
			arrowArr.emplace_back( std::make_unique<Arrow>(
				pos + dir,dir ) );

			// Rotate direction right.
			dir.y *= -1;
			std::swap( dir.x,dir.y );
			break;
		}
	}
}
