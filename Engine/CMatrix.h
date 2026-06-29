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

#ifndef CMATRIX
#define CMATRIX

#include "CVector3.h"

class CMatrix
{

public:
    
    // Die obere Hälfter der Matrix beschreibt die Rotation
    float m11, m12, m13; 
    float m21, m22, m23;
    float m31, m32, m33;
    
    // Die Translations Vektoren
    float tx, ty, tz;
    
    CMatrix();
    
    // Setzt eine Rotationsmatrix um die ( normalisierte ) Achse "axis" und den Winkel "theta"
    void setupRotation( CVector3 axis, float theta );
    
};

#endif