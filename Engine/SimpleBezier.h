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

#ifndef SIMPLEBEZIER_H
#define SIMPLEBEZIER_H

#include "Vector3.h"

class SimpleBezier {
public:
	//private:
	int m_iControlPointCount;
	Vector3 *m_pControlPoints;

	// returns a point on the curve for a value t in [0,1]
	Vector3 calculatePoint(float t);

	int calculateFactorial(int number); // factorial of number
	int calculateBinomialCoefficient(int n, int k); // (n choose k)
	// Bernstein polynomial of degree m_iControlPointCount
	float calculateBernsteinPolynomial(float t, int i);

public:
	SimpleBezier();
	SimpleBezier(Vector3 vPoint0, Vector3 vPoint1, Vector3 vPoint2);
	SimpleBezier(Vector3 vPoint0, Vector3 vPoint1, Vector3 vPoint2,
		     Vector3 vPoint3);
	~SimpleBezier();

	void draw();
};

#endif
