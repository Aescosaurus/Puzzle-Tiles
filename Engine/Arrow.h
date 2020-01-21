#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"

class Arrow
{
public:
	Arrow( const Vei2& pos,const Vei2& vel );

	void Update( float dt );
	void Draw( TileMap& tilemap ) const;

	void Destroy();

	Vei2 GetPos();
	bool IsDestroyed() const;
private:
	Vei2 pos;
	Vei2 vel;
	bool destroyed = false;
	Timer moveSpeed = 0.04f;
};