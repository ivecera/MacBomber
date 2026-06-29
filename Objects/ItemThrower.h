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

#ifndef ITEMTHROWER_H
#define ITEMTHROWER_H

#include "ObjectThrowerManager.h"

class Item;

class ItemThrower : public ObjectThrowerManager {
private:
	// choose a random target
	Vector3 getTarget(int ignoreFieldX, int ignoreFieldZ);

public:
	ItemThrower(Map *pMap);

	void add(Vector3 vStart, Item *pBomb);
	void handleDestinationReached(Object_Moving *pObject);
};

#endif
