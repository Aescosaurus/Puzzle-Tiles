#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"
#include "LevelObject.h"

class Arrow
	:
	public LevelObject
{
public:
	Arrow( const Vei2& pos,const Vei2& vel );

	void Update( float dt );
	void Draw( TileMap& tilemap ) const;
private:
	Vei2 vel;
	Timer moveSpeed = 0.04f;
};