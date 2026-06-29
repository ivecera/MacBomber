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

#include "Shaker.h"

Shaker::Shaker()
{
}

Vector3 Shaker::doShake(Vector3 &vec1, Vector3 &vec2)
{
	float deltaX = (rand() % 2) * 0.1;
	float deltaZ = (rand() % 2) * 0.1;

	vec1.x = vec1.x + deltaX;
	vec2.x = vec2.x - deltaX;

	vec1.z = vec1.z + deltaZ;
	vec2.z = vec2.z - deltaZ;

	Vector3 vDelta = vec2 - vec1;

	// Random value between 0 and 1
	float t = (rand() % 100) * 0.01;
	Vector3 output = vec1 + (vDelta * t);
	return output;
}
