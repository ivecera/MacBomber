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

#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3::~Vector3()
{
}

Vector3::Vector3(float xp, float yp, float zp)
{
	x = xp;
	y = yp;
	z = zp;
}

Vector3 const Vector3::operator+(const Vector3 &vector2)
{
	return Vector3(x + vector2.x, y + vector2.y, z + vector2.z);
}

Vector3 const Vector3::operator-(const Vector3 &vector2)
{
	return Vector3(x - vector2.x, y - vector2.y, z - vector2.z);
}

Vector3 const Vector3::operator*(float skalar)
{
	return Vector3(skalar * x, skalar * y, skalar * z);
}

Vector3 Vector3::operator/(float skalar)
{
	return Vector3(x / skalar, y / skalar, z / skalar);
}

void Vector3::showElements()
{
	cout << x << " / " << y << " / " << z << endl;
}
