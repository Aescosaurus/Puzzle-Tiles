#pragma once

#include "LevelObject.h"

// Gate where you have to walk next to it to open.
class StepGate
	:
	public LevelObject
{
public:
	StepGate( const Vei2& pos );

	void Update( UpdateInfo& info );
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 255,87,243 ),20 };
};