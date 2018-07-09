/***************************************************************************
 *            init.cc
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

bool upPressed = false , downPressed = false, rightPressed = false, leftPressed = false, spacePressed = false;

void InitializeSystem(void)
{
	// Initialize video and audio system
	if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
  	{
    	printf("Unable to init SDL: %s\n", SDL_GetError());
		Quit();
  	}
	
	//
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
  	{
    	printf("Warning: Couldn't set 44100 Hz 16-bit audio\n\ Reason: %s\n", SDL_GetError());
  	}
  	
	// Set the title bar
	SDL_WM_SetCaption("Space", "Space");

	// Create window SDL_DOUBLEBUF
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_DOUBLEBUF);
	if (screen==NULL)
	{
    	printf("Warning: Couldn't set screen: %s\n" , SDL_GetError());
  	}
	
	//screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
}

//   This function TOGGLES between FULLSCREEN and WINDOWED mode
void ToggleFullScreen(void)
{
    if(SDL_WM_ToggleFullScreen(screen) == 0)        // try to toggle fullscreen mode for window 'screen' 
    {
        printf("Warning: Couldn't set screen: %s\n" , SDL_GetError());
		Quit();
    }
}

// Load spaceship

void LoadSound(void)
{
	music = Mix_LoadMUS("sound/music.xm");
	shot = Mix_LoadWAV("sound/shot.wav");
    explode = Mix_LoadWAV("sound/explode.wav");
	
	if (music==NULL || music ==NULL || explode==NULL)
	{
    	printf("Warning: Couldn't set sound: %s\n" , SDL_GetError());
  	}
}

void LoadSpaceShip(void)
{
	int colorkey;
	
	SDL_Surface *temp = SDL_LoadBMP("gfx/ship.bmp");
	spaceship = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(spaceship, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
	/* set sprite position */
	rcShip.x = 0;
	rcShip.y = (SCREEN_HEIGHT/2)-32;
}

