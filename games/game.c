//==========================================================================
// Mouse Injector Plugin
//==========================================================================
// Copyright (C) 2018 Carnivorous
// All rights reserved.
//
// Mouse Injector is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, visit http://www.gnu.org/licenses/gpl-2.0.html
//==========================================================================
#include <stdlib.h>
#include "game.h"

extern const GAMEDRIVER *GAME_GOLDENEYE007;
extern const GAMEDRIVER *GAME_PERFECTDARK;

static const GAMEDRIVER **GAMELIST[] =
{
	&GAME_GOLDENEYE007,
	&GAME_PERFECTDARK
};

static const GAMEDRIVER *CURRENT_GAME = NULL;

int GAME_Status(void);
const char *GAME_Name(void);
void GAME_Inject(void);
void GAME_Quit(void);

int GAME_Status(void)
{
	const int upper = (sizeof(GAMELIST) / sizeof(GAMELIST[0]));
	const GAMEDRIVER *THIS_GAME;
	CURRENT_GAME = NULL;
	for(int i = 0; (i < upper) && (CURRENT_GAME == NULL); i++)
	{
		THIS_GAME = *(GAMELIST[i]);
		if(THIS_GAME != NULL && THIS_GAME->Status())
			CURRENT_GAME = THIS_GAME;
	}
	return CURRENT_GAME != NULL ? 1 : 0;
}

const char *GAME_Name(void)
{
	return CURRENT_GAME ? CURRENT_GAME->Name : NULL;
}

void GAME_Inject(void)
{
	if(CURRENT_GAME)
		CURRENT_GAME->Inject();
}

void GAME_Quit(void)
{
	if(CURRENT_GAME)
		CURRENT_GAME->Quit();
	CURRENT_GAME = NULL;
}