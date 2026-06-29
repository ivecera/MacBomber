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

#ifndef BOMB_H
#define BOMB_H

#include <SDL3/SDL_opengl.h>
#include <iostream>
#include <SDL3/SDL.h>

#include "../Defines.h"
#include "Object_Moving.h"
#include "../Engine/Timer.h"

class Bomb : public Object_Moving {
protected:
	int m_iOwnerID;
	int m_iBombID;
	bool m_bOwnerLeft;

	// Has the bomb exploded?
	// This variable is important for the bomb manager logic
	bool m_bExploded;

	// The maximum explosion radius of the bomb in tiles
	int m_iStrength;

	// The following values indicate how many tiles from the bomb are covered
	// in each of the 4 possible explosion directions
	int m_iRadius[4];

	// The time at which the bomb explodes
	float m_fExplosionTime;

public:
	static int m_iBombNr;

	Timer m_StartExplosionTimer;

	// Parameters: position, owner, and strength of the bomb
	Bomb(int xBlock, int zBlock, int owner, int strength);

	// Sets m_bExploded to true
	void explode();

	// Returns whether the bomb has exploded
	bool isExploded();
	int getStrength();

	int getOwnerID()
	{
		return m_iOwnerID;
	};
	int getBombID()
	{
		return m_iBombID;
	};

	bool hasOwnerLeft()
	{
		return m_bOwnerLeft;
	};
	void setOwnerLeft(bool b)
	{
		m_bOwnerLeft = b;
	};

	// Returns true if the bomb is moving
	bool doesMove();
	// Stops the movement
	void stopMovement();

	void update();
	void draw();
};

#endif
