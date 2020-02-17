#pragma once

#include "LevelObject.h"
#include "Codex.h"

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
	int curSound = 0;
	std::vector<CSoundPtr> hitSounds =
	{
		SoundCodex::Fetch( "Sounds/Auto1.wav" ),
		SoundCodex::Fetch( "Sounds/Auto2.wav" ),
		SoundCodex::Fetch( "Sounds/Auto3.wav" ),
		SoundCodex::Fetch( "Sounds/Auto4.wav" )
	};
};