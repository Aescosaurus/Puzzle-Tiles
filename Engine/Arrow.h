#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"
#include "LevelObject.h"
#include "ColorStyle.h"
#include "ColorMap.h"

class Arrow
	:
	public LevelObject
{
public:
	Arrow( const Vei2& pos,const Vei2& vel );

	void Update( UpdateInfo& info ) override;
	void Update2( UpdateInfo& info ) override;
	void Draw( TileMap& tilemap ) const override;
private:
	static constexpr int lightArea = 2;
	Vei2 vel;
	Timer moveSpeed = 0.05f;
	static constexpr ColorStyle cs = { Colors::MakeRGB( 230,230,140 ),20 };
	ColorMap colMap;
};