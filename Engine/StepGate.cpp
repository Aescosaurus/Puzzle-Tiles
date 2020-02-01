#include "StepGate.h"

StepGate::StepGate( const Vei2& pos )
	:
	LevelObject( pos,style.Generate() )
{}

void StepGate::Update( UpdateInfo& info )
{
	const auto& playerPos = info.player.GetPos();
	if( playerPos + Vei2::Up() == pos ||
		playerPos + Vei2::Down() == pos ||
		playerPos + Vei2::Left() == pos ||
		playerPos + Vei2::Right() == pos )
	{
		bool isTrigger = true;
		for( const auto& gate : info.levelObjects[int( Type::StepGate )] )
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
			for( auto& gate : info.levelObjects[int( Type::StepGate )] )
			{
				gate->Destroy();
			}
		}
	}
}
