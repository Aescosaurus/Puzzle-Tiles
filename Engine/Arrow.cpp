#include "Arrow.h"

Arrow::Arrow( const Vei2& pos,const Vei2& vel )
	:
	LevelObject( pos,cs.Generate(),true ),
	vel( vel ),
	colMap( ColorMap::CreateCircle( lightArea,cs,0.1f ) )
{}

void Arrow::Update( UpdateInfo& info )
{
	if( moveSpeed.Update( info.dt ) )
	{
		moveSpeed.Reset2();
		pos += vel;

		static constexpr auto lenSq = lightArea * lightArea;
		for( auto& vec : info.levelObjects )
		{
			for( auto& item : vec )
			{
				if( ( item->GetPos() - pos ).GetLengthSq() <= lenSq )
				{
					item->SetVisible();
				}
			}
		}
	}

	if( !Graphics::ScreenRect.GetExpanded( lightArea )
		.ContainsPoint( pos ) )
	{
		Destroy();
	}
}

void Arrow::Draw( TileMap& tilemap ) const
{
	// tilemap.PutPixel( int( pos.x ),int( pos.y ),Colors::Yellow );
	LevelObject::Draw( tilemap );

	// tilemap.DrawLightCircle( pos.x,pos.y,2,
	// 	Colors::MakeRGB( 200,200,140 ),0.5f );
	// tilemap.DrawLightCircle( pos.x,pos.y,2,cs );
	colMap.Draw( pos,tilemap );
}
