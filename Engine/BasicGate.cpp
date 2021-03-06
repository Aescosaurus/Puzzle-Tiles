#include "BasicGate.h"

BasicGate::BasicGate( const Vei2& pos )
	:
	LevelObject( pos,styles[0].Generate() )
{}

void BasicGate::Update( UpdateInfo& info )
{
	for( auto& arrow : info.levelObjects[int( Type::Arrow )] )
	{
		if( arrow->GetPos() == pos )
		{
			arrow->Destroy();
			bool isTrigger = true;
			for( const auto& gate : info.levelObjects[int( Type::BasicGate )] )
			{
				const auto& gatePos = gate->GetPos();
				if( gatePos == pos + Vei2::Up() ||
					gatePos == pos + Vei2::Down() ||
					gatePos == pos + Vei2::Left() ||
					gatePos == pos + Vei2::Right() )
				{
					isTrigger = false;
					hitSound->Play( 0.5f );
					break;
				}
			}
			if( isTrigger )
			{
				openSound->Play( 0.8f );
				// info.levelObjects[int( Type::BasicGate )].clear();
				for( auto& gate : info.levelObjects[int( Type::BasicGate )] )
				{
					gate->Destroy();
				}
			}
		}
	}
}
