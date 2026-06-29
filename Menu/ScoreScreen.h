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
#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include "../Engine/Vector3.h"
class Game;
class Player;
class Wobbler;

class ScoreScreen {
private:
	struct stRow {
		//stores first slot (player) of row
		Vector3 position;

		int iColumns;
		Player *pPlayer;
	};

	Game *m_pGame;
	//the Heading of the score screen
	char m_cHeading[100];
	// true if the scorescreen should be left (because of User input)
	bool m_bDone;
	// true when input should not handled
	// prevents that players misses the scorescreen
	bool m_bDoHandleInput;

	bool m_bPaused;

	//New Cup Position
	Vector3 m_vCupPosition;
	// rotation angle of Cup
	float m_fCupRotationAngle;

	//position of the first Row on screen
	Vector3 m_vFirstRowPosition;
	//spacing between elements of a row / between rows
	float m_fColumnSpacing;
	float m_fRowSpacing;
	//an offset to the first colum
	float m_fOffsetLeft;

	//row count
	int m_iRows;
	//pointer to the rows
	stRow *m_pRows;

	//Wobbler used for wobbling the winners cup
	Wobbler *m_pWobbler;

	// handles Input
	void handleInput();

	// animates / draws the the winners cup on its way to position row/col
	void drawCup();

public:
	ScoreScreen(Game *pGame);
	~ScoreScreen();

	bool done()
	{
		return m_bDone;
	};

	void startPause();
	void stopPause();

	void update();
	void draw();
};

#endif
