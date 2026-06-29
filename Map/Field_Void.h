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

#ifndef FIELD_VOID_H
#define FIELD_VOID_H

#include "Field.h"
#include <list>

//FIX ME: Item/Bomb handling is messy. Clean up (e.g convert Items to moving_objects)

class Field_Void : public Field {
protected:
	// FIX ME: this is not a clean solution....
	struct SBombContainer {
		Object_Moving *pObject;
		bool bDoesFall;
	};

	//Liste, die alle fallenden Bomben enthält
	list<SBombContainer> m_lBombList;
	// Returniert true wenn die Bombe fallen darf (Mittellinie überschrittenn)
	bool startFall(Object_Moving *pObject);
	bool stopFall(Object *pObject);

public:
	Field_Void(int xGrid, int yGrid, Map *pMap);
	~Field_Void();

	bool hasBomb();
	bool placeBomb(Bomb *bomb);
	void placeItem(Item *pItem);
	void destroy();

	void moveBomb();
	void update();
	void draw();
	void drawBombs();
};

#endif
