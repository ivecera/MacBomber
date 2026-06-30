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

#include "Field_Hole.h"
#include "Map.h"
#include "../Engine/MeshManager.h"
#include "../Engine/Timer.h"
#include "../Engine/ParticleSystem/ParticleManager.h"

#include "../MeshObjects/SquareMesh.h"
#include "../Explosion.h"
#include "../Application.h"
#include "../Defines.h"

Field_Hole::Field_Hole(int xGrid, int yGrid, Map *pMap)
	: Field(xGrid, yGrid, pMap)
{
	m_iType = HOLE;
	m_bFree = true;
}

Field_Hole::~Field_Hole()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end(); it++) {
		delete (*it).pBomb;
	}
	m_lBombList.clear();
}

bool Field_Hole::startFall(Bomb *pBomb)
{
	//Only flip if the direction is wrong
	//if (m_pBomb->getDirection() != m_iDirection)

	//Check if the bomb has crossed the field center line
	switch (pBomb->getDirection()) {
	case UP:
		if (pBomb->getPosition().z < m_vPos.z)
			return true;
		else
			return false;
		break;
	case DOWN:
		if (pBomb->getPosition().z > m_vPos.z)
			return true;
		else
			return false;
		break;
	case LEFT:
		if (pBomb->getPosition().x < m_vPos.x)
			return true;
		else
			return false;
		break;
	case RIGHT:
		if (pBomb->getPosition().x > m_vPos.x)
			return true;
		else
			return false;
		break;
	case NONE:
		return true;
		break;

	default:
		return false;
		break;
	}
}

bool Field_Hole::stopFall(Bomb *pBomb)
{
	if ((pBomb->getPosition().y) > -4)
		return false;
	else
		return true;
}

bool Field_Hole::hasBomb()
{
	return !(m_lBombList.empty());
}

bool Field_Hole::placeBomb(Bomb *bomb)
{
	SBombContainer newContainer;
	newContainer.pBomb = bomb;
	newContainer.bDoesFall = false; // A newly placed bomb does not fall
	newContainer.bDoesFly = false; // A newly placed bomb does not fly
	newContainer.bDraw = true;
	// Add the bomb to the list of falling bombs
	m_lBombList.push_back(newContainer);
	return true;
}

void Field_Hole::moveBomb()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end(); it++) {
		(*it).pBomb->update();
		(*it).pBomb->move();

		// If the bomb is not yet falling, check if it should start falling now
		if ((*it).bDoesFall == false) {
			if (startFall((*it).pBomb)) {
				(*it).bDoesFall = true;
				(*it).pBomb->setDisplacement(
					glm::vec3(0, -1, 0));
			}

		} else {
			if (stopFall((*it).pBomb)) {
				(*it).bDoesFall = false;
				(*it).bDoesFly = true;

				(*it).pBomb->setPosition(m_vPos);
				m_pMap->addBombToThrower(m_vPos, (*it).pBomb);
				m_lBombList.erase(it++);

				m_pMap->m_ParticleManager.addSmokeParticle(
					m_vPos, 15);

				/*					m_pSmoke->activate();
					m_tParticleDeactivationTimer.setAlarm(800);*/
			}

			//draw bombs till they are completley under the hole
			if (((*it).bDraw == true) &&
			    (((*it).pBomb)->getPosition().y < -1))
				(*it).bDraw = false;
		}
	}
}

void Field_Hole::update()
{
	switch (m_iState) {
	case FALLING:
		m_vPos.y -= (Application::m_fReciprocalFPS * 4);
		m_fAngle += (Application::m_fReciprocalFPS * 90);
		break;
	case BURNING:
		m_pExplosion->update();
		if (m_EndOfExplosion.isTimeUp()) {
			m_iState = NORMAL;
			m_pExplosion->reset();
		}
		break;
	default:
		break;
	};

	moveBomb();
}

void Field_Hole::draw()
{
	modelview.push();
	modelview.translate(m_vPos.x, m_vPos.y, m_vPos.z);
	modelview.apply();
	Application::m_pMeshManager->m_pSquareMesh->drawVBO();

	modelview.pop();

	//	pBombThrower->draw();
}

void Field_Hole::drawBombs()
{
	list<SBombContainer>::iterator it;
	for (it = m_lBombList.begin(); it != m_lBombList.end(); it++) {
		if ((*it).bDraw == true) {
			(*it).pBomb->draw();
		}
	}
}
