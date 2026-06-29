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

#include "3DMath.h"
#include <math.h>

#define PI 3.14159265

/**
 * Mit dem Kreuzprodukt zweier Vektoren berechnet man den Vektor, welcher Senkrecht zu der Ebene ist
 * den die beiden Vektoren aufspannen ( welcher Senkrecht ist zu beiden Vektoren )
 * Definiton:
 * u = ( u1, u2, u3 ) 
 * v = ( v1, v2, v3 )
 *
 * u x v = ( u2*v3 - u3*v2, u3*v1 - u1*v3, u2*v1 - u1*v2 );
 *
 */

CVector3 crossProduct ( const CVector3 &u, const CVector3 &v )
{
	
	CVector3 product;
	
	product.x = ( u.y * v.z - u.z * v.y );
	product.y = ( u.z * v.x - u.x * v.z );
	product.z = ( u.x * v.y - u.y * v.x );
	
	return product;

}

float dotProduct ( const CVector3 &u, const CVector3 &v )
{
	float x,y,z = 0;
	
	x = u.x * v.x;
	y = u.y * v.y;
	z = u.z * v.z;
	
	return ( x + y + z );

}


float magnitude ( const CVector3 &v )
{
	float product = dotProduct ( v, v );
	return sqrt( product );
}


// TODO: add const
CVector3 normalize (   CVector3 &v )
{
	float length = magnitude( v );
	CVector3 normalizedVector = v / length;

	return normalizedVector;
}

void rotateAroundYAxis(float &x,float &z, float theta)
{
	float _x;
	float _z; 
	//convert deg -> rad
	theta = (theta*PI/180);

	_x =  (   (cos(theta) * x) + (sin(theta) *z)	);
	_z =  ((-1*sin(theta) * x) + (cos(theta) *z)	); 

	x = _x;
	z = _z;
}

