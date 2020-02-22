#pragma once

#include "Keyboard.h"
#include "TileMap.h"
#include "Player.h"
#include "Level.h"
#include "FrameTimer.h"
#include "Lantern.h"
#include "Door.h"
#include "BasicGate.h"
#include "Replicator.h"
#include "StepGate.h"
#include "Turret.h"
#include "Teleporter.h"
#include "Enemy.h"
#include "AutoShooter.h"
#include "Surface.h"

class Gameplay
{
public:
	Gameplay( const Keyboard& kbd,TileMap& tilemap );
	~Gameplay();

	void Update();
	void Draw();
	
	bool HasWon() const;
private:
	void Load( const std::string& levelName );
	int ReadSave() const;
	void WriteSave() const;
	std::string GenerateLevelName() const;
private:
	const Keyboard& kbd;
	TileMap& tilemap;

	FrameTimer ft;
	Level level;
	LevelObject::UpdateInfo updateInfo;
	std::vector<PLevelObjectArr> levelObjects;
	Player guy;
	Door door;
	int curLevel = 0;
	bool canAdvanceLevel = false;
	CSoundPtr exitSound = SoundCodex::Fetch( "Sounds/Door.wav" );
	// CSoundPtr music = SoundCodex::Fetch( "Sounds/Puzzle01.wav" );
	Sound music = Sound{ L"Sounds/Puzzle01.wav",Sound::LoopType::AutoFullSound };
	Timer fadeIn = 1.0f;
	bool canPressR = false;
};