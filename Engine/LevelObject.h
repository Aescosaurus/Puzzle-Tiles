#pragma once

#include "Vec2.h"

class LevelObject
{
public:
	LevelObject( const Vei2& pos );

	void Destroy();

	const Vei2& GetPos();
	bool IsDestroyed() const;
protected:
	Vei2 pos;
private:
	bool destroyed = false;
};