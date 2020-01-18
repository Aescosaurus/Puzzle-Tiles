#include "Flashlight.h"
#include "TileMap.h"

Flashlight::Flashlight( const Level& level )
	:
	level( level )
{
	flashArea.reserve( TileMap::size * TileMap::size );
	for( int y = 0; y < TileMap::size; ++y )
	{
		for( int x = 0; x < TileMap::size; ++x )
		{
			flashArea.emplace_back( 0.0f );
		}
	}
}

void Flashlight::Update( const Vec2& playerPos,const Vec2& mousePos )
{
	for( int y = 0; y < TileMap::size; ++y )
	{
		for( int x = 0; x < TileMap::size; ++x )
		{
			flashArea[y * TileMap::size + x] = 0.0f;
		}
	}

	const auto startAngle = ( mousePos - playerPos ).GetAngle();
	for( int col = 0; col < int( resolution ); ++col )
	{
		const float x = float( col ) / resolution - 0.5f;
		const float angle = std::atan2( x,/*focalLen*/0.8f );
		Ray ray = CastSingleRay( playerPos,
			startAngle + angle );
		ray.col = col;
		ray.angle = angle;
		// rays.emplace_back( ray );
		// DrawSingleRay( col,ray,angle,gfx );
		DrawLine( ray.start,ray.pos );
	}
}

void Flashlight::Draw( TileMap& map ) const
{
	for( int y = 0; y < TileMap::size; ++y )
	{
		for( int x = 0; x < TileMap::size; ++x )
		{
			if( flashArea[y * TileMap::size + x] > 0.0f )
			{
				map.PutPixel( x,y,Colors::White );
			}
		}
	}
}

void Flashlight::DrawLine( Vec2 p0,Vec2 p1 )
{
	float m = 0.0f;
	if( p0.x != p1.x )
	{
		m = ( p1.y - p0.y ) / ( p1.x - p0.x );
	}

	float power = strength;

	if( p0.x != p1.x && abs( m ) < 1.0f )
	{
		if( p0.x > p1.x ) std::swap( p0,p1 );

		const float b = p0.y - m * p0.x;

		for( int x = int( p0.x ); x < int( p1.x ); ++x )
		{
			const float y = m * float( x ) + b;
			// if( x >= 0 && x < ScreenWidth &&
			// 	y >= 0.0f && y < float( ScreenHeight ) )
			{
				// PutPixel( x,int( y ),c );
				flashArea[int( y ) * TileMap::size + x] = power;

				power -= loss;
				if( power <= globalBrightness ) break;
			}
		}
	}
	else
	{
		if( p0.y > p1.y ) std::swap( p0,p1 );

		const float w = ( p1.x - p0.x ) / ( p1.y - p0.y );
		const float p = p0.x - w * p0.y;

		for( int y = int( p0.y ); y < int( p1.y ); ++y )
		{
			const float x = w * float( y ) + p;
			// if( x >= 0.0f && x < float( ScreenWidth ) &&
			// 	y >= 0 && y < ScreenHeight )
			{
				// PutPixel( int( x ),y,c );
				flashArea[y * TileMap::size + int( x )] = power;

				power -= loss;
				if( power <= globalBrightness ) break;
			}
		}
	}
}

Ray Flashlight::CastSingleRay( const Vec2& start,float angle ) const
{
	Ray temp{ start,angle };
	bool foundWall = false;
	const auto sin = std::sin( angle );
	const auto cos = std::cos( angle );

	// while( GetTile( temp.GetPos() ) == TileType::Empty )
	while( !foundWall )
	{
		const Vec2 stepX = CalcStepOffset( sin,
			cos,temp.pos.x,temp.pos.y,false );
		const Vec2 stepY = CalcStepOffset( cos,
			sin,temp.pos.y,temp.pos.x,true );

		if( stepX.GetLengthSq() < stepY.GetLengthSq() )
		{
			temp.pos = stepX;
			temp.offset = stepX.y - std::floor( stepX.y );

			const auto dx = cos < 0 ? 1 : 0;
			if( level.GetTile( Vei2( temp.pos ) -
				Vei2{ dx,0 } ) != Level::TileType::Floor )
			{
				foundWall = true;
			}
		}
		else
		{
			temp.pos = stepY;
			temp.offset = stepY.x - std::floor( stepY.x );

			const auto dy = sin < 0 ? 1 : 0;
			if( level.GetTile( Vei2( temp.pos ) -
				Vei2{ 0,dy } ) != Level::TileType::Floor )
			{
				foundWall = true;
			}
		}
	}

	return( temp );
}

Vec2 Flashlight::CalcStepOffset( float rise,float run,
	float x,float y,bool inverted ) const
{
	if( run == 0.0f ) return( Vec2::Zero() );

	const float dx = ( ( run > 0 )
		? std::floor( x + 1.0f ) - x
		: std::ceil( x - 1.0f ) - x );
	const float dy = dx * ( rise / run );

	return( Vec2{ inverted ? y + dy : x + dx,
		inverted ? x + dx : y + dy } );
}
