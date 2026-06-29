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

#ifndef CTriangle_H
#define CTriangle_H

#include <glm/glm.hpp>;

// Data specified per triangle
class CTriangle {
public:
	// Each triangle has three points (vectors)
	int nVertex[3];

	glm::vec3 *pVertex[3];

	// each with an x,y texture coordinate
	float texCoordX[3];
	float texCoordY[3];

	// The index number of the surface's material
	int nMaterial;

	// The following two fields are not needed, as the info is in the material
	// Is this triangle textured
	bool bTexture;
	// The index number of the texture
	int iTextureIndex;

	// The center point of the triangle
	glm::vec3 vMiddle;

	// The normal vector of the triangle
	glm::vec3 vNormal;

	// The distance from the plane spanned by the triangle to the origin
	float distanceToOrigin;
};

#endif
