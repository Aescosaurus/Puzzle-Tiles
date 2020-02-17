#pragma once

#include "LevelObject.h"
#include "Timer.h"
#include "Codex.h"

// Shoots up but rotates right each time you hit it.
class Turret
	:
	public LevelObject
{
public:
	Turret( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 230,180,70 ),20 };
	Vei2 dir = Vei2::Up();
	int curSound = 0;
	std::vector<CSoundPtr> hitSounds =
	{
		SoundCodex::Fetch( "Sounds/Turret1.wav" ),
		SoundCodex::Fetch( "Sounds/Turret2.wav" ),
		SoundCodex::Fetch( "Sounds/Turret3.wav" ),
		SoundCodex::Fetch( "Sounds/Turret4.wav" )
	};
};