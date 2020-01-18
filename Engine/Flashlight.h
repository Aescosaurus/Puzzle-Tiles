#pragma once

#include "Vec2.h"
#include "Ray.h"
#include "Level.h"

class Flashlight
{
public:
	Flashlight( const Level& level );

	void Update( const Vec2& playerPos,const Vec2& mousePos );
	void Draw( TileMap& map ) const;
private:
	void DrawLine( Vec2 p0,Vec2 p1 );

	Ray CastSingleRay( const Vec2& start,float angle ) const;
	Vec2 CalcStepOffset( float rise,float run,
		float x,float y,bool inverted ) const;
private:
	const Level& level;
	std::vector<float> flashArea;
	static constexpr int resolution = 1;
	static constexpr float globalBrightness = 0.1f;
	// Affects flashlight brightness.
	static constexpr float strength = 1.0f;
	static constexpr float loss = 0.2f;
};