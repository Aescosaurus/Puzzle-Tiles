#pragma once

#include "LevelObject.h"
#include "Timer.h"

class Shooter
	:
	public LevelObject
{
public:
	Shooter( const Vei2& pos,const Vei2& dir );

	void Update( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 230,230,20 ),20 };
	Timer refire = 0.75f;
	Vei2 dir;
};