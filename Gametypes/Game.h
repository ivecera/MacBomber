/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef GAME_H
#define GAME_H

#include <SDL_opengl.h>

#include "../Config.h"
#include "../Engine/Timer.h"
#include "../Defines.h"

class Player;
class Map;
class MapManager;
class ScoreScreen;
class Application;
class HUD;
class MapPlaylist;

class Game {
protected:
	// the amount of rounds to be played
	int m_iRounds;
	//the current Round
	int m_iCurrentRound;
	int m_iPlayerScore[4];
	int m_iAlivePlayerCount;
	//the winner of the current round (NONE if there is no winner)
	int m_iWinner;

	// true if a game is finished (either by abort or by reaching m_iRounds)
	bool m_bDone;

	Player *m_pPlayer[4];
	Map *m_pMap;
	Application *m_pApp;
	MapManager *m_pMapManager;
	ScoreScreen *m_pScoreScreen;
	HUD *m_pHUD;
	// This timer counts the round time
	// if player count <= 1 then set reset the timer to e.g 2 sec!
	Timer m_tRoundTimer;
	// true if the clock has been reset to end the round ahead of time
	bool m_bDeathBell;

	//contains the indices to all maps to be played
	MapPlaylist *m_pPlaylist;

	// A Game can be in two states
	// RUNNNIG		game is running
	// DONE			Player has won the entire game / or Abort by Player
	// SCORESCREEN	the score screen between two games is displayed
	enum states { RUNNING = 0, GAMEOVER, SCORESCREEN };
	// in which mode are we currently ?
	int m_iState;
	//is game paused?
	bool m_bPaused;

	//a Displaylist to fill the background with a textured quad
	GLuint m_iBackgroundDL;
	void compileBackgroundDisplayList();
	// gets called once if time is Up. Returns winning player index or
	int determineWinner();
	Application *pApp;

	void _startNextRound();
	void updateScoreScreen();
	virtual void updateRunning() = 0;
	virtual void drawRunning() = 0;

public:
	Game(Application *pApp);
	virtual ~Game();

	virtual void startNextRound() = 0;

	//returns the current Round
	int getCurrentRound()
	{
		return m_iCurrentRound;
	};
	//returns max Rounds
	//int getTotalRounds(){return m_iRounds;};
	// returns the player count;
	int getPlayerCount();
	// returns the winner of the last round
	int getWinnerOfRound()
	{
		return m_iWinner;
	};
	// returns the Score of playerNr
	int getPlayerScore(int playerNr)
	{
		return m_iPlayerScore[playerNr];
	};
	Player *getPlayer(int playerNr);

	// returns elapsed game Time
	uint getElapsedTime();
	//returns total game Time
	uint getTotalTime();

	// updates Game.
	void update();
	// pauses / continues games
	void startPause();
	void stopPause();
	bool isPaused();

	// aborts game
	void abort();
	void draw();
};
#endif
