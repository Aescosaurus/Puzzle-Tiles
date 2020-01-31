#pragma once

#include "LevelObject.h"

// When hit by an arrow shoots arrows back in all directions.
class Replicator
	:
	public LevelObject
{
public:
	Replicator( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 90,170,240 ),10 };
	static constexpr Vei2 dirs[] = { Vei2::Up(),Vei2::Down(),
		Vei2::Left(),Vei2::Right() };
};