#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"

class Enemy
{
public:
	Enemy( const Vei2& pos );

	void Update( const Vei2& playerPos,float dt );
	void Draw( TileMap& map ) const;

	void Destroy();

	const Vei2& GetPos() const;
	bool IsDestroyed() const;
private:
	Vei2 pos;
	Timer moveTimer = 0.7f;
	bool destroyed = false;
};