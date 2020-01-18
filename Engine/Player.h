#pragma once

#include "Vec2.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"
#include "Flashlight.h"

class Player
{
public:
	Player( const Vei2& pos,const Level& level );

	void Update( const Keyboard& kbd,const Mouse& mouse,float dt );
	void Draw( TileMap& map ) const;
	void DrawFlashlight( TileMap& map ) const;
private:
	static constexpr float speed = 0.2f;
	Vec2 pos;
	Flashlight flashlight;
};