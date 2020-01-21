#pragma once

#include "Vec2.h"
#include "TileMap.h"

// Player shoots arrows at enemies.
class Arrow
{
public:
	Arrow( const Vec2& pos,const Vec2& target );

	void Update( float dt );
	void Draw( TileMap& tilemap ) const;
private:
	static constexpr float speed = 35.0f;
	Vec2 pos;
	Vec2 vel;
};