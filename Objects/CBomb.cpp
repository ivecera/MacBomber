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

#include "CBomb.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTriangleMesh.h"
#include "../MeshObjects/CBombMesh.h"

#include "../Defines.h"
#include "../CApplication.h"
#include "../Engine/CSoundManager.h"
#include "../Engine/CWobbler.h"
int CBomb::m_iBombNr = 0;



CBomb::CBomb( int xBlock, int zBlock, int owner, int strength ): CObject_Moving( xBlock, zBlock, 0.9f )
{	
	m_iType = BOMB_OBJECT;

	m_iOwnerID	= owner;
	m_bOwnerLeft = false;
	
    m_iStrength = strength;
    m_bExploded = false;
    
	m_StartExplosionTimer = CTimer(2500);

	m_fVelocity = 3;
	m_iBombID = m_iBombNr++;

	m_bWobble = true;
	m_pWobbler->setRads(0.785,2.35,0.785);
	m_pWobbler->setMedians(0.8,0.9,0.8);

    m_vPos.y = 0.0f;

}

void CBomb::explode()
{
    // Wenn es sich um eine Bombe in Bewegung handelt, dann stoppe die Bewegung
	m_iDirection = NONE;
    m_bExploded = true;
	
	CApplication::m_pSoundManager->playSoundFX(EXPlOSION_SOUND);
}

bool CBomb::isExploded()
{
    return m_bExploded;
}

int CBomb::getStrength()
{
    return m_iStrength;
}

bool CBomb::doesMove()
{
	if ( m_iDirection == NONE)
		return false;
	else
		return true;
}


void CBomb::stopMovement()
{
    m_iDirection = NONE;
	m_vPos.x =  m_xBlock + 0.5f;
	m_vPos.z =  m_zBlock + 0.5f;

}



void CBomb::update()
{
	if (m_bWobble)
		m_pWobbler->update();
}

void CBomb::draw()
{
	 glPushMatrix();
	   glTranslatef(m_vPos.x, m_vPos.y,m_vPos.z);
	   
	   if (m_bWobble)
		   glScalef(m_pWobbler->getScaleValueX(),m_pWobbler->getScaleValueY(),m_pWobbler->getScaleValueZ());

		CApplication::m_pMeshManager->m_pBombMesh->drawVBO();
		
	glPopMatrix();

}
