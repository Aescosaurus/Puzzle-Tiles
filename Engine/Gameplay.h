#pragma once

#include "Keyboard.h"
#include "TileMap.h"
#include "Player.h"
#include "Level.h"
#include "FrameTimer.h"
#include "Lantern.h"
#include "Door.h"
#include "BasicGate.h"

class Gameplay
{
public:
	Gameplay( const Keyboard& kbd,TileMap& tilemap );

	void Update();
	void Draw();
private:
	void Load( const std::string& levelName );
private:
	const Keyboard& kbd;
	TileMap& tilemap;

	FrameTimer ft;
	Level level;
	LevelObject::UpdateInfo updateInfo;
	Player guy;
	PLevelObjectArr& arrows;
	PLevelObjectArr lanterns;
	PLevelObjectArr basicGates;
	Door door;
};