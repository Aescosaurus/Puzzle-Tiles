#include "Arrow.h"

Arrow::Arrow( const Vei2& pos,const Vei2& vel )
	:
	LevelObject( pos,cs.Generate(),true ),
	vel( vel ),
	colMap( ColorMap::CreateCircle( lightArea,cs,0.1f ) )
{
	assert( vel.x == 0 || vel.y == 0 );
	// moveSpeed.Update( moveSpeed.GetDuration() );
}

void Arrow::Update( UpdateInfo& info )
{
	if( moveSpeed.Update( info.dt ) )
	{
		Update2( info );
	}

	if( !Graphics::ScreenRect.GetExpanded( lightArea )
		.ContainsPoint( pos ) )
	{
		Destroy();
	}
}

void Arrow::Update2( UpdateInfo& info )
{
	moveSpeed.Reset2();
	pos += vel;

	for( int i = int( Type::Arrow ) + 1;
		i < int( info.levelObjects.size() );
		++i )
	{
		auto& vec = info.levelObjects[i];
		for( auto& obj : vec )
		{
			if( obj->GetPos() == pos )
			{
				obj->StartFlash();
			}
		}
	}
}

void Arrow::Draw( TileMap& tilemap ) const
{
	// tilemap.PutPixel( int( pos.x ),int( pos.y ),Colors::Yellow );
	LevelObject::Draw( tilemap );

	// tilemap.DrawLightCircle( pos.x,pos.y,2,
	// 	Colors::MakeRGB( 200,200,140 ),0.5f );
	// tilemap.DrawLightCircle( pos.x,pos.y,2,cs );
	// colMap.Draw( pos,tilemap );
}
