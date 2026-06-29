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

#include "../Defines.h"
#include "CField.h"
#include "CMap.h"
#include "../Objects/CItem.h"
#include "../Objects/CItem_PowerUp.h"
#include "../Objects/CItem_BombUp.h"
#include "../Objects/CItem_SpeedUp.h"
#include "../Objects/CItem_EnableKick.h"
#include "../Objects/CItem_Cocaine.h"
#include "../Objects/CItem_Joint.h"
#include "../Objects/CItem_Viagra.h"
#include "../Objects/CItem_Condom.h"

#include "../CExplosion.h"
#include "../CConfig.h"
#include "CApplication.h"
#include "../Engine/CMeshManager.h"

#include "../Engine/ParticleSystem/CParticleManager.h"
#include "../Engine/CBoundingBox_2D.h"
#include "../Engine/3DMath.h"

CField::CField( int xGridPos, int zGridPos, CMap *pMap )
{
    
    m_iType = FIELD;

    m_bBomb = false;
	m_bFree = true;
	m_bCrate = false;
	m_bItem = false;
	
    m_pBomb = NULL;
	m_pCrate = NULL;
	m_pItem = NULL;
	m_pMap = pMap;
	
    m_iXGrid = xGridPos;
    m_iZGrid = zGridPos;
    
    // Berechnne aus der Gitterposition die Position des Blocks seine Welt Koordinaten
    // Diese einfache Zuweisung funktioniert, weil die Blocklänge 1 ist.
    m_vMin.x = xGridPos;
    m_vMin.z = zGridPos;
    m_vMax.x = xGridPos+1;
    m_vMax.z = zGridPos+1;
	m_vPos.x = float(xGridPos) + 0.5f;
	m_vPos.y = 0.0f;
	m_vPos.z = float(zGridPos) + 0.5f;

	m_pBBox = new CBoundingBox_2D(m_vPos,1);

	//init a random rotation vector
	m_fAngle = 0;
	m_vRotationAxis.x = 0;
	m_vRotationAxis.y = 1;		
	m_vRotationAxis.z = 0;
	
	// +0.5 y, damit die Explosion auf dem Feld ist
	m_pExplosion = new CExplosion(m_vPos + CVector3(0,0.5,0));
	
	m_iState = NORMAL;

}

CField::~CField()
{
	if ( m_pBomb != NULL )
	{
		//falling fields may contain bombs
		CMap::m_iBombsOnField[m_pBomb->getOwnerID()]--;
		delete m_pBomb;
	}

	if ( m_pCrate != NULL )
		delete m_pCrate;

	if ( m_pItem != NULL)
		delete m_pItem;
	
	delete m_pExplosion;

/*	if ( m_pItemParticleSystem != NULL)
		delete m_pItemParticleSystem;
*/		
	delete m_pBBox;

}
void CField::checkBomb()
{
	//only check bomb, if there is actually a bomb
	if (m_bBomb)
	{	
		m_pBomb->update();
		
		//did the bomb explode ?
		if ((m_iState == NORMAL) && (m_pBomb->m_StartExplosionTimer.isTimeUp()))
		{
			m_pBomb->explode();
			destroy();
		}
		else
		// a bomb could have entered the field while it is burning
		if ( m_iState == BURNING)
		{
			m_pBomb->explode();
			destroy();
		}
		
	
	}
	
}

void CField::explodeField(int iSteps, CVector3 vDir, int x, int z)
{
	// Abbruch falls out of Bounds / max. Anzahl an Steps erreicht /  erreichtes Feld ist Block / erreichtes Feld hat Crate
	if ( (x < 0) || ( x == m_pMap->getWidth()) || ( z < 0 ) || ( z == m_pMap->getHeight()) || (iSteps == 0) ||
		 (m_pMap->getType(x,z) == BLOCK)  )
		return;
	
	// has this newly reached field an Crate or Item?
	bool bStop = ( m_pMap->hasCrate(x,z) || m_pMap->hasItem(x,z) );
	
	m_pMap->destroyBlock(x,z);
	int nextX = (x + (int)vDir.x);
	int nextZ = (z + (int)vDir.z);

	// Only proceed with explosion if we didn't reach a crate or item
	if (!bStop)
		explodeField(--iSteps,vDir, nextX, nextZ);
	else
		return;
}

