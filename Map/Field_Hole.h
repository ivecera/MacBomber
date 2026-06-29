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

#ifndef FIELD_HOLE_H
#define FIELD_HOLE_H

#include "../Map/Field.h"
//#include "../Objects/BombThrower.h"
//#include "../Objects/ObjectThrower.h"
#include <list>

//class CParticleSystem_Hole;
class Timer;

class Field_Hole : public Field {
protected:
	struct SBombContainer {
		Bomb *pBomb;
		bool bDoesFall; // Is the bomb still moving toward the field center?
		bool bDoesFly; // Has it already been catapulted?
		Timer tDelayTimer; // Only catapult when the delay is over
		bool bDraw;
	};

	// contains all bombs, which are moving _into_ the hole
	list<SBombContainer> m_lBombList;

	bool startFall(Bomb *pBomb);
	bool stopFall(Bomb *pBomb);

	Timer m_tParticleDeactivationTimer;

public:
	Field_Hole(int xGrid, int yGrid, Map *pMap);
	~Field_Hole();

	bool hasBomb();

	bool placeBomb(Bomb *bomb);

	void moveBomb();
	void update();
	void draw();
	void drawBombs();
};

#endif
