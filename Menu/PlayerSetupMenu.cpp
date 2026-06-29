
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

#include "PlayerSetupMenu.h"
#include "PlayerSetupRow.h"
#include "ControllerSetupItem.h"
#include "Menu.h"
#include "../Controller/Controller_Keyboard.h"
#include "../Engine/Timer.h"
#include "../Engine/TextDrawer.h"
#include "../Application.h"
#include "../Engine/TextDrawer.h"
#include "../Engine/ortho.h"
#include "../Config.h"
#include "../Defines.h"

PlayerSetupMenu::PlayerSetupMenu(Menu *pParent)
	: Menu("Player Setup", pParent)
{
	//	m_cHelperText = "up&down navigates/ space enables or disables player / return modifies option / ESC exits";
	strcpy(m_cHelperText,
	       "up&down navigates/ space enables or disables player / return modifies option / ESC exits");
	m_iCurrentRow = 0;
	m_pRows[0] =
		new PlayerSetupRow(Application::m_pConfig->getPlayerSkin(0),
				   Application::m_pConfig->getPlayerKeySet(0),
				   Application::m_pConfig->isPlayerEnabled(0));

	m_pRows[1] =
		new PlayerSetupRow(Application::m_pConfig->getPlayerSkin(1),
				   Application::m_pConfig->getPlayerKeySet(1),
				   Application::m_pConfig->isPlayerEnabled(1));

	m_pRows[2] =
		new PlayerSetupRow(Application::m_pConfig->getPlayerSkin(2),
				   Application::m_pConfig->getPlayerKeySet(2),
				   Application::m_pConfig->isPlayerEnabled(2));

	m_pRows[3] =
		new PlayerSetupRow(Application::m_pConfig->getPlayerSkin(3),
				   Application::m_pConfig->getPlayerKeySet(3),
				   Application::m_pConfig->isPlayerEnabled(3));

	/*	m_pRows[1] = new PlayerSetupRow();
	m_pRows[2] = new PlayerSetupRow();
	m_pRows[3] = new PlayerSetupRow();*/

	addMenuItem(m_pRows[0], Vector3(0.312, 0.66, 0));
	addMenuItem(m_pRows[1], Vector3(0.312, 0.48, 0));
	addMenuItem(m_pRows[2], Vector3(0.312, 0.30, 0));
	addMenuItem(m_pRows[3], Vector3(0.312, 0.12, 0));
}

PlayerSetupMenu::~PlayerSetupMenu()
{
	/*	delete m_pRows[0];
	delete m_pRows[1];
	delete m_pRows[2];
	delete m_pRows[3];*/
}

void PlayerSetupMenu::determineEnabledPlayerCount()
{
	m_iEnabledPlayerCount = 0;

	//determine the amount of enabled players
	for (int i = 0; i < 4; i++) {
		if (m_pRows[i]->isEnabled())
			m_iEnabledPlayerCount++;
	}
}

void PlayerSetupMenu::storeSettings()
{
	int iPlayerCount = 0;

	//save all settings to the config Object
	for (int i = 0; i < 4; i++) {
		Application::m_pConfig->setPlayerKeySet(
			i, m_pRows[i]->getKeySet());
		Application::m_pConfig->setPlayerSkin(i, m_pRows[i]->getSkin());
		Application::m_pConfig->setPlayerEnabled(
			i, m_pRows[i]->isEnabled());

		//determine active Player Count
		if (m_pRows[i]->isEnabled())
			iPlayerCount++;
	}

	Application::m_pConfig->setPlayerCount(iPlayerCount);
}

void PlayerSetupMenu::update()
{
	//	(*m_itIterator)->setActive();
	for (int i = 0; i < (int)m_lMenuItems.size(); i++) {
		m_lMenuItems[i]->setActive(false);
	}
	m_lMenuItems[m_iActiveItem]->setActive(true);
	determineEnabledPlayerCount();
}

void PlayerSetupMenu::draw()
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

	if (m_iEnabledPlayerCount <= 1) {
		Application::m_pTextDrawer->setSize(STD);
		Application::m_pTextDrawer->drawTextCentered(
			0.5, 0.84, "Please enable at least two players!");
	}
}

void PlayerSetupMenu::up()
{
	if (m_iActiveItem > 0) {
		//		((PlayerSetupRow*)m_lMenuItems[m_iActiveItem])->setColumn(0);
		m_iActiveItem--;

	} else
		m_iActiveItem = (int)m_lMenuItems.size() - 1;
}

void PlayerSetupMenu::down()
{
	if (m_iActiveItem < (int)m_lMenuItems.size() - 1) {
		//		((PlayerSetupRow*)m_lMenuItems[m_iActiveItem])->setColumn(0);
		m_iActiveItem++;

	} else
		m_iActiveItem = 0;
}
void PlayerSetupMenu::back()
{
	// only exit menu if at least two players are enabled
	if (m_iEnabledPlayerCount > 1)
		gotoParentMenu();
}

void PlayerSetupMenu::space()
{
	PlayerSetupRow *pSetupRow =
		(PlayerSetupRow *)m_lMenuItems[m_iActiveItem];
	pSetupRow->toggleEnable();
}
