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

#ifndef LEVELSELECTIONMENU_H
#define LEVELSELECTIONMENU_H

#include "Menu.h"
class LevelScrollListItem;
class MapPreview;
class ToggleItem;

class LevelSelectionMenu : public Menu {
private:
	LevelScrollListItem *m_pLevelScrollList;
	MapPreview *m_pMapPreview;
	ToggleItem *m_pEnableAllMenuItem;
	ToggleItem *m_pDisableAllMenuItem;

public:
	LevelSelectionMenu(Menu *pParent);
	~LevelSelectionMenu();

	void update();

	void up();
	void down();
	void left();
	void right();

	void back();
	void draw();
};

#endif