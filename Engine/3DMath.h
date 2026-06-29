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

#ifndef DMath_H
#define DMath_H

#include "Vector3.h"

/// Calculates the cross product of two vectors
Vector3 crossProduct(const Vector3 &u, const Vector3 &v);

/** Calculates the dot product of two vectors
 *
 *  \param u,v the vectors whose dot product should be computed
 *  \return The dot product of u and v
 */
float dotProduct(const Vector3 &u, const Vector3 &v);

/** Calculates the length of vector v
 *
 * \return The length of vector v
 *
 */
float magnitude(const Vector3 &v);

/** Calculates the unit vector (a vector with same direction but length one)
 * \param v The vector to normalize
 * \return The normalized vector
 *
 */
Vector3 normalize(Vector3 &v);

//rotates a given point in the x/z plane around the y axis
void rotateAroundYAxis(float &x, float &z, float theta);

#endif
