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

#ifndef FIELD_PLAIN_H
#define FIELD_PLAIN_H

#include <SDL3/SDL_opengl.h>

#include "Field.h"
#include <glm/glm.hpp>
#include "../Objects/Bomb.h"

class Item;
class Timer;
class Map;

class Field_Plain : public Field {
private:
	//plain fields can have a second decal texture (mud, flowers, etc..)
	bool m_bDecal; // true, if a mud texture should be drawn on the main texture
	int m_iDecalTexture; // index of the fields second decal texture
	int m_iDecalOrientation; // specifies in which direction the decal should be rotated
	void placeCrate();

public:
	Field_Plain(int xGrid, int yGrid, bool bCrate, Map *pMap);

	~Field_Plain();

	// Returns true if a bomb could be placed
	bool placeBomb(Bomb *bomb);
	void moveBomb();
	void kickBomb(int dir);
	void update();
	void draw();
};

#endif
