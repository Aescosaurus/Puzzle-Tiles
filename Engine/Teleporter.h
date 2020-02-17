#pragma once

#include "LevelObject.h"
#include "Codex.h"

class Teleporter
	:
	public LevelObject
{
public:
	Teleporter( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 50,230,20 ),20 };
	std::vector<CSoundPtr> hitSounds =
	{
		SoundCodex::Fetch( "Sounds/Teleporter1.wav" ),
		SoundCodex::Fetch( "Sounds/Teleporter2.wav" ),
		SoundCodex::Fetch( "Sounds/Teleporter3.wav" ),
		SoundCodex::Fetch( "Sounds/Teleporter4.wav" )
	};
};