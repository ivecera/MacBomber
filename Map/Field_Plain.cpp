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

#include "Field_Plain.h"

//#include "Field.h"
#include "../Defines.h"
#include "Map.h"
#include "../Objects/Crate.h"
#include "../Objects/Item_PowerUp.h"
#include "../Objects/Item_BombUp.h"
#include "../Objects/Item_SpeedUp.h"
#include "../Objects/Item_Cocaine.h"
#include "../Objects/Item_Joint.h"
#include "../Explosion.h"
#include "../Engine/MeshManager.h"
#include "../Application.h"
#include "../MeshObjects/SquareMesh.h"

Field_Plain::Field_Plain(int xGridPos, int zGridPos, bool bCrate, Map *pMap)
	: Field(xGridPos, zGridPos, pMap)
{
	m_iType = FIELD;

	if (bCrate)
		placeCrate();

	//throw the dice to see if this field has a second texture
	if (rand() % 6 == 0) {
		m_bDecal = true;
		m_iDecalOrientation = rand() % 4;

		// now decide which second texture
		switch (rand() % 3) {
		case 0:
			m_iDecalTexture = FIELD_MUD0_TEXTURE;
			break;
		case 1:
			m_iDecalTexture = FIELD_MUD1_TEXTURE;
			break;
		case 2:
			//only assign if this square has a crate
			if (bCrate)
				m_iDecalTexture = FIELD_CRATEDEBRIS_TEXTURE;
			else
				m_bDecal = false;
			break;
		}
	} else
		m_bDecal = false;
}

Field_Plain::~Field_Plain()
{
}
void Field_Plain::placeCrate()
{
	if (m_bCrate == false) {
		m_bCrate = true;
		m_bFree = false;
		m_pCrate = new Crate(m_iXGrid, m_iZGrid);
	}
}

bool Field_Plain::placeBomb(Bomb *bomb)
{
	//There can only be one bomb per square
	if (m_bBomb == false) {
		m_bBomb = true;
		m_pBomb = bomb;

		// The field is not walkable if a bomb was placed
		m_bFree = false;
		return true;
	} else {
		delete bomb;
		return false;
	}
}

void Field_Plain::moveBomb()
{
	if (m_bBomb) {
		float fSize = m_pBomb->getSize() / 2;
		Vector3 vPos_next = m_pBomb->getPosition() +
				    (m_pBomb->getDisplacement() * fSize);

		// Is vPos_next still in the same field?
		if ((int(vPos_next.x) == m_iXGrid) &&
		    (int(vPos_next.z) == m_iZGrid)) {
			// The bomb can safely be moved, if it is supposed to move
			if (m_pBomb->doesMove()) {
				m_pBomb->move();
			}

		} else {
			//Is the newly reached field free and has no player?
			if (((m_pMap->isFree(
				     m_iXGrid +
					     (int)m_pBomb->getDisplacement().x,
				     m_iZGrid + (int)m_pBomb->getDisplacement()
							.z)) &&
			     (!m_pMap->hasPlayer(
				     m_iXGrid +
					     (int)m_pBomb->getDisplacement().x,
				     m_iZGrid + (int)m_pBomb->getDisplacement()
							.z))) // &&
			    //(!m_pMap->hasItem(m_iXGrid + m_pBomb->getDisplacement().x,m_iZGrid + m_pBomb->getDisplacement().z))
			    )
			//check for ITEM here?
			{
				// move the bomb
				m_pBomb->move();

				// Has the center of the bomb landed in a new field?
				// If so, hand the bomb over to that field
				if ((m_pBomb->getXBlock() != m_iXGrid) ||
				    (m_pBomb->getZBlock() != m_iZGrid)) {
					// The bomb is handed over to the next field
					m_pMap->placeBomb(m_pBomb);
					dispatchBomb();
				}

			} else {
				m_pBomb->stopMovement();
			}
		}
	}
}

void Field_Plain::kickBomb(int dir)
{
	if (m_bBomb) {
		m_pBomb->setDirection(dir);
	}
}

void Field_Plain::update()
{
	updateItem();
	checkBomb();

	switch (m_iState) {
	case (FALLING):

		m_vPos.y -= (Application::m_fReciprocalFPS * 4);
		m_fAngle += (Application::m_fReciprocalFPS * 90);
		if (m_bItem) {
			Vector3 vVector = m_pItem->getPosition();
			vVector.y -= (Application::m_fReciprocalFPS * 4);
			m_pItem->setPosition(vVector);
		}

		if (m_bBomb) {
			Vector3 vVector = m_pBomb->getPosition();
			vVector.y -= (Application::m_fReciprocalFPS * 4);
			m_pBomb->setPosition(vVector);
		}

		break;

	case BURNING:
		m_pExplosion->update();
		if (m_EndOfExplosion.isTimeUp()) {
			m_iState = NORMAL;
			m_pExplosion->reset();
		}
		break;
	case NORMAL:
		moveBomb();
		break;
	default:
		break;
	}
}

void Field_Plain::draw()
{
	glPushMatrix();
	glTranslatef(m_vPos.x, m_vPos.y, m_vPos.z);

	//only rotatie if there is a crate on this field
	if ((m_iState == FALLING) && (m_bCrate))
		glRotatef(m_fAngle, m_vRotationAxis.x, m_vRotationAxis.y,
			  m_vRotationAxis.z);

	if (m_bCrate)
		m_pCrate->draw();
	else {
		if (m_bDecal) {
			Application::m_pMeshManager->m_pSquareMesh
				->configureTexture1(m_iDecalTexture);
			Application::m_pMeshManager->m_pSquareMesh
				->configureTexCoord1(m_iDecalOrientation);
		}

		Application::m_pMeshManager->m_pSquareMesh->drawVBO();

		if (m_bDecal) {
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
		}
	}
	glPopMatrix();
}
