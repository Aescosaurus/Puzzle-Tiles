#include "Lantern.h"

Lantern::Lantern( const Vei2& pos )
	:
	LevelObject( pos ),
	style( Colors::MakeRGB( 240,190,110 ),10,false ),
	colMap( ColorMap::CreateCircle( 5,style,0.2f ) )
{}

void Lantern::Update( UpdateInfo& info )
{
	for( auto& arrow : *info.arrows )
	{
		if( arrow->GetPos() == pos )
		{
			Light();
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

void Lantern::Light()
{
	lit = true;
}
