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
	enum class Type
	{
		Arrow = 0,
		Lantern,
		BasicGate,
		Replicator,
		StepGate,
		Max
	};
public:
	class UpdateInfo
	{
	public:
		const Keyboard& kbd;
		float dt;
		LevelObject& player;
		LevelObject& door;
		std::vector<PLevelObjectArr>& levelObjects;
		// PLevelObjectArr* arrows;
		// PLevelObjectArr* lanterns;
		// PLevelObjectArr* basicGates;
		// PLevelObjectArr* lanterns;
	};
public:
	LevelObject( const Vei2& pos,Color col,bool visible = false );

	virtual void Update( UpdateInfo& info ) {}
	virtual void Draw( TileMap& map ) const;

	void Destroy();
	void SetPos( const Vei2& pos );
	void SetVisible();

	const Vei2& GetPos() const;
	bool IsDestroyed() const;
	// Returns true if pos has nothing on top of it.
	bool CheckPos( const Vei2& pos,const UpdateInfo& info ) const;
	bool IsVisible() const;
	virtual bool IsLit() const;
protected:
	Vei2 pos;
	Color col;
	bool visible = false;
private:
	bool destroyed = false;
};
