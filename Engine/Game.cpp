/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	gameplay( wnd.kbd,tilemap ),
	levelEditor( wnd.kbd,wnd.mouse )
{
#if NDEBUG
	gameState = State::Gameplay;
#endif
}

void Game::Go()
{
	gfx.BeginFrame();
	tilemap.Reset();
	UpdateModel();
	ComposeFrame();
	tilemap.Draw( gfx );
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	switch( gameState )
	{
	case State::Menu:
		if( wnd.kbd.KeyIsPressed( VK_SPACE ) )
		{
			gameState = State::Gameplay;
		}
		if( wnd.kbd.KeyIsPressed( 'E' ) )
		{
			gameState = State::LevelEditor;
		}
		break;
	case State::Gameplay:
		gameplay.Update();
		break;
	case State::LevelEditor:
		levelEditor.Update();
		break;
	}
}

void Game::ComposeFrame()
{
	switch( gameState )
	{
	case State::Menu:
		break;
	case State::Gameplay:
		gameplay.Draw();
		break;
	case State::LevelEditor:
		levelEditor.Draw( tilemap );
		break;
	}
}
