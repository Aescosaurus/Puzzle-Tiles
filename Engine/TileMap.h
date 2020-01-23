#pragma once

#include <vector>
#include "Graphics.h"
#include "ColorStyle.h"

class TileMap
{
public:
	TileMap();

	void Draw( Graphics& gfx ) const;

	void PutPixel( int x,int y,Color c );
	void PutLight( int x,int y,Color c,float val );
	// void DrawLightRect( int x,int y,int width,int height,Color c,float val );
	// void DrawLightCircle( int x,int y,int size,const ColorStyle& cs );
	void Reset();

	Color GetPixel( int x,int y ) const;
public:
	static constexpr int size = 20;
	static constexpr int tileSize = Graphics::ScreenHeight / size;
	static constexpr int padding = ( Graphics::ScreenWidth - tileSize * size ) / 2;
private:
	static constexpr float globalBrightness = 0.5f;
	std::vector<Color> tiles;
	std::vector<std::pair<Color,float>> lightMap;
};