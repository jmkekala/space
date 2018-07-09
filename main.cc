/***************************************************************************
 *            main.cc
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

SDL_Surface *screen, *spaceship, *enemyship1, *space,*missile, *enemymissile, *explosion1, *explosion2, *explosion3, *temp;
SDL_Rect rcShip, rcSpace;
SDL_Event event;
Mix_Music *music;         // This will store our music
Mix_Chunk *shot;		  // This will store our shot sound
Mix_Chunk *explode;       // This will store our "explosion" sound

SDLFont *font;


int iMissile = 0; // Which missile
int iKills = 0;

queue<int> MissileX; // Queue for player missiles, x position
queue<int> MissileY; // Queue for player missiles, y position

queue<int> EnemyX;	 // Queue for enemy positions, x position 	 
queue<int> EnemyY;	 // Queue for enemy positions, y position

queue<int> EnemyMissileX; // Queue for enemy missiles, x position
queue<int> EnemyMissileY; // Queue for enemy missiles, y position

int colorkey;
	
void MainLoop(void)
{
	bool done = false;
		
	while (!done)
	{
	while( SDL_PollEvent(& event) )                    // look for events
        {
           	switch ( event.type )                          // what kind of event have we got ?
           	{
               	case SDL_QUIT :									// if user wishes to quit
					Quit();											
                   	done = true;									// this implies our job is done
                   	break;

               	case SDL_KEYDOWN :                                      // if the user has pressed a key
                   	HandleKeyPressEvent( & event. key.keysym );         // callback for handling keystrokes, arg is key pressed
                   	break;
                    
               	case SDL_KEYUP :
                   	HandleKeyReleaseEvent(& event.key.keysym) ;         // callback for handling keystrokes, arg is key released
                   	break;

               	default:                                    // any other event
                   	break;                                  // nothing to do
           	} 	
		}
		
		NewEnemy();
		MoveEnemy();
		
		MoveSpaceship();
		MoveMissiles();
		
		CheckCollision();
		CheckMissileCollision();
		
		
		DrawSpace();
		DrawEnemy();
		DrawSpaceship();		
		DrawMissiles();
		
		int iFont = StringWidth(font,"Score");
		
		DrawString(screen,font,0,10,"Kills:");
		DrawString(screen,font,iFont+10,10,"%d",iKills);
				
		UpdateScreen();

		
	}
		
}

void Quit(void)
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(spaceship);
	SDL_FreeSurface(enemymissile);
	SDL_FreeSurface(enemyship1);
	SDL_FreeSurface(space);
	SDL_FreeSurface(explosion1);
	SDL_FreeSurface(explosion2);
	SDL_FreeSurface(explosion3);
	Mix_FreeChunk(shot);
	Mix_FreeChunk(explode);
	Mix_FreeMusic(music);
	FreeFont(font);
	SDL_Quit();
	cout << "Number of kills: " << iKills << endl;
	exit(0);
}


int main(int argc, char *argv[])
{
	
	InitializeSystem();
	LoadSound();
	LoadSpaceShip();
	LoadEnemyShip1();
	LoadSpace();
	LoadMissile();
	LoadXplosion();
	
	font = initFont("font",1,1,0);
	
	//yellowfont = initFont("data/font",1,1,0);
	
	
	 // If we aren't playing music at the moment
    	if(!Mix_PlayingMusic())
    	{
      		// then start playing it.
      		Mix_PlayMusic(music, 0);
    	}
	
	srand(time(NULL));
	
	MainLoop();
	Quit();
}
