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

#include "MapDestroyer.h"
#include "../Defines.h"
#include "../Application.h"
#include <glm/glm.hpp>
#include "../Engine/MeshManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/SoundManager.h"
#include "../Engine/ParticleSystem/ParticleManager.h"
#include "../Map/Map.h"
#include "../Objects/ObjectThrower.h"
#include "../Objects/Wiley.h"

#include <SDL3/SDL_opengl.h>

MapDestroyer::MapDestroyer(Map *pMap)
{
	m_bMapCleared = false;
	m_pMap = pMap;
	m_iFieldsLeft = m_pMap->getFieldCount();

	m_pWiley = new Wiley();
	m_pDestroyerThrower =
		new ObjectThrower(glm::vec3(-10, 0, 0), getTarget(), m_pWiley);

	m_iTicks = 0;
}

MapDestroyer::~MapDestroyer()
{
	delete m_pDestroyerThrower;
	delete m_pWiley;
}

//randomly chooses a new target
glm::vec3 MapDestroyer::getTarget()
{
	// FIX ME: don't choose field randomly if count is below 5

	float x, z, y = 0;
	bool done = false;
	while (!done) {
		x = rand() % m_pMap->getWidth();
		z = rand() % m_pMap->getHeight();

		// Don't choose a void field
		if (m_pMap->getType((int)x, (int)z) != VOID)
			done = true;

		x += 0.5;
		z += 0.5;

		//if a block has been chosen or this field has a crate/item
		//-> set the y coordinate of the target a bit higher (otherwise it looks wrong)
		if ((m_pMap->getType((int)x, (int)z) == BLOCK) ||
		    (m_pMap->hasCrate((int)x, (int)z)) ||
		    (m_pMap->hasItem((int)x, (int)z)))
			y = 1;
	}

	return glm::vec3(x, y, z);
}

void MapDestroyer::update()
{
	if (m_bMapCleared) {
		if (!m_pDestroyerThrower->isDone())
			m_pDestroyerThrower->update();
	} else {
		m_pDestroyerThrower->update();

		if ((m_iTicks++) % 5 == 0)
			m_pMap->m_ParticleManager.addWileyParticle(
				m_pWiley->getPosition(), 3);

		//Did the the destroyer reach his target?
		if (m_pDestroyerThrower->isDone()) {
			//get destroyers position & a new target
			glm::vec3 vDestination;

			//one field less to go
			m_iFieldsLeft--;

			// has last field been destroyed ?
			if (m_iFieldsLeft <= 0) {
				m_bMapCleared = true;
				// let mapdestroyer hop out of the map
				vDestination = glm::vec3(-10, 0, 0);
			} else {
				vDestination = getTarget();
				//play a crunching sound
				Application::m_pSoundManager->playSoundFX(
					CRUNCH_SOUND);
			}

			//tell the map do drop field x,z
			m_pMap->doDrop(m_pWiley->getXBlock(),
				       m_pWiley->getZBlock());

			//create a new Thrower and choose a new target
			delete m_pDestroyerThrower;
			m_pDestroyerThrower =
				new ObjectThrower(m_pWiley->getPosition(),
						  vDestination, m_pWiley);
		}
	}
}

void MapDestroyer::draw()
{
	glPushMatrix();
	m_pWiley->draw();
	glPopMatrix();
}
