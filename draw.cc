/***************************************************************************
 *            draw.cc
 *
 *  Sun Jan  9 21:05:51 2005
 *  Copyright  2005  Juha Kekäläinen
 *  Email: juha.kekalainen@gmail.com
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "main.h"
#include <unistd.h>

void UpdateScreen(void)
{
	SDL_UpdateRect(screen,0,0,0,0);	
	usleep(6000);
}

void DrawSprite( SDL_Surface *surface, int x, int y) 
{
	SDL_Rect destination;

	destination.x = x;
	destination.y = y;

	SDL_BlitSurface( surface, NULL, screen, &destination );
}

void DrawSpace(void)
{
	for (int x = 0; x <= SCREEN_WIDTH/SPRITE_SIZE; x++) {
		for (int y = 0; y <= SCREEN_HEIGHT/SPRITE_SIZE; y++) {
			rcSpace.x = (x * SPRITE_SIZE);
			rcSpace.y = y * SPRITE_SIZE;
			SDL_BlitSurface(space, NULL, screen, &rcSpace);
		}
	}
}

void DrawMissiles(void)
{
	int x,y;
	for (int i=0; i<MissileX.size();i++)
	{
		x=MissileX.front();
		y=MissileY.front();
		MissileX.pop();
		MissileY.pop();
		DrawSprite(missile,x,y);
		MissileX.push(x);
		MissileY.push(y);
	}
	for (int i=0; i<EnemyMissileX.size();i++)
	{
		x=EnemyMissileX.front();
		y=EnemyMissileY.front();
		EnemyMissileX.pop();
		EnemyMissileY.pop();
		DrawSprite(enemymissile,x,y);
		EnemyMissileX.push(x);
		EnemyMissileY.push(y);
	}
}

void DrawSpaceship(void)
{
	DrawSprite(spaceship,rcShip.x,rcShip.y);
}

void DrawEnemy(void)
{
	for (int i=0; i<EnemyX.size();i++)
	{
		int x,y;
		x=EnemyX.front();
		y=EnemyY.front();
		EnemyX.pop();
		EnemyY.pop();
		DrawSprite(enemyship1,x,y);
		EnemyX.push(x);
		EnemyY.push(y);
	}	
}

void DrawExplosion(int x, int y)
{
	DrawSprite(explosion1,x,y);
	DrawSprite(explosion2,x,y);
	DrawSprite(explosion3,x,y);
}
