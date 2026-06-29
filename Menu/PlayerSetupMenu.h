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
#ifndef PLAYERSETUPMENU_H
#define PLAYERSETUPMENU_H

#include "Menu.h"

class PlayerSetupRow;

class PlayerSetupMenu : public Menu {
private:
	int m_iCurrentRow;
	PlayerSetupRow *m_pRows[4];

	int m_iEnabledPlayerCount;
	// determines the amount of enabled players
	void determineEnabledPlayerCount();

public:
	PlayerSetupMenu(Menu *pParent);
	~PlayerSetupMenu();

	void storeSettings();
	void update();
	void draw();

	void up();
	void down();
	/*void left();
	void right();
	void enter();*/
	void back();
	void space();
};
#endif
