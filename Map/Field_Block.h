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

#ifndef Field_Block_H
#define Field_Block_H

#include "Field.h"

class Field_Block : public Field {
protected:
private:
	// to make it look more interessting, we allow each block to rotate around the y-axis (in 90° steps)
	float m_iOrientation;

public:
	Field_Block(int xGrid, int yGrid, Map *pMap);

	bool placeBomb(Bomb *bomb);
	void destroy() {};

	void draw();
	void update();
};

#endif
