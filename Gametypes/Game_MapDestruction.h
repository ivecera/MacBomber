/*
 *  Game_MapDestruction.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_MAPDESTRUCTION_H
#define GAME_MAPDESTRUCTION_H

#include "Game.h"
#include "../Engine/Timer.h"

class Application;
class MapDestroyer;

class Game_MapDestruction : public Game {
private:
	//the guy, which knocks out the fields one by one
	MapDestroyer *m_pMapDestroyer;
	//is the mapDestroyer active ?
	bool m_bMapDestroyerActive;
	void updateRunning();
	void drawRunning();

	Timer m_tRoundTimer2;

public:
	Game_MapDestruction(Application *pApp);
	~Game_MapDestruction();

	void startNextRound();
};
#endif
