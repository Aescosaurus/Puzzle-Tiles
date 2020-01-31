#pragma once

#include "Vec2.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TileMap.h"
#include "Level.h"
#include "Arrow.h"
#include <vector>
#include "Timer.h"
#include "LevelObject.h"

class Player
	:
	public LevelObject
{
public:
	Player( const Vei2& pos,const Level& level,
		PLevelObjectArr& arrows );

	void Update( UpdateInfo& info ) override;
	void Draw( TileMap& map ) const override;

	// void SetPos( const Vei2& pos );

	// const Vei2& GetPos() const;
	// PLevelObjectArr& GetArrows();
private:
	// Tells whether player can move into loc.
	bool CanMove( const Vei2& loc,UpdateInfo& info ) const;
private:
	static constexpr float speed = 12.0f;
	const Level& level;
	// Vei2 pos;
	PLevelObjectArr& arrows;
	// Timer refire = 0.45f;
	bool canMove = false;
	bool canShoot = false;
};