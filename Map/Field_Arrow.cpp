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
#include "../Engine/MatrixStack.h"
#include <SDL3/SDL_opengl.h>

#include "Field_Arrow.h"
#include "Map.h"
#include "../Objects/Item.h"
#include "../Engine/MeshManager.h"
#include "../Engine/TextureManager.h"
#include "../Explosion.h"
#include "../MeshObjects/SquareMesh.h"
#include "../Application.h"

Field_Arrow::Field_Arrow(int xGrid, int yGrid, int direction, Map *pMap)
	: Field(xGrid, yGrid, pMap)
{
	m_bFree = true;
	m_iDirection = direction;

	m_iNextBlockX = m_iXGrid;
	m_iNextBlockZ = m_iZGrid;

	switch (m_iDirection) {
	case UP:
		m_iType = ARROW_UP;
		m_iNextBlockZ = m_iZGrid - 1;
		break;
	case DOWN:
		m_iType = ARROW_DOWN;
		m_iNextBlockZ = m_iZGrid + 1;
		break;
	case LEFT:
		m_iType = ARROW_LEFT;
		m_iNextBlockX = m_iXGrid - 1;
		break;
	case RIGHT:
		m_iType = ARROW_RIGHT;
		m_iNextBlockX = m_iXGrid + 1;
		break;
	}
	m_pMap = pMap;
}

bool Field_Arrow::doFlip()
{
	//Only flip if the direction is wrong
	if (m_pBomb->getDirection() != m_iDirection) {
		//Check if the bomb has crossed a certain line
		switch (m_pBomb->getDirection()) {
		case UP:
			if (m_pBomb->getPosition().z < m_vPos.z)
				return true;
			else
				return false;
			break;
		case DOWN:
			if (m_pBomb->getPosition().z > m_vPos.z)
				return true;
			else
				return false;
			break;
		case LEFT:
			if (m_pBomb->getPosition().x < m_vPos.x)
				return true;
			else
				return false;
			break;
		case RIGHT:
			if (m_pBomb->getPosition().x > m_vPos.x)
				return true;
			else
				return false;
			break;
		default: // NONE
			return false;
			break;
		}
	} else // Direction is correct
		return false;
}

bool Field_Arrow::placeBomb(Bomb *bomb)
{
	// Only one bomb can be placed on a field
	if (m_bBomb == false) {
		m_bBomb = true;
		m_pBomb = bomb;

		// The field is not walkable if a bomb was placed
		m_bFree = false;
		return true;
	} else
		return false;
}

void Field_Arrow::moveBomb()
{
	if (m_bBomb) {
		float fSize = m_pBomb->getSize() / 2;
		glm::vec3 vPos_next = m_pBomb->getPosition() +
				      (m_pBomb->getDisplacement() * fSize);

		// If the bomb is not moving (just placed), push it
		if ((m_pBomb->getDirection() == NONE) &&
		    (m_pMap->isFree(m_iNextBlockX, m_iNextBlockZ)))
			m_pBomb->setDirection(m_iDirection);

		// Flip if the direction is wrong
		if (doFlip())
			m_pBomb->setDirection(m_iDirection);

		// Is vPos_next still in the same field?
		if ((int(vPos_next.x) == m_iXGrid) &&
		    (int(vPos_next.z) == m_iZGrid)) {
			// The bomb can safely be moved, if it is supposed to move
			if (m_pBomb->doesMove())
				m_pBomb->move();

		} else // new field reached
		{
			int nextBlockX =
				(int)(m_iXGrid + m_pBomb->getDisplacement().x);
			int nextBlockZ =
				(int)(m_iZGrid + m_pBomb->getDisplacement().z);

			//Is the newly reached field free?
			if ((m_pMap->isFree(nextBlockX, nextBlockZ)) &&
			    (!m_pMap->hasPlayer(nextBlockX, nextBlockZ))) {
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

void Field_Arrow::update()
{
	checkBomb();
	switch (m_iState) {
	case FALLING:
		m_vPos.y -= (Application::m_fReciprocalFPS * 4);
		m_fAngle += (Application::m_fReciprocalFPS * 90);

		if (m_bItem) {
			glm::vec3 vVector = m_pItem->getPosition();
			vVector.y -= (Application::m_fReciprocalFPS * 4);
			m_pItem->setPosition(vVector);
		}

		if (m_bBomb) {
			glm::vec3 vVector = m_pBomb->getPosition();
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
	};
}

void Field_Arrow::draw()
{
	glEnable(GL_BLEND);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	modelview.push();
	modelview.translate(m_vPos.x, m_vPos.y, m_vPos.z);
	modelview.apply();
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord1(
		m_iDirection);
	Application::m_pMeshManager->m_pSquareMesh->drawVBO();
	modelview.pop();

	glDisable(GL_BLEND);
}
