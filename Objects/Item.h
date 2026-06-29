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

#ifndef ITEM_H
#define ITEM_H

#include "Object_Moving.h"
#include "../Defines.h"

class Player;

class Item : public Object_Moving {
protected:
	int m_iType; // type of Goodies  (defined in Defines.h)
	int m_iTexture; // which texture does this item use (defined in Defines.h)

	void showType();

public:
	//      type    -   the type of the goodie/badie
	Item(int xBlock, int zBlock);

	/* Applies the goodie/badie to the player.
	Returns true when the action has been performed (one-time application, e.g. for goodies)
	or when the effect duration (for badies) has expired.
	*/
	virtual bool affectPlayer(Player *player) = 0;
	int getType()
	{
		return m_iType;
	};

	void update();
	void draw();
};

#endif
