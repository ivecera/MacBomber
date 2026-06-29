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

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Vector3.h"
#include "../Defines.h"

// We only deal with square bounding boxes
// So we include a bounding circle as well
class BoundingBox_2D {
private:
	// This is a 2D bounding box, so four corner points
	// These vectors give the position of the corners RELATIVE to the object center (0,0,0)
	//
	//      0--------1
	//      |        |
	//      |        |
	//      3--------2

	// The position of the bounding box in world space
	Vector3 m_vPos;
	float m_fRadius;

public:
	Vector3 m_vMin;
	Vector3 m_vMax;

	Vector3 m_vVertex[4];
	Vector3 m_vVertex_Worldspace[4];

	// Parameters: start world position + the min/max vertices of the 3D bounding box
	BoundingBox_2D(Vector3 vPos, float size);

	//Updates the world space coordinates
	void update(Vector3 &vPos);

	//checks fixed bboxes for collision
	bool doesCollideWith(BoundingBox_2D *pBBox);

	//checks if moving pBBox collides with this static boundingbox. returns true if yes
	// vVelocityVector: m_vDisplacement * vVelocity
	// time: contains time of collision
	bool doesCollide(BoundingBox_2D *pBBox, const Vector3 &vVelocityVector,
			 float &time);
};

#endif