void LoadEnemyShip1(void)
{
	int colorkey;
	
	SDL_Surface *temp = SDL_LoadBMP("gfx/enemy1.bmp");
	enemyship1 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(enemyship1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
	/* set sprite position */
	EnemyX.push(SCREEN_WIDTH);
	EnemyY.push(SCREEN_HEIGHT/2);
	
}

// Load space
void LoadSpace(void)
{
	SDL_Surface *temp  = SDL_LoadBMP("gfx/space.bmp");
	space = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
}

void LoadMissile(void)
{
	int colorkey;
	
	SDL_Surface *temp = SDL_LoadBMP("gfx/missile.bmp");
	missile = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(missile, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
	
	temp = SDL_LoadBMP("gfx/enemymissile.bmp");
	enemymissile= SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(enemymissile, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
}

void LoadXplosion(void)
{

	int colorkey;
	
	SDL_Surface *temp1 = SDL_LoadBMP("gfx/xplosion1.bmp");
	explosion1 = SDL_DisplayFormat(temp1);
	//SDL_FreeSurface(temp);
	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(explosion1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);	
	
	SDL_Surface *temp2 = SDL_LoadBMP("gfx/xplosion2.bmp");
	explosion2 = SDL_DisplayFormat(temp2);
	SDL_FreeSurface(temp2);
	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(explosion2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);	

	SDL_Surface *temp3 = SDL_LoadBMP("gfx/xplosion3.bmp");
	explosion3 = SDL_DisplayFormat(temp3);
	SDL_FreeSurface(temp3);
	// Setup sprite colorkey and turn on RLE
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(explosion3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);	
}

// Creates new player missile
void ShootMissile(int i)
{
	MissileX.push(rcShip.x);
	MissileY.push(rcShip.y);
	Mix_PlayChannel(0,shot,0);
	
}

// Creates new enemy missile
void EnemyShootMissile(int x, int y)
{
	
	EnemyMissileX.push(x);
	EnemyMissileY.push(y);
}

void HandleKeyPressEvent(SDL_keysym * keysym)
{
    switch(keysym -> sym)                                  // which key have we got
    {
        case SDLK_F1 :                                     // if it is F1
            ToggleFullScreen();                            // toggle between fullscreen and windowed mode
            break;
		
		case SDLK_SPACE :
			spacePressed = true;	
			break;
		
		case SDLK_LCTRL :                                  // if it is CTRL
		case SDLK_RCTRL :
						
            ShootMissile(iMissile);
			
					// toggle between fullscreen and windowed mode
            break;

        case SDLK_ESCAPE:                                  // if it is ESCAPE
        case SDLK_q:
			Quit();
			break;											// quit after cleaning up

        case SDLK_UP :                                     // If we hit the UP arrow Key
        case SDLK_w :
            upPressed = true;                              // make upPressed true
            break;
            
       case SDLK_DOWN :                                    // If we hit the Down arrow Key
       case SDLK_s :
            downPressed = true;                            // make downPressed true
            break;

		case SDLK_RIGHT :                                     // If we hit the RIGHT arrow Key
        case SDLK_d :
            rightPressed = true;                              // make upPressed true
            break;
            
       case SDLK_LEFT :                                    // If we hit the LEFT arrow Key
       case SDLK_a :
            leftPressed = true;                            // make downPressed true
            break;
	   
        default:                                           // any other key
            break;                                         // nothing to do
    }
}

// This function handles the keyrelease events generated when the user release a key
void HandleKeyReleaseEvent(SDL_keysym * keysym)
{
    switch(keysym -> sym)                                  // which key have we got
    {
        case SDLK_UP :                                     // If we release the UP arrow Key
        case SDLK_w :
            upPressed = false;                             // make it false 
            break;
            
       case SDLK_DOWN :                                    // If we release the Down arrow Key
       case SDLK_s :
            downPressed = false;                           // make downPressed false 
            break;

		case SDLK_RIGHT :                                     // If we hit the RIGHT arrow Key
        case SDLK_d :
            rightPressed = false;                              // make upPressed true
            break;
            
       case SDLK_LEFT :                                    // If we hit the LEFT arrow Key
       case SDLK_a :
            leftPressed = false;                            // make downPressed true
            break;
		
	   case SDLK_SPACE :                                  // if it is Space
			spacePressed = false;	
			break;
	   
	   
	   default:                                           // any other key
            break;                                         // nothing to do
    }
}

// Checks if player pressed keyboard and moves hero
void MoveSpaceship(void)
{

    if(upPressed)                   // If we hit the UP arrow key
       // Hero.SetY(-2);
		rcShip.y -= 2;            // Move our camera forward by a positive speed
    
    if(downPressed)                // If we hit the DOWN arrow key
        //Hero.SetY(2);
		rcShip.y += 2;            // Move our camera backward by a negative speed
    	
	if(rightPressed)                // If we hit the UP arrow key
        rcShip.x += 2;            // Move our camera forward by a positive speed

    if(leftPressed)	  		        // If we hit the DOWN arrow key
        rcShip.x -= 2;            // Move our camera backward by a negative speed
	
	/* collide with edges of screen */
	if ( rcShip.x < 0 ) {
		rcShip.x = 0;
	}
	else if ( rcShip.x > SCREEN_WIDTH-SPRITE_SIZE ) {
		rcShip.x = SCREEN_WIDTH-SPRITE_SIZE;
	}
	if ( rcShip.y < 0 ) {
		rcShip.y = 0;
	}
	else if ( rcShip.y > SCREEN_HEIGHT-SPRITE_SIZE ) {
		rcShip.y = SCREEN_HEIGHT-SPRITE_SIZE;
	}
}
// Moves missiles (player and enemies)
void MoveMissiles(void)
{
	int x,y;
	for (int i=0;i<MissileX.size();i++)
	{
		x=MissileX.front();
		y=MissileY.front();
		MissileX.pop();
		MissileY.pop();	
		x += 4;		
		if (x < SCREEN_WIDTH)
		{
			MissileX.push(x);
			MissileY.push(y);
		}
	}
	for (int i=0;i<EnemyMissileX.size();i++)
	{
		x=EnemyMissileX.front();
		y=EnemyMissileY.front();
		EnemyMissileX.pop();
		EnemyMissileY.pop();
		x -= 4;
		if (x > 0);
		{
			EnemyMissileX.push(x);
			EnemyMissileY.push(y);
		}
	}
}

//Moves enemies
void MoveEnemy(void)
{
	int x,y,c;	
	for (int i=0;i<EnemyX.size();i++)
	{
		x=EnemyX.front();
		y=EnemyY.front();
		
		EnemyX.pop();
		EnemyY.pop();	
		x--;
		
		c = rand()%200;
		
		switch(c)
		{
    		case 1:
				EnemyShootMissile(x,y);
				break;
			
			default:
				break;
		}
		
		if (x < SCREEN_WIDTH)
		{
			EnemyX.push(x);
			EnemyY.push(y);
		}
	}
}

// Create new enemy
void NewEnemy(void)
{
	int x = rand()%100;
	
	int y =((SPRITE_SIZE/2)+rand()%(SCREEN_HEIGHT-(SPRITE_SIZE/2)));	
		
	
	switch(x)
	{
    	case 1:
			EnemyX.push(SCREEN_WIDTH);
			EnemyY.push(y);
			break;
		
		default:                                           // any other key
            break;
	}
}

// Check if player and enemy collide
void CheckCollision(void)
{
	for (int i=0; i<EnemyX.size();i++)
	{
		int x1,y1;
		
		// Enemy sprite left-top corner
		x1=EnemyX.front();
		y1=EnemyY.front();
		
		EnemyX.pop();
		EnemyY.pop();
		
		if ((rcShip.x-1 > x1) && (rcShip.x-1 < x1+SPRITE_SIZE+1) && (rcShip.y+1 > y1) && (rcShip.y+1 < y1+SPRITE_SIZE+1))
		{
			Quit();
		}
		
		EnemyX.push(x1);
		EnemyY.push(y1);
	}		
}

void CheckMissileCollision(void)
{
	bool hit = false;
	int x1,x2,y1,y2, missilex, missiley;
	
	// Check if player missiles hit enemies
	for (int z=0; z<MissileX.size();z++)
	{
		missilex=MissileX.front();
		missiley=MissileY.front();
		MissileX.pop();
		MissileY.pop();
		for (int i=0; i<EnemyX.size();i++)
		{
			// Enemy sprite left-top corner
			x1=EnemyX.front();
			y1=EnemyY.front();
		
			EnemyX.pop();
			EnemyY.pop();
		
			if ((missilex-1 > x1) && (missilex-1 < x1+SPRITE_SIZE+1) && (missiley+1 > y1) && (missiley+1 < y1+SPRITE_SIZE+1))
			{
				Mix_PlayChannel(1,explode,0);
				hit = true; 
				iKills++;
								
				//DrawSprite(explosion3, x1,y1);
				//DrawExplosion(1,x1+16,y1+16);
			}
			else{
				
				EnemyX.push(x1);
				EnemyY.push(y1);
			}
		}
		if (!hit)
		{
			MissileX.push(missilex);
			MissileY.push(missiley);
		}
		hit = false;
	}
	hit = false;
	
	// Check if enemy missiles hit player
	for (int z=0; z<EnemyMissileX.size();z++)
	{
		missilex=EnemyMissileX.front();
		missiley=EnemyMissileY.front();
		EnemyMissileX.pop();
		EnemyMissileY.pop();

		x1=rcShip.x;
		y1=rcShip.y;
		
		if ((missilex-1 > x1) && (missilex-1 < x1+SPRITE_SIZE+1) && (missiley+1 > y1) && (missiley+1 < y1+SPRITE_SIZE+1))
		{
			hit = true; 
			Quit();
		}
		
		if (!hit)
		{
			EnemyMissileX.push(missilex);
			EnemyMissileY.push(missiley);
		}
	}
	
}
