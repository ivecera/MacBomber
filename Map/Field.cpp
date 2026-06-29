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
#include "Field.h"
#include "Map.h"
#include "../Objects/Item.h"
#include "../Objects/Item_PowerUp.h"
#include "../Objects/Item_BombUp.h"
#include "../Objects/Item_SpeedUp.h"
#include "../Objects/Item_EnableKick.h"
#include "../Objects/Item_Cocaine.h"
#include "../Objects/Item_Joint.h"
#include "../Objects/Item_Viagra.h"
#include "../Objects/Item_Condom.h"

#include "../Explosion.h"
#include "../Config.h"
#include "../Application.h"
#include "../Engine/MeshManager.h"

#include "../Engine/ParticleSystem/ParticleManager.h"
#include "../Engine/BoundingBox_2D.h"

Field::Field(int xGridPos, int zGridPos, Map *pMap)
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

	// Calculate the block's world coordinates from the grid position
	// This simple assignment works because the block length is 1.
	m_vMin.x = xGridPos;
	m_vMin.z = zGridPos;
	m_vMax.x = xGridPos + 1;
	m_vMax.z = zGridPos + 1;
	m_vPos.x = float(xGridPos) + 0.5f;
	m_vPos.y = 0.0f;
	m_vPos.z = float(zGridPos) + 0.5f;

	m_pBBox = new BoundingBox_2D(m_vPos, 1);

	//init a random rotation vector
	m_fAngle = 0;
	m_vRotationAxis.x = 0;
	m_vRotationAxis.y = 1;
	m_vRotationAxis.z = 0;

	// +0.5 y so the explosion is on the field
	m_pExplosion = new Explosion(m_vPos + glm::vec3(0, 0.5, 0));

	m_iState = NORMAL;
}

Field::~Field()
{
	if (m_pBomb != NULL) {
		//falling fields may contain bombs
		Map::m_iBombsOnField[m_pBomb->getOwnerID()]--;
		delete m_pBomb;
	}

	if (m_pCrate != NULL)
		delete m_pCrate;

	if (m_pItem != NULL)
		delete m_pItem;

	delete m_pExplosion;

	/*	if ( m_pItemParticleSystem != NULL)
		delete m_pItemParticleSystem;
*/
	delete m_pBBox;
}
void Field::checkBomb()
{
	//only check bomb, if there is actually a bomb
	if (m_bBomb) {
		m_pBomb->update();

		//did the bomb explode ?
		if ((m_iState == NORMAL) &&
		    (m_pBomb->m_StartExplosionTimer.isTimeUp())) {
			m_pBomb->explode();
			destroy();
		} else
			// a bomb could have entered the field while it is burning
			if (m_iState == BURNING) {
				m_pBomb->explode();
				destroy();
			}
	}
}

void Field::explodeField(int iSteps, glm::vec3 vDir, int x, int z)
{
	// Abort if out of bounds / max steps reached / reached field is a block / reached field has a crate
	if ((x < 0) || (x == m_pMap->getWidth()) || (z < 0) ||
	    (z == m_pMap->getHeight()) || (iSteps == 0) ||
	    (m_pMap->getType(x, z) == BLOCK))
		return;

	// has this newly reached field an Crate or Item?
	bool bStop = (m_pMap->hasCrate(x, z) || m_pMap->hasItem(x, z));

	m_pMap->destroyBlock(x, z);
	int nextX = (x + (int)vDir.x);
	int nextZ = (z + (int)vDir.z);

	// Only proceed with explosion if we didn't reach a crate or item
	if (!bStop)
		explodeField(--iSteps, vDir, nextX, nextZ);
	else
		return;
}

