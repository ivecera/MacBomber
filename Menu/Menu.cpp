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

#include <SDL_opengl.h>
#include "../Application.h"
#include "../Defines.h"
#include "../Controller/Controller_Keyboard.h"
#include "../Engine/TextDrawer.h"
#include "../Engine/ortho.h"

#include "Menu.h"

Menu *Menu::pActiveMenu = NULL;

Menu::Menu(const char *Title, Menu *pMenu, const char *helpText)
{
	m_fYValue = 0.8;
	m_pParentMenu = pMenu;
	//m_itIterator = m_lMenuItems.begin();
	m_iActiveItem = 0;
	//m_cTitle = Title;
	strcpy(m_cTitle, Title);
	//	m_cHelperText = helpText;
	strcpy(m_cHelperText, helpText);
}

Menu::~Menu()
{
	// delete all Items in this menu
	vector<ptrMenuItem>::iterator it;
	for (it = m_lMenuItems.begin(); it != m_lMenuItems.end(); it++) {
		delete (*it);
	}
}

void Menu::gotoParentMenu()
{
	if (m_pParentMenu != NULL)
		Menu::pActiveMenu = m_pParentMenu;
}

void Menu::drawHelperText()
{
	Application::m_pTextDrawer->setSize(SMALL);
	if (m_cHelperText != NULL)
		Application::m_pTextDrawer->drawText(0.005, 0.005,
						     m_cHelperText);
}

void Menu::addMenuItem(MenuItem *pMenuItem)
{
	Vector3 vPosition;
	vPosition.x = 0.25;
	vPosition.y = m_fYValue -= 0.0625;
	pMenuItem->setPosition(vPosition);

	// add an MenuItem & set the active Menu item to the end of the list
	m_lMenuItems.push_back(pMenuItem);
	//	m_itIterator = m_lMenuItems.begin();
}

void Menu::addMenuItem(MenuItem *pMenuItem, Vector3 vPosition)
{
	pMenuItem->setPosition(vPosition);

	// add an MenuItem & set the active Menu item to the end of the list
	m_lMenuItems.push_back(pMenuItem);
	//m_itIterator = m_lMenuItems.begin();
}

void Menu::addSpace(float value)
{
	// ???!?!?!?
	//	m_fYValue = m_fYValue-= value;
	m_fYValue -= value;
}

void Menu::reset()
{
	m_iActiveItem = 0;
}

void Menu::setActiveMenu(Menu *pMenu)
{
	Menu::pActiveMenu = pMenu;
	Menu::pActiveMenu->reset();
}

void Menu::update()
{
	for (int i = 0; i < (int)m_lMenuItems.size(); i++) {
		m_lMenuItems[i]->setActive(false);
	}
	m_lMenuItems[m_iActiveItem]->setActive(true);
}

void Menu::draw()
{
	// Draw MenuTitle
	Application::m_pTextDrawer->setSize(BIG);
	Application::m_pTextDrawer->drawTextCentered(0.5, 0.90, m_cTitle);

	drawHelperText();

	Application::m_pTextDrawer->setSize(STD);

	//loop through all MenuItems and draw them
	vector<ptrMenuItem>::iterator it;
	for (it = m_lMenuItems.begin(); it != m_lMenuItems.end(); it++) {
		(*it)->draw();
	}
}

// FIX ME: check for non interactive elements
void Menu::up()
{
	//are we at the firstmenu entry? Then move to the bottom
	if (m_iActiveItem == 0) {
		m_iActiveItem = (int)m_lMenuItems.size() - 1;
		return;
	}

	// Skip over non interactive Menu elements
	for (int i = m_iActiveItem - 1; i >= 0; i--) {
		if (m_lMenuItems[i]->isInteractive()) {
			m_iActiveItem = i;
			break;
		}
	}
}

// FIX ME: check for non interactive elements
void Menu::down()
{
	//are we at the last menu entry? Then move to the top
	if (m_iActiveItem == (int)m_lMenuItems.size() - 1) {
		m_iActiveItem = 0;
		return;
	}

	// Skip over non interactive Menu elements
	for (int i = m_iActiveItem + 1; i < (int)m_lMenuItems.size(); i++) {
		if (m_lMenuItems[i]->isInteractive()) {
			m_iActiveItem = i;
			break;
		}
	}
}

void Menu::left()
{
	m_lMenuItems[m_iActiveItem]->left();
}

void Menu::right()
{
	m_lMenuItems[m_iActiveItem]->right();
}

void Menu::enter()
{
	m_lMenuItems[m_iActiveItem]->enter();
}

void Menu::space()
{
	m_lMenuItems[m_iActiveItem]->space();
}

void Menu::back()
{
	gotoParentMenu();
}
