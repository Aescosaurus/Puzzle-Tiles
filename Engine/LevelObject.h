#pragma once

#include "Vec2.h"
#include "TileMap.h"
#include <memory>
#include "Keyboard.h"

class LevelObject;
typedef std::vector<std::unique_ptr<LevelObject>> PLevelObjectArr;

class LevelObject
{
public:
	class UpdateInfo
	{
	public:
		const Keyboard* kbd;
		float dt;
		LevelObject* player;
		LevelObject* door;
		PLevelObjectArr* arrows;
		PLevelObjectArr* lanterns;
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
	// Returns true if pos has nothing on top of it.
	bool CheckPos( const Vei2& pos,const UpdateInfo& info ) const;
private:
	// True if arr does not contain object on pos.
	bool IsEmpty( const Vei2& pos,PLevelObjectArr* arr ) const;
protected:
	Vei2 pos;
private:
	bool destroyed = false;
};
