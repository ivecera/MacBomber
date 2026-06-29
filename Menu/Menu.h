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

#ifndef MENU_H
#define MENU_H

#include <vector>
#include "MenuItem.h"

typedef MenuItem *ptrMenuItem;

class Menu {
protected:
	// the parent menu of the current Menu
	Menu *m_pParentMenu;

	// this Vector contains all Menuitems of this Menu
	vector<ptrMenuItem> m_lMenuItems;
	// An iterator to the currently active Menuitem
	//vector <ptrMenuItem>::iterator m_itIterator;
	int m_iActiveItem;

	// This value is used to place the MenuItems properly
	float m_fYValue;

	// Menu Caption
	char m_cTitle[40];
	// a short helper text, which is displayed at the bottom of the screen
	char m_cHelperText[100];

	// the currently active Menu
	static Menu *pActiveMenu;

	void gotoParentMenu();

	//draws the helper Text at the bottom of the screen
	void drawHelperText();

public:
	Menu(char *Title, Menu *pParent = NULL,
	     char *helpText =
		     "use up&down keys to navigate / return to choose submenu");
	virtual ~Menu();

	// adds a Menuitem to the menu. The position of this Item willbe determined by the Menu itself
	void addMenuItem(MenuItem *pMenuItem);
	// adds a Menuitem to the menu, with position vPosition
	void addMenuItem(MenuItem *pMenuItem, Vector3 vPosition);
	// adds a vertical Spacing
	void addSpace(float value = 0.03);

	//resets the Menu (The first item is selected as activeItem)
	void reset();

	//used to set the currently active Menu. for e.g called by MenuSwitchItem
	static void setActiveMenu(Menu *pMenu);
	//used to set the currently active Menu. for e.g called by MenuSwitchItem
	static Menu *getActiveMenu()
	{
		return pActiveMenu;
	};

	// do stuff like Inputhandling etc.
	virtual void update();
	virtual void draw();

	// handle Controller Input
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();
	virtual void enter();
	virtual void back();
	virtual void space();

	// handles Controller Input
	virtual void handleInput() {};
};

#endif
