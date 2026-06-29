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

#include "../CApplication.h"
#include "CBoundingBox_2D.h"
#include "3DMath.h"

CBoundingBox_2D::CBoundingBox_2D(CVector3 vPos, float size )

{
    // Initialisiere das VertexArray für die Box
	//      0--------1
    //      |        |
    //      |        |
    //      3--------2
	
	m_vVertex[0].x = -(size/2);
    m_vVertex[0].z = -(size/2);
	
    m_vVertex[1].x = (size/2);
    m_vVertex[1].z = -(size/2);
    
    m_vVertex[2].x = (size/2);
    m_vVertex[2].z = (size/2);
	
    m_vVertex[3].x = -(size/2);
    m_vVertex[3].z = (size/2);
	
	m_fRadius = size/2;
	m_vPos = vPos;
	

	m_vPos = vPos;
	update(m_vPos);
}

void CBoundingBox_2D::update(CVector3 & vPos)
{
	m_vVertex_Worldspace[0] = m_vVertex[0] + vPos;
	m_vVertex_Worldspace[1] = m_vVertex[1] + vPos;
	m_vVertex_Worldspace[2] = m_vVertex[2] + vPos;
	m_vVertex_Worldspace[3] = m_vVertex[3] + vPos;

	m_vMin = m_vVertex_Worldspace[0];
	m_vMax = m_vVertex_Worldspace[2];

	m_vPos = vPos;

}	

bool CBoundingBox_2D::doesCollideWith(CBoundingBox_2D * pBBox)
{
/*	printf("thisX: [1]:%f [3]:%f\n", m_vVertex_Worldspace[1].x,m_vVertex_Worldspace[3].z);
	printf("pBBox: [1]:%f [3]:%f\n", pBBox->m_vVertex_Worldspace[1].x,pBBox->m_vVertex_Worldspace[3].z);
	printf("\n");
*/	

	if ( m_vVertex_Worldspace[1].x < pBBox->m_vVertex_Worldspace[3].x )
		return false;
	if ( m_vVertex_Worldspace[0].x > pBBox->m_vVertex_Worldspace[1].x )
		return false;
	
	if ( m_vVertex_Worldspace[1].z > pBBox->m_vVertex_Worldspace[3].z )
		return false;
	if ( m_vVertex_Worldspace[3].z < pBBox->m_vVertex_Worldspace[1].z )
		return false;
	
	return true;
}


bool CBoundingBox_2D::doesCollide(CBoundingBox_2D * pBBox,const CVector3 & vVelocityVector, float &time)
{
	//performs an parametric collision detetcion
	
	float tEnterX = 66;	//time when pBBox will enter (collide) this boundingbox on x axis
	float tLeaveX = 66;	//time when pBBox will leave this boundingbox on x axis
	float tEnterZ = 66;	//time when pBBox will enter (collide) this boundingbox on z axis
	float tLeaveZ = 66;	//time when pBBox will leave this boundingbox on z axis
	
	
	//check on x-Axis  (if necessary)
	if (vVelocityVector.x != 0)
	{
		tEnterX = (m_vMin.x - pBBox->m_vMax.x)	/ (CApplication::m_fReciprocalFPS * vVelocityVector.x);
		tLeaveX = (m_vMax.x - pBBox->m_vMin.x) / (CApplication::m_fReciprocalFPS * vVelocityVector.x);
		
		//we assume that pBBox is left to this pBBox
		//we have to swap tEnter & tLeave if it's the other way round.
		if (tEnterX > tLeaveX)
			swap(tEnterX, tLeaveX);
		 			
	}
	
	//check on z-Axis
	if (vVelocityVector.z != 0)
	{
		tEnterZ = (m_vMin.z - pBBox->m_vMax.z)	/ (CApplication::m_fReciprocalFPS * vVelocityVector.z);
		tLeaveZ = (m_vMax.z - pBBox->m_vMin.z) / (CApplication::m_fReciprocalFPS * vVelocityVector.z);
		
		//we assume that pBBox is above  this pBBox
		//we have to swap tEnter & tLeave if it's the other way round.
		if (tEnterZ > tLeaveZ)
			swap(tEnterZ, tLeaveZ);
		 			
	}
	
	(tEnterX < tEnterZ)?time = tEnterX:time = tEnterZ;
	
//	printf("tEnter: %f\n",time);
	if  (time < 1)
		return true;
	else
		return false;
	
}


