#include "Lantern.h"

Lantern::Lantern( const Vei2& pos )
	:
	LevelObject( pos,tileStyle.Generate(),true ),
	colMap( ColorMap::CreateCircle( lightRadius,mapStyle,0.2f ) )
{}

void Lantern::Update( UpdateInfo& info )
{
	for( auto& arrow : info.levelObjects[int( Type::Arrow )] )
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
	// map.PutPixel( pos.x,pos.y,Colors::Orange );
	LevelObject::Draw( map );

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

	static constexpr int radSq = lightRadius * lightRadius;
	for( auto& vec : info.levelObjects )
	{
		for( auto& obj : vec )
		{
			if( ( obj->GetPos() - pos ).GetLengthSq() <= radSq )
			{
				obj->SetVisible();
			}
		}
	}
}
