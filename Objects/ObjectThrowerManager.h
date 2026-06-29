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

#ifndef OBJECTTHROWERMANAGER_H
#define OBJECTTHROWERMANAGER_H

#include <list>
#include "ObjectThrower.h"
#include "../Engine/Vector3.h"

class Map;
class Object_Moving;

class ObjectThrowerManager {
protected:
	struct SThrowerContainer {
		ObjectThrower *pThrower;
		Object_Moving *pObject; // pObject is sufficient for setPosition()
	};

	list<SThrowerContainer> m_listThrower;
	Map *m_pMap;

	virtual Vector3 getTarget(int ignoreFieldX, int ignoreFieldZ) = 0;
	virtual void handleDestinationReached(Object_Moving *pObject) = 0;
	void addToList(Vector3 vStart, Vector3 vEnd, Object_Moving *pObject);

public:
	ObjectThrowerManager(Map *pMap);
	virtual ~ObjectThrowerManager();
	void update();
	void draw();
};

#endif