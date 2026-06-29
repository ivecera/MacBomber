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

#ifndef BILLBOARD_H
#define BILLBOARD_H
class Vector3;
class Camera;

void createBillboardMatrix(const Vector3 &vPos, const Vector3 &vLook,
			   const Vector3 &vUp, const Vector3 &vRight,
			   float *pMatrix);

void calculateBillboardMatrix_Point(const Vector3 &vPos, float *pMatrix);
void calculateBillboardMatrix_Xaxis(const Vector3 &vPos, float *pMatrix);
void calculateBillboardMatrix_Yaxis(const Vector3 &vPos, float *pMatrix);
void calculateBillboardMatrix_Zaxis(const Vector3 &vPos, float *pMatrix);

#endif
