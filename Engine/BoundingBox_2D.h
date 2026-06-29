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

// Wir haben es nur mit quadratischen BBoxes zu tun
// Also packen wir eine BoundingCircle gleich mit hinzu
class BoundingBox_2D {
private:
	// Es handelt sich um eine 2D Bounding Box. Also vier Eckpunkte
	// Diese Vektoren geben die Position der Eckpunkt RELATIV zum Objektmittelpunkt ( 0,0,0 ) an
	//
	//      0--------1
	//      |        |
	//      |        |
	//      3--------2

	// Die Position der BBox im Worldspace
	Vector3 m_vPos;
	float m_fRadius;

public:
	Vector3 m_vMin;
	Vector3 m_vMax;

	Vector3 m_vVertex[4];
	Vector3 m_vVertex_Worldspace[4];

	// Übergeben werden StartworldPis + die Minimalen / Maximalen Vertices der 3D Boundingbox
	BoundingBox_2D(Vector3 vPos, float size);

	//Updatet die Worldspace Koordinaten
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
