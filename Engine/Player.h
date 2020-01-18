#pragma once

#include "Vec2.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"

class Player
{
public:
	Player( const Vei2& pos );

	void Update( const Keyboard& kbd,const Mouse& mouse,float dt );
	void Draw( TileMap& map ) const;
private:
	static constexpr float speed = 0.2f;
	Vec2 pos;
};