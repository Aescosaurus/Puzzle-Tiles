#pragma once

#include "LevelObject.h"
#include <vector>
#include "Colors.h"
#include "ColorMap.h"

class Lantern
	:
	public LevelObject
{
public:
	Lantern( const Vei2& pos );

	void Update( UpdateInfo& info ) override;
	void Draw( TileMap& map ) const override;

	void Light( UpdateInfo& info );
private:
	void SetArrVisible( PLevelObjectArr* arr ) const;
	void SetItemVisible( LevelObject& obj ) const;
private:
	static constexpr int lightRadius = 5;
	bool lit = false;
	static constexpr ColorStyle style = { Colors::MakeRGB( 240,190,110 ),10 };
	ColorMap colMap;
};