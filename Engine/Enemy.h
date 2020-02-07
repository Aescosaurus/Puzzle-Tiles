#pragma once

#include "LevelObject.h"

class Enemy
	:
	public LevelObject
{
public:
	Enemy( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
	void Update2( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 120,30,230 ),20 };
	int dir = 1;
	Vei2 playerPos = Vei2::Zero();
};