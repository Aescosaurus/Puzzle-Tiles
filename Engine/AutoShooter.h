#pragma once

#include "LevelObject.h"

class AutoShooter
	:
	public LevelObject
{
public:
	AutoShooter( const Vei2& pos );

	void Update( UpdateInfo& info );
private:
	// Certain dir based on loc on map.
	Vei2 CalcDir( const Vei2& pos );
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 200,230,20 ),20 };
	Vei2 dir;
	Vei2 oldPlayerPos;
};