#include "Lantern.h"

Lantern::Lantern( const Vei2& pos )
	:
	LevelObject( pos ),
	colMap( ColorMap::CreateCircle( lightRadius,style,0.2f ) )
{
	SetVisible();
}

void Lantern::Update( UpdateInfo& info )
{
	for( auto& arrow : *info.arrows )
	{
		if( arrow->GetPos() == pos )
		{
			Light( info );
			arrow->Destroy();
		}
	}
}

void Lantern::Draw( TileMap& map ) const
{
	map.PutPixel( pos.x,pos.y,Colors::Orange );

	if( lit )
	{
		// map.DrawLightCircle( pos.x,pos.y,5,
		// 	Colors::MakeRGB( 240,190,110 ),0.5f );
		// map.DrawLightCircle( pos.x,pos.y,5,style );
		colMap.Draw( pos,map );
	}
}

void Lantern::Light( UpdateInfo& info )
{
	lit = true;

	SetItemVisible( *info.door );
	SetArrVisible( info.arrows );
	SetArrVisible( info.lanterns );
	SetArrVisible( info.basicGates );
}

void Lantern::SetArrVisible( PLevelObjectArr* arr ) const
{
	for( auto& item : *arr )
	{
		SetItemVisible( *item );
	}
}

void Lantern::SetItemVisible( LevelObject& item ) const
{
	static constexpr int radSq = lightRadius * lightRadius;
	if( ( item.GetPos() - pos ).GetLengthSq() <= radSq )
	{
		item.SetVisible();
	}
}
