#pragma once

#include "Vec2.h"
#include "TileMap.h"

class LevelObject
{
public:
	LevelObject( const Vei2& pos );

	virtual void Draw( TileMap& map ) const;

	void Destroy();

	const Vei2& GetPos();
	bool IsDestroyed() const;
protected:
	Vei2 pos;
private:
	bool destroyed = false;
};