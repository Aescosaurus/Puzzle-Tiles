#include "Level.h"
#include "Random.h"

Level::Level()
{
	// Create initial array.
	tiles.reserve( size * size );
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			tiles.emplace_back( Tile{ TileType::Wall,
				Colors::Black } );
		}
	}

	// Set up random rooms.
	const int nRooms = int( Random{ 11,15 } );
	std::vector<RectI> rooms;
	for( int i = 0; i < nRooms; i )
	{
		const auto randSize = Vei2{
			int( Random{ 4,7 } ),
			int( Random{ 4,7 } )
		};
		const auto randPos = Vei2{
			int( Random{ 1,size - randSize.x - 1 } ),
			int( Random{ 1,size - randSize.y - 1 } )
		};

		auto testRect = RectI{ randPos,randSize.x,randSize.y };
		bool overlapping = false;
		if( int( rooms.size() ) == 0 ) overlapping = true;
		for( const auto& room : rooms )
		{
			if( room.IsOverlappingWith( testRect ) )
			{
				overlapping = true;
				break;
			}
		}
		if( overlapping )
		{
			rooms.emplace_back( RectI{ randPos,randSize.x,randSize.y } );
			++i;
		}
	}

	// Fill in random rooms.
	for( const auto& room : rooms )
	{
		DrawRect( room );
	}

	// Randomize colors.
	for( auto& tile : tiles )
	{
		tile.RandomizeColor();
	}
}

void Level::Draw( TileMap& map ) const
{
	for( int y = 0; y < size; ++y )
	{
		for( int x = 0; x < size; ++x )
		{
			map.PutPixel( x,y,tiles[y * size + x].c );
		}
	}
}

Level::TileType Level::GetTile( const Vei2& pos ) const
{
	return( tiles[pos.y * size + pos.x].type );
}

Vei2 Level::GetValidSpot() const
{
	auto randSpot = Vei2::Zero();
	do
	{
		randSpot.x = int( Random{ 0,size - 1 } );
		randSpot.y = int( Random{ 0,size - 1 } );
	}
	while( GetTile( randSpot ) != TileType::Floor );

	return( randSpot );
}

void Level::DrawRect( const RectI& rect )
{
	for( int y = rect.top; y < rect.bottom; ++y )
	{
		for( int x = rect.left; x < rect.right; ++x )
		{
			tiles[y * size + x].type = TileType::Floor;
		}
	}
}

void Level::Tile::RandomizeColor()
{
	Color base = Colors::Black;
	bool sameDeviation = false;
	switch( type )
	{
	case TileType::Floor:
		base = Colors::MakeRGB( 110,110,110 );
		sameDeviation = true;
		break;
	case TileType::Wall:
		base = Colors::MakeRGB( 20,20,50 );
		sameDeviation = false;
		break;
	}

	if( sameDeviation )
	{
		const auto amount = int( Random{ -deviation,deviation } );
		c.SetR( base.GetR() + amount );
		c.SetG( base.GetG() + amount );
		c.SetB( base.GetB() + amount );
	}
	else
	{
		c.SetR( base.GetR() + int( Random{ -deviation,deviation } ) );
		c.SetG( base.GetG() + int( Random{ -deviation,deviation } ) );
		c.SetB( base.GetB() + int( Random{ -deviation,deviation } ) );
	}
}
