#pragma once

#include "Vec2.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"
#include "Level.h"
#include "Arrow.h"
#include <vector>

class Player
{
public:
	Player( const Vei2& pos,const Level& level );

	void Update( const Keyboard& kbd,const Mouse& mouse,float dt );
	void Draw( TileMap& map ) const;
private:
	static constexpr float speed = 12.0f;
	const Level& level;
	Vec2 pos;
	std::vector<Arrow> arrows;
};