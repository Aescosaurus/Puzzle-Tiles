#pragma once

#include "LevelObject.h"
#include <vector>
#include "Colors.h"
#include "ColorMap.h"
#include "Codex.h"

class Lantern
	:
	public LevelObject
{
public:
	Lantern( const Vei2& pos,bool lit = false );

	void Update( UpdateInfo& info ) override;
	void Draw( TileMap& map ) const override;

	void Light( UpdateInfo& info );

	bool IsLit() const override;
public:
	static constexpr int lightRadius = 5;
private:
	bool lit = false;
	bool willLight = false;
	static constexpr ColorStyle mapStyle = { Colors::MakeRGB( 240,190,110 ),10 };
	static constexpr ColorStyle tileStyle = { Colors::MakeRGB( 230,100,30 ),10 };
	ColorMap colMap;
	CSoundPtr hitSound = SoundCodex::Fetch( "Sounds/LanternHitOn.wav" );
	CSoundPtr alreadyHitSound = SoundCodex::Fetch( "Sounds/LanternHit.wav" );
};