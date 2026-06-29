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

#ifndef FIELD_ARROW_H
#define FIELD_ARROW_H

#include "Field.h"

class Map;

class Field_Arrow : public Field {
protected:
	// Die Richtung in die Bomben geschubst werden sollen
	int m_iDirection;

	// Die X/Z Koordinaten des Blocks auf den die Bomben geschubst werden
	int m_iNextBlockX;
	int m_iNextBlockZ;
	Map *m_pMap;

	// Bestimmt, ob die Richtung der Bombe gedreht werden muss
	bool doFlip();

public:
	Field_Arrow(int xGrid, int yGrid, int direction, Map *m_pMap);

	bool placeBomb(Bomb *bomb);
	void moveBomb();
	void update();
	void draw();
};

#endif
