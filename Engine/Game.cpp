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
#include "ChiliUtils.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	guy( level.GetValidSpot(),level )
{
	enemies.emplace_back( Enemy{ Vei2{ 5,5 } } );
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
	const auto dt = ft.Mark();
	guy.Update( wnd.kbd,wnd.mouse,dt );

	auto& arrows = guy.GetArrows();
	
	const auto& playerPos = guy.GetPos();
	for( auto& enemy : enemies )
	{
		enemy.Update( playerPos,dt );

		for( auto& arrow : arrows )
		{
			if( arrow.GetPos() == enemy.GetPos() )
			{
				arrow.Destroy();
				enemy.Destroy();
				tilemap.DrawLightRect( 0,0,
					TileMap::size,TileMap::size,
					Colors::White,0.9f );
			}
		}
	}

	chili::remove_erase_if( enemies,std::mem_fn( &Enemy::IsDestroyed ) );
	chili::remove_erase_if( arrows,std::mem_fn( &Arrow::IsDestroyed ) );
}

void Game::ComposeFrame()
{
	level.Draw( tilemap );
	guy.Draw( tilemap );

	for( const auto& enemy : enemies )
	{
		enemy.Draw( tilemap );
	}
}
