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

#include <SDL3/SDL.h>
#include "Matrix.h"

Matrix::Matrix()
{
}

void Matrix::setupRotation(Vector3 axis, float theta)
{
	// Calculate sine and cosine of theta once
	float sinTheta = SDL_sinf(theta);
	float cosTheta = SDL_cosf(theta);

	// We will use ( 1 - cos ( theta ) ) frequently in the rotation matrix
	float a = 1.0f - cosTheta;

	/*
     * The following expressions also appear frequently in the matrix,
     * so we precompute them as well.
     */

	float ax = axis.x * a;
	float ay = axis.y * a;
	float az = axis.z * a;

	/* From this matrix:

    m11 = axis.x * axis.x * a + cosTheta;
    m12 = axis.x * axis.y * a + axis.z * sinTheta;
    m13 = axis.x * axis.z * a - axis.y * sinTheta;

    m21 = axis.x * axis.y * a - axis.z * sinTheta;
    m22 = axis.y * axis.y * a + cosTheta;
    m23 = axis.y * axis.z * a + axis.x sinTheta;

    m31 = axis.x * axis.z * a + axis.y * sinTheta;
    m32 = axis.y * axis.z * a - axis.x * sinTheta;
    m33 = axis.z * axis.z * a + cosTheta;

    becomes: */

	m11 = ax * axis.x + cosTheta;
	m12 = ax * axis.y + axis.z * sinTheta;
	m13 = ax * axis.z - axis.y * sinTheta;

	m21 = ay * axis.x - axis.z * sinTheta;
	m22 = ay * axis.y + cosTheta;
	m23 = ay * axis.z + axis.x * sinTheta;

	m31 = az * axis.x + axis.y * sinTheta;
	m32 = az * axis.y - axis.x * sinTheta;
	m33 = az * axis.z + cosTheta;

	// Since we only want a rotation matrix, set the translation elements to 0
	tx = 0.0f;
	ty = 0.0f;
	tz = 0.0f;
}
