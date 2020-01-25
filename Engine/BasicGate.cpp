#include "BasicGate.h"

BasicGate::BasicGate( const Vei2& pos )
	:
	LevelObject( pos ),
	col( style.Generate() )
{}

void BasicGate::Update( UpdateInfo& info )
{
	for( auto& arrow : *info.arrows )
	{
		if( arrow->GetPos() == pos )
		{
			arrow->Destroy();
			bool isTrigger = true;
			for( const auto& gate : *info.basicGates )
			{
				const auto& gatePos = gate->GetPos();
				if( gatePos == pos + Vei2::Up() ||
					gatePos == pos + Vei2::Down() ||
					gatePos == pos + Vei2::Left() ||
					gatePos == pos + Vei2::Right() )
				{
					isTrigger = false;
					break;
				}
			}
			if( isTrigger )
			{
				info.basicGates->clear();
			}
		}
	}
}

void BasicGate::Draw( TileMap& tilemap ) const
{
	tilemap.PutPixel( pos.x,pos.y,col );
}