void CField::generateItem()
{
		
	switch (rand()%9)
	{
		case 0:
			if ( CApplication::m_pConfig->getPower() )
			{
				m_pItem = new CItem_PowerUp(m_iXGrid, m_iZGrid);
				m_bItem = true;
			}
			break;
		case 1:
			if ( CApplication::m_pConfig->getBomb() )
			{
				m_pItem = new CItem_BombUp(m_iXGrid, m_iZGrid);
				m_bItem = true;
			}
			break;
		case 2:
			if ( CApplication::m_pConfig->getSpeed() )
			{
				m_pItem = new CItem_SpeedUp(m_iXGrid, m_iZGrid);
				m_bItem = true;
			}
			break;
		case 3:
			switch (rand()%2)
			{
				case 0:
				if ( CApplication::m_pConfig->getKick() )
				{
						m_pItem = new CItem_EnableKick(m_iXGrid, m_iZGrid);
						m_bItem = true;
				}
				break;
				default:
					m_bItem = false;
					m_pItem = NULL;
					break;
			}
			break;
		case 4:
		case 5:
			switch (rand()%7)
			{
				case 0:
					if ( CApplication::m_pConfig->getJoint() )
					{
						m_pItem = new CItem_Joint(m_iXGrid, m_iZGrid);
						m_bItem = true;
					}
					break;
				case 1: 
					if ( CApplication::m_pConfig->getCondom() )
					{
						m_pItem = new CItem_Condom(m_iXGrid, m_iZGrid);
						m_bItem = true;
					}
					break;
				case 2:
					if ( CApplication::m_pConfig->getCocaine() )
					{
						m_pItem = new CItem_Cocaine(m_iXGrid, m_iZGrid);
						m_bItem = true;
					}
					break;
				case 3:
					if ( CApplication::m_pConfig->getViagra() )
					{
						m_pItem = new CItem_Viagra(m_iXGrid, m_iZGrid);
						m_bItem = true;
					}
					break;					
				default:
					m_bItem = false;
					m_pItem = NULL;
					break;

			}
			break;
		default:
			m_bItem = false;
			m_pItem = NULL;
			break;
	}
	
}


void CField::destroy()
{
	m_iState = BURNING;
	m_EndOfExplosion.setAlarm(500);
	m_pMap->m_ParticleManager.addExplosionParticle(m_vPos);
	
	//if there exists an crate on this field, generate an item
    if (m_bCrate)
	{
		generateItem();
		m_bCrate = false;
		CVector3 vPos = m_vPos;
		vPos.y = 1;
		m_pMap->m_ParticleManager.addCrateParticle(vPos,3);

	}
	else
	// else: is there an item on this field ?
	if (m_bItem)
	{
		delete m_pItem;
		m_pItem = NULL;

		m_bItem = false;
	}

	
    if ( m_bBomb )
    {
		m_bBomb = false;
		explodeField(m_pBomb->getStrength(), CVector3(0,0,1), m_iXGrid, m_iZGrid+1);
		explodeField(m_pBomb->getStrength(), CVector3(0,0,-1), m_iXGrid, m_iZGrid-1);
		explodeField(m_pBomb->getStrength(), CVector3(1,0,0), m_iXGrid+1, m_iZGrid);
		explodeField(m_pBomb->getStrength(), CVector3(-1,0,0), m_iXGrid-1, m_iZGrid);
		
		m_pBomb->explode();
		CMap::m_iBombsOnField[m_pBomb->getOwnerID()]--;
		delete m_pBomb;
		m_pBomb = NULL;
	}

	m_pMap->doShake();
    m_bFree = true; 
}

void CField::dispatchBomb()
{
	m_bBomb = false;
	m_pBomb = NULL;
	m_bFree = true;		
}

void CField::placeItem ( CItem * item )
{
	// Auf dem Feld steht bereits ein Item
	if (m_bItem)
	{
		delete m_pItem; // altes Item löschen
		m_pItem = item; 
	}
	else
	{
		m_bItem = true;
		m_pItem = item;
	}
}

void CField::dispatchItem()
{
	m_pMap->m_ParticleManager.addItemParticle(m_vPos,6,m_pItem->getType());
	m_pItem = NULL;
	m_bItem = false;
	
}


int CField::getType()
{
    return m_iType;
}



CBomb * CField::getBomb()
{
    return m_pBomb;
}

// steht auf dem Block eine Bombe
bool CField::hasBomb()
{
    return m_bBomb;
}


// steht auf dem Block ein Crate
bool CField::hasCrate()
{
    return m_bCrate;
}

// ist das Feld begehbar ?
bool CField::isFree()
{
    return m_bFree;
}

bool CField::isExploding()
{	
	if ( m_EndOfExplosion.isTimeUp())
		return false;
	else
		return true;
}


float CField::getMinX()
{
    return m_vMin.x;
}

float CField::getMinZ()
{
    return m_vMin.z;

}

float CField::getMaxX()
{
    return m_vMax.x;

}

float CField::getMaxZ()
{
    return m_vMax.z;

}


void CField::updateItem()
{
	if(m_bItem)
		m_pItem->update();
}


void CField::drawBombs()
{
	if (m_bBomb)
		m_pBomb->draw();
}

void CField::drawExplosion()
{
	if ( m_iState == BURNING )
		m_pExplosion->draw();
}

