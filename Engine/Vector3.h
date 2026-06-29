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

#ifndef Vector3_H
#define Vector3_H

#include <iostream>

using namespace std;

/**
  * Diese Klasse repräsentiert einen Vektor mit 3 Float Elementen x,y,z
  */
class Vector3 {
public:
	///param x,y,z Die x,y und z Elemente des Vektors

	float x;
	float y;
	float z;

	Vector3();
	~Vector3();

	/**
	  * \param x das x Element des Vektors
	  * \param y das y Element des Vektors
	  * \param z das z Element des Vektors
	  */
	Vector3(float x, float y, float z);

	/// Ueberladen des "+" Operators.
	Vector3 const operator+(const Vector3 &vector2);

	/// Ueberladen des "-" Operators.
	Vector3 const operator-(const Vector3 &vector2);

	/// Ueberladen des "*"  Operators. So koennnen wir den Vektor mir einem Skalar multiplizieren
	Vector3 const operator*(float skalar);
	/// Ueberladen des "/"  Operators. So koennen wir den Vektor mir einem Skalar dividieren
	Vector3 operator/(float skalar);

	/// gibt die Elemente des Vektors aus;
	void showElements();
};

#endif
