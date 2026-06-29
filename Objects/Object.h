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

#ifndef OBJECT_H
#define OBJECT_H

#include "../Engine/Vector3.h"
#include "../Engine/BoundingBox_2D.h"

/*
 * This class describes an object on the game field.
 * An object can be a player or a bomb.
 *
 */

class Wobbler;

class Object {
protected:
	//what kind of object is this ?
	int m_iType;

	// The position of the object on the game field in blocks
	int m_xBlock;
	int m_zBlock;

	Vector3 m_vPos; // The position of the object's center on the game field in world coordinates
	float m_fSize; // The side length of the object

	BoundingBox_2D *m_pBBox;

	// m_pWobbbler is used to scale the object on up to 3 axis, thus causing a "wobbling" effect
	bool m_bWobble; //true if Object should "wobble"
	Wobbler *m_pWobbler;

public:
	// The following values are passed to the constructor:
	//      xBlock  -   the x position of the object in block coordinates
	//      zBlock  -   the z position of the object in block coordinates
	//      size    -   the length of the object's bounding box (default = 1)

	Object(int xBlock, int zBlock, float size = 1.0f);
	virtual ~Object();

	int getXBlock();
	int getZBlock();

	int getType()
	{
		return m_iType;
	};
	float getSize();
	void setPosition(Vector3 vPos);
	Vector3 getPosition();
	BoundingBox_2D *getBoundingBox();

	// Checks whether this object collides with another
	bool doesCollideWith(Object *pObject);

	void setWobble(bool bWobble);
	virtual void draw() = 0;
};

#endif