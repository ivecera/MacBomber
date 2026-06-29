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

#include <GLUT/glut.h>

#include "Billboard.h"
#include "Camera.h"
#include "Vector3.h"
#include "3DMath.h"
#include "../Application.h"

void createBillboardMatrix(const Vector3 &vPos, const Vector3 &vLook,
			   const Vector3 &vUp, const Vector3 &vRight,
			   float *pMatrix)
{
	pMatrix[0] = vRight.x;
	pMatrix[1] = vRight.y;
	pMatrix[2] = vRight.z;
	pMatrix[3] = 0;
	pMatrix[4] = vUp.x;
	pMatrix[5] = vUp.y;
	pMatrix[6] = vUp.z;
	pMatrix[7] = 0;
	pMatrix[8] = vLook.x;
	pMatrix[9] = vLook.y;
	pMatrix[10] = vLook.z;
	pMatrix[11] = 0;

	pMatrix[12] = vPos.x;
	pMatrix[13] = vPos.y;
	pMatrix[14] = vPos.z;
	pMatrix[15] = 1;
}

void calculateBillboardMatrix_Point(const Vector3 &vPos, float *pMatrix)
{
	Vector3 vLook = Application::m_pCamera->m_vPosition - vPos;
	vLook = normalize(vLook);
	Vector3 vRight = crossProduct(Application::m_pCamera->m_vUp, vLook);
	Vector3 vUp = crossProduct(vRight, vLook);

	createBillboardMatrix(vPos, vLook, vUp, vRight, pMatrix);
}

void calculateBillboardMatrix_Xaxis(const Vector3 &vPos, float *pMatrix)
{
	Vector3 vLook = Application::m_pCamera->m_vPosition - vPos;
	vLook.x = 0;
	vLook = normalize(vLook);
	Vector3 vUp(1, 0, 0);
	Vector3 vRight = crossProduct(vUp, vLook);
	createBillboardMatrix(vPos, vLook, vUp, vRight, pMatrix);
}

void calculateBillboardMatrix_Yaxis(const Vector3 &vPos, float *pMatrix)
{
	Vector3 vLook = Application::m_pCamera->m_vPosition - vPos;
	vLook.y = 0;
	vLook = normalize(vLook);
	Vector3 vUp(0, 1, 0);
	Vector3 vRight = crossProduct(vUp, vLook);
	createBillboardMatrix(vPos, vLook, vUp, vRight, pMatrix);
}

void calculateBillboardMatrix_Zaxis(const Vector3 &vPos, float *pMatrix)
{
	Vector3 vLook = Application::m_pCamera->m_vPosition - vPos;
	vLook.z = 0;
	vLook = normalize(vLook);
	Vector3 vUp(0, 0, 1);
	Vector3 vRight = crossProduct(vUp, vLook);
	createBillboardMatrix(vPos, vLook, vUp, vRight, pMatrix);
}