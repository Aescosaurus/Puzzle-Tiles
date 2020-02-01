#pragma once

#include "LevelObject.h"
#include "Timer.h"

// Shoots up but rotates right each time you hit it.
class Turret
	:
	public LevelObject
{
public:
	Turret( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 230,230,20 ),20 };
	Vei2 dir = Vei2::Up();
};