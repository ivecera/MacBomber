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

#ifndef APPLICATIONMENU_H
#define APPLICATIONMENU_H

class Menu;
class MenuItem;
class ToggleItem;
class MenuSwitchItem;
class Timer;

class ApplicationMenu {
private:
	Menu *m_pMainMenu; //the menu, with which the player ist greeted
	Menu *m_pStartgameMenu; //the menu, which is used to start a game
	Menu *m_pOptionsMenu; //Optionsmenu
	Menu *m_pGoodieslimitMenu; //set the maxmimum amount of collectible Goodies
	Menu *m_pGoodiesMenu; //Enable/Disable Goodies
	Menu *m_pBadiesMenu; //Enable/Disable Badies
	Menu *m_pPlayerSetupMenu; //select playerskins and inputkeys. enable/disable player
	Menu *m_pSoundSetupMenu;
	Menu *m_pVideoSetupMenu;
	Menu *m_pLevelSelectionMenu;
	Menu *m_pCredits; //a menu consisting of textlabels and one back "switchitem"

	//Pointer to Menuitems. Used to retrieve the menuitem values
	MenuItem *m_pQuitGameMenuItem;

	MenuItem *m_pStartGameMenuItem;
	MenuItem *m_pRoundTimeMenuItem;
	MenuItem *m_pPointsToWinMenuItem;
	MenuItem *m_pRandomMapOrderMenuItem;
	MenuItem *m_pGameTypeMenuItem;

	MenuItem *m_pStartBombsMenuItem;
	MenuItem *m_pStartPowerMenuItem;
	MenuItem *m_pStartSpeedMenuItem;
	MenuItem *m_pStartKickMenuItem;
	MenuItem *m_pExtraBombsMenuItem;
	MenuItem *m_pExtraPowerMenuItem;
	MenuItem *m_pExtraSpeedMenuItem;

	MenuItem *m_pToggleBombUpMenuItem;
	MenuItem *m_pTogglePowerUpMenuItem;
	MenuItem *m_pToggleSpeedUpMenuItem;
	MenuItem *m_pToggleKickMenuItem;

	MenuItem *m_pToggleJointMenuItem;
	MenuItem *m_pToggleViagraMenuItem;
	MenuItem *m_pToggleCocaineMenuItem;
	MenuItem *m_pToggleCondomMenuItem;

	MenuItem *m_pToggleSoundFXItem;
	MenuItem *m_pToggleMusicItem;
	MenuItem *m_pSoundFXVolumeItem;
	MenuItem *m_pMusicVolumeItem;

	MenuItem *m_pToggleResolutionItem;
	MenuItem *m_pToggleFullscreenItem;

	//Pointer pointing to the Main application
	Application *m_pApp;

	//used to determine when Input repetition should be activated
	//( so that the user just to hold for e.g down to navigate down a menu)
	Timer *m_pActivateRepetitionTimer;

	void handleInput();

public:
	//creates Menuelement and initializes them according to Config
	ApplicationMenu(Application *pApp);
	~ApplicationMenu();

	// saves the values of the GUI Elements to the config object
	void storeSettings();

	void update();
	void draw();
};

#endif
