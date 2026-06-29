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

#ifndef LEVELSCROLLLISTITEM_H
#define LEVELSCROLLLISTITEM_H

#include "MenuItem.h"

class LevelScrollListItem : public MenuItem {
private:
	// the amount of total slots (Maps)
	int m_iSlotCount;
	// the amountg of slots which shall be shown without scrolling
	int m_iSlotsPerPage;

	int m_iOffset;
	// the number of the currenlty selected Slot  ( 0 - m_iSlotPerPage)
	int m_iCurrentSlot;

	// draws a Triangle
	void drawTriangle();
	void drawSlots();
	// draws the number of enabled maps
	void drawCount();

public:
	LevelScrollListItem();

	void up();
	void down();
	void space();

	void draw();
};

#endif