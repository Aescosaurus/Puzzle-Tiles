#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include <memory>

class LevelObject
{
public:
	class UpdateInfo
	{
	private:
		typedef std::vector<std::unique_ptr<LevelObject>> PLevelObjectArr;
	public:
		float dt;
		PLevelObjectArr* arrows;
		PLevelObjectArr* basicGates;
		// PLevelObjectArr* lanterns;
	};
public:
	LevelObject( const Vei2& pos );

	virtual void Update( UpdateInfo& info ) {}
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

typedef std::vector<std::unique_ptr<LevelObject>> PLevelObjectArr;