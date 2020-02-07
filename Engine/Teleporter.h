#pragma once

#include "LevelObject.h"

class Teleporter
	:
	public LevelObject
{
public:
	Teleporter( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 50,230,20 ),20 };
};