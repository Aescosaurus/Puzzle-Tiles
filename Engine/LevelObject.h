#pragma once

#include "Vec2.h"
#include "TileMap.h"

class LevelObject
{
public:
	LevelObject( const Vei2& pos );

	virtual void Draw( TileMap& map ) const;

	void Destroy();
	void SetPos( const Vei2& pos );

	const Vei2& GetPos() const;
	bool IsDestroyed() const;
protected:
	Vei2 pos;
private:
	bool destroyed = false;
};