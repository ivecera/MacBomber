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

#include "CVector3.h"

CVector3::CVector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	
}
CVector3::~CVector3()
{
}

CVector3::CVector3( float xp, float yp, float zp)
{
	x = xp;
	y = yp;
	z = zp;
}


CVector3 const CVector3::operator+( const CVector3 & vector2 )
{
	return CVector3( x + vector2.x, y + vector2.y, z + vector2.z);
}

CVector3 const CVector3::operator-( const  CVector3& vector2 )
{
	return CVector3( x - vector2.x, y - vector2.y, z - vector2.z);
}


CVector3 const CVector3::operator*( float skalar )
{
	return CVector3( skalar * x, skalar * y, skalar * z);
}

CVector3  CVector3::operator/( float skalar )
{
	return CVector3( x / skalar, y / skalar , z / skalar );
}


void CVector3::showElements()
{
	cout << x << " / " << y << " / " << z << endl;
}