void Field::generateItem()
{
	switch (SDL_rand(9)) {
	case 0:
		if (Application::m_pConfig->getPower()) {
			m_pItem = new Item_PowerUp(m_iXGrid, m_iZGrid);
			m_bItem = true;
		}
		break;
	case 1:
		if (Application::m_pConfig->getBomb()) {
			m_pItem = new Item_BombUp(m_iXGrid, m_iZGrid);
			m_bItem = true;
		}
		break;
	case 2:
		if (Application::m_pConfig->getSpeed()) {
			m_pItem = new Item_SpeedUp(m_iXGrid, m_iZGrid);
			m_bItem = true;
		}
		break;
	case 3:
		switch (SDL_rand(2)) {
		case 0:
			if (Application::m_pConfig->getKick()) {
				m_pItem =
					new Item_EnableKick(m_iXGrid, m_iZGrid);
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
		switch (SDL_rand(7)) {
		case 0:
			if (Application::m_pConfig->getJoint()) {
				m_pItem = new Item_Joint(m_iXGrid, m_iZGrid);
				m_bItem = true;
			}
			break;
		case 1:
			if (Application::m_pConfig->getCondom()) {
				m_pItem = new Item_Condom(m_iXGrid, m_iZGrid);
				m_bItem = true;
			}
			break;
		case 2:
			if (Application::m_pConfig->getCocaine()) {
				m_pItem = new Item_Cocaine(m_iXGrid, m_iZGrid);
				m_bItem = true;
			}
			break;
		case 3:
			if (Application::m_pConfig->getViagra()) {
				m_pItem = new Item_Viagra(m_iXGrid, m_iZGrid);
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

void Field::destroy()
{
	m_iState = BURNING;
	m_EndOfExplosion.setAlarm(500);
	m_pMap->m_ParticleManager.addExplosionParticle(m_vPos);

	//if there exists an crate on this field, generate an item
	if (m_bCrate) {
		generateItem();
		m_bCrate = false;
		glm::vec3 vPos = m_vPos;
		vPos.y = 1;
		m_pMap->m_ParticleManager.addCrateParticle(vPos, 3);

	} else
		// else: is there an item on this field ?
		if (m_bItem) {
			delete m_pItem;
			m_pItem = NULL;

			m_bItem = false;
		}

	if (m_bBomb) {
		m_bBomb = false;
		explodeField(m_pBomb->getStrength(), glm::vec3(0, 0, 1),
			     m_iXGrid, m_iZGrid + 1);
		explodeField(m_pBomb->getStrength(), glm::vec3(0, 0, -1),
			     m_iXGrid, m_iZGrid - 1);
		explodeField(m_pBomb->getStrength(), glm::vec3(1, 0, 0),
			     m_iXGrid + 1, m_iZGrid);
		explodeField(m_pBomb->getStrength(), glm::vec3(-1, 0, 0),
			     m_iXGrid - 1, m_iZGrid);

		m_pBomb->explode();
		Map::m_iBombsOnField[m_pBomb->getOwnerID()]--;
		delete m_pBomb;
		m_pBomb = NULL;
	}

	m_pMap->doShake();
	m_bFree = true;
}

void Field::dispatchBomb()
{
	m_bBomb = false;
	m_pBomb = NULL;
	m_bFree = true;
}

void Field::placeItem(Item *item)
{
	// There is already an item on the field
	if (m_bItem) {
		delete m_pItem; // delete the old item
		m_pItem = item;
	} else {
		m_bItem = true;
		m_pItem = item;
	}
}

void Field::dispatchItem()
{
	m_pMap->m_ParticleManager.addItemParticle(m_vPos, 6,
						  m_pItem->getType());
	m_pItem = NULL;
	m_bItem = false;
}

int Field::getType()
{
	return m_iType;
}

Bomb *Field::getBomb()
{
	return m_pBomb;
}

// is there a bomb on the block
bool Field::hasBomb()
{
	return m_bBomb;
}

// is there a crate on the block
bool Field::hasCrate()
{
	return m_bCrate;
}

// is the field walkable?
bool Field::isFree()
{
	return m_bFree;
}

bool Field::isExploding()
{
	if (m_EndOfExplosion.isTimeUp())
		return false;
	else
		return true;
}

float Field::getMinX()
{
	return m_vMin.x;
}

float Field::getMinZ()
{
	return m_vMin.z;
}

float Field::getMaxX()
{
	return m_vMax.x;
}

float Field::getMaxZ()
{
	return m_vMax.z;
}

void Field::updateItem()
{
	if (m_bItem)
		m_pItem->update();
}

void Field::drawBombs()
{
	if (m_bBomb)
		m_pBomb->draw();
}

void Field::drawExplosion()
{
	if (m_iState == BURNING)
		m_pExplosion->draw();
}
