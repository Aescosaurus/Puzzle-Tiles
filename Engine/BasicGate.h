#pragma once

#include "LevelObject.h"
#include "ColorStyle.h"

// Basic gate requires you to shoot the trigger to open.
// The trigger is one block of this type with none surrounding it.
class BasicGate
	:
	public LevelObject
{
public:
	BasicGate( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
	void Draw( TileMap& tilemap ) const override;
private:
	static constexpr ColorStyle style = { Colors::MakeRGB( 230,50,50 ),20 };
	Color col;
};