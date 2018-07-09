/***************************************************************************
 *            main.h
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

#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "string"
#include "queue"

#include "iostream"
#include "stdio.h"
#include "stdlib.h"


#include "time.h"
#include "math.h"


#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define SPRITE_SIZE 	32

using namespace std;
using std::queue;


extern SDL_Surface *screen, *spaceship, *enemyship1, *space, *missile,*enemymissile, *explosion1, *explosion2, *explosion3;
extern SDL_Rect rcShip, rcSpace;
extern Mix_Music *music;         // This will store our music
extern Mix_Chunk *shot;          // This will store our shot sound
extern Mix_Chunk *explode;       // This will store our "explosion" sound




extern int iMissile, iAir, iKills;
extern queue<int> MissileX;
extern queue<int> MissileY;

extern queue<int> EnemyX;
extern queue<int> EnemyY;

extern queue<int> EnemyMissileX;
extern queue<int> EnemyMissileY;

// Init.cc functions
void InitializeSystem(void);
void ToggleFullScreen(void);
void LoadSound(void);
void LoadSpaceShip(void);
void LoadEnemyShip1(void);
void LoadSpace(void);
void LoadMissile(void);
void LoadXplosion(void);
void ShootMissile(int i);
void EnemyShootMissile(int x, int y);
void HandleKeyPressEvent(SDL_keysym * keysym);
void HandleKeyReleaseEvent(SDL_keysym * keysym);
void MoveSpaceship(void);
void MoveMissiles(void);
void MoveEnemy(void);
void NewEnemy(void);
void CheckCollision(void);
void CheckMissileCollision(void);


// draw.cc functions

void UpdateScreen(void);
void DrawSprite( SDL_Surface *surface, int x, int y);
void DrawSpace(void);
void DrawMissiles(void);
void DrawSpaceship(void);
void DrawEnemy(void);
void DrawExplosion(int x, int y);

// main.cc functions
void MainLoop(void);
void Quit(void);

// font.cc functions etc

struct SDLFont
{
  SDL_Surface *font;    // The SDL Surface for the font image
  int width;            // Width of the SDL Surface (same as the height)
  int charWidth;        // Width of one block character in the font (fontWidth/16)
  int *widths;          // Real widths of all the fonts
  unsigned char *data;  // The raw font data
};

// Function prototypes

// This function initalizes a font
SDLFont *initFont(char *fontdir, float r, float g, float b, float a);

// Some overloaded functions to make your life easier
inline SDLFont *initFont(char *fontdir, float r, float g, float b) { return initFont(fontdir, r,g,b,1); }
inline SDLFont *initFont(char *fontdir) { return initFont(fontdir, 1,1,1,1); }

// This function draws a string
void DrawString(SDL_Surface *screen, SDLFont *font, int x, int y, char *str,...);

// This function returns the width of a string
int StringWidth(SDLFont *font, char *str,...);

// This function destroys the font
void FreeFont(SDLFont *font);
