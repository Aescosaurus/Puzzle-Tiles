#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"
#include "LevelObject.h"

class Enemy
	:
	public LevelObject
{
public:
	Enemy( const Vei2& pos );

	void Update( const Vei2& playerPos,float dt );
	void Draw( TileMap& map ) const override;
private:
	Timer moveTimer = 0.7f;
};