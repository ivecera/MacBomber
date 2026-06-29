/*
 *  Game_Standard.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_STANDARD_H
#define GAME_STANDARD_H

#include "Game.h"

class Application;

class Game_Standard : public Game {
private:
	void updateRunning();
	void drawRunning();

public:
	Game_Standard(Application *pApp);
	~Game_Standard();

	void startNextRound();
};

#endif