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

#include "BombThrower.h"
#include "../Map/Map.h"

BombThrower::BombThrower(Map *pMap)
	: ObjectThrowerManager(pMap)
{
}

glm::vec3 BombThrower::getTarget(int ignoreFieldX, int ignoreFieldZ)
{
	int x, z;
	bool done = false;
	bool bConsiderVoid = false;
	(m_pMap->getFieldCount() < 10) ? bConsiderVoid = true :
					 bConsiderVoid = false;

	while (!done) {
		x = SDL_rand(m_pMap->getWidth());
		z = SDL_rand(m_pMap->getHeight());

		//Also take void fields in consideration if there are too few plain fields !
		if (bConsiderVoid) {
			if (((m_pMap->getType(x, z) == FIELD) ||
			     (m_pMap->getType(x, z) == HOLE) ||
			     (m_pMap->getType(x, z) == VOID)) &&
			    (x != ignoreFieldX) && (z != ignoreFieldZ))
				done = true;

		} else {
			if (((m_pMap->getType(x, z) == FIELD) ||
			     (m_pMap->getType(x, z) == HOLE)) &&
			    (x != ignoreFieldX) && (z != ignoreFieldZ))
				done = true;
		}
	}
	float _x = (float)x + 0.5f;
	float _z = (float)z + 0.5f;

	return glm::vec3(_x, 0.0f, _z);
}

void BombThrower::add(glm::vec3 vStart, Bomb *pBomb)
{
	glm::vec3 vTarget = getTarget((int)vStart.x, (int)vStart.z);
	// add Bomb...
	addToList(vStart, vTarget, pBomb);
	// ..and disable bomb wobbling
	pBomb->setWobble(false);
}

void BombThrower::handleDestinationReached(Object_Moving *pObject)
{
	Bomb *pBomb = (Bomb *)pObject;
	// There is a bomb on the reached tile. It must be detonated
	if (m_pMap->hasBomb(pBomb->getXBlock(), pBomb->getZBlock())) {
		m_pMap->destroyBlock(pBomb->getXBlock(), pBomb->getZBlock());

		Map::m_iBombsOnField[pBomb->getOwnerID()]--;
		delete pBomb;

	} else // Call the appropriate placeBomb method of the field (also for blocks)
	{
		pBomb->setDisplacement(glm::vec3(0, 0, 0));
		m_pMap->placeBomb(pBomb);

		//only call destroyBlock Method if reached Field is *not* a hole or an void field
		//(destroyBlock would cause an explosion to be drawn)
		if ((m_pMap->getType(pBomb->getXBlock(), pBomb->getZBlock()) !=
		     HOLE) &&
		    (m_pMap->getType(pBomb->getXBlock(), pBomb->getZBlock()) !=
		     VOID))
			m_pMap->destroyBlock(pBomb->getXBlock(),
					     pBomb->getZBlock());
	}
}
