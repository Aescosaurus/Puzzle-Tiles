#include "Arrow.h"

Arrow::Arrow( const Vei2& pos,const Vei2& vel )
	:
	LevelObject( pos ),
	vel( vel ),
	colMap( ColorMap::CreateCircle( lightArea,cs,0.1f ) )
{}

void Arrow::Update( UpdateInfo& info )
{
	if( moveSpeed.Update( info.dt ) )
	{
		moveSpeed.Reset();
		pos += vel;
	}

	if( !Graphics::ScreenRect.GetExpanded( lightArea )
		.ContainsPoint( pos ) )
	{
		Destroy();
	}
}

void Arrow::Draw( TileMap& tilemap ) const
{
	tilemap.PutPixel( int( pos.x ),int( pos.y ),Colors::Yellow );

	// tilemap.DrawLightCircle( pos.x,pos.y,2,
	// 	Colors::MakeRGB( 200,200,140 ),0.5f );
	// tilemap.DrawLightCircle( pos.x,pos.y,2,cs );
	colMap.Draw( pos,tilemap );
}
