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

#ifndef OBJECT_MOVING_H
#define OBJECT_MOVING_H

#include "Object.h"
#include "../Defines.h"
class Object_Moving : public Object {
protected:
	float m_fVelocity;
	glm::vec3 m_vDisplacement =
		glm::vec3(0.0f); // The direction of the player
	int m_iDirection; // The direction of the player (UP = 0; RIGHT, DOWN, LEFT)

	bool m_bDoesDrop; // True when this variable has been set to true

	// Rotate Object around m_fAngle around Y-Axis depepnding on its direction.
	// Usually this variable has one of the following values: 0,90,180,-90 or similar
	float m_fOrientation;

public:
	Object_Moving(int xBlock, int zBlock, float size = 1.0f);

	float getVelocity()
	{
		return m_fVelocity;
	};
	int getDirection()
	{
		return m_iDirection;
	};
	void setDisplacement(glm::vec3 vDisplacement);
	glm::vec3 getDisplacement()
	{
		return m_vDisplacement;
	};
	void setVelocity(float speed)
	{
		m_fVelocity = speed;
	};
	void setDirection(int dir);

	bool doesDrop()
	{
		return m_bDoesDrop;
	};
	void setDrop(bool bDrop);

	// moves object according to specified displacment
	// uesd to correct collision
	void move(glm::vec3 vDisplacement);
	virtual void move();
	// Returns true if the object is falling, false if the fall duration has expired
	bool doDrop();
};
#endif
