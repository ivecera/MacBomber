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

#include "ObjectThrower.h"
#include <glm/glm.hpp>
#include "../Engine/SimpleBezier.h"
#include "../Objects/Object_Moving.h"
#include "../Application.h"
#include <SDL3/SDL_opengl.h>

ObjectThrower::ObjectThrower(glm::vec3 vStart, glm::vec3 vEnd,
			     Object_Moving *pObject)
{
	glm::vec3 vMiddle;
	m_fVelocity = pObject->getVelocity();
	m_bDone = false;

	m_iWayPointCount = 10;
	m_iCurrentWayPoint = 0;
	m_pPath = new glm::vec3[m_iWayPointCount];

	m_vObjectPosition = vStart;
	m_pObject = pObject;

	glm::vec3 tmp = (vEnd - vStart);
	tmp = tmp / 2.0f;
	vMiddle = vStart + tmp;
	//:compiler error	vMiddle = vStart + ( (vEnd-vStart)/2) ;

	float fDistance = glm::length(vEnd - vStart);
	if (fDistance <= 3)
		vMiddle.y = 3;
	else if (fDistance <= 6)
		vMiddle.y = 8;
	else if (fDistance <= 12)
		vMiddle.y = 12;
	else
		vMiddle.y = 15;

	m_pBezier = new SimpleBezier(vStart, vMiddle, vEnd);
	calculateWayPoints(vStart, vEnd);
	calculateParameters();
}

ObjectThrower::~ObjectThrower()
{
	delete m_pBezier;
	delete[] m_pPath;
}

void ObjectThrower::calculateWayPoints(glm::vec3 vStart, glm::vec3 vEnd)
{
	float fStepping = 1 / (float)(m_iWayPointCount - 1);

	//...and calculate all points in between
	for (int i = 0; i < m_iWayPointCount; i++) {
		m_pPath[i] = m_pBezier->calculatePoint(fStepping * i);
	}
}

void ObjectThrower::calculateParameters()
{
	//since we call this function only when we reached an waypoint, we now set the next waypoint
	m_iCurrentWayPoint++;

	//Calculate a directional vector between the new and old waypoint
	m_vDisplacement =
		m_pPath[m_iCurrentWayPoint] - m_pPath[m_iCurrentWayPoint - 1];

	//calculate its Length
	m_fLength = glm::length(m_vDisplacement);
	m_fLengthTraveled = 0;

	//convert the directional vector to a displacment vector by normalizing
	m_vDisplacement = glm::normalize(m_vDisplacement);
	m_pObject->setDisplacement(m_vDisplacement);
}

void ObjectThrower::update()
{
	//object has reached it's destination
	if (m_iCurrentWayPoint == m_iWayPointCount) {
		m_bDone = true;

	} else {
		//current waypoint hasn't been reached
		if ((m_fLength - m_fLengthTraveled) >
		    (Application::m_fReciprocalFPS * m_fVelocity)) {
			m_pObject->move();
			m_fLengthTraveled +=
				(Application::m_fReciprocalFPS * m_fVelocity);
		} else {
			m_pObject->setPosition(m_pPath[m_iCurrentWayPoint]);
			calculateParameters();
		}
	}
}

void ObjectThrower::draw()
{
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < m_iWayPointCount; i++)
		glVertex3f(m_pPath[i].x, m_pPath[i].y, m_pPath[i].z);
	glEnd();
	glPopMatrix();
}
