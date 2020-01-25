#pragma once

#include "LevelObject.h"
#include "ColorStyle.h"

class Door
	:
	public LevelObject
{
public:
	Door( const Vei2& pos );
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 50,210,210 ),20 };
};