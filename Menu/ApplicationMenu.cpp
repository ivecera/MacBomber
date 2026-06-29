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

#include <SDL3/SDL_opengl.h>

#include "../Defines.h"
#include "../Application.h"
#include "ApplicationMenu.h"
#include "../Engine/Vector3.h"
#include "Menu.h"
#include "PlayerSetupMenu.h"
#include "LevelSelectionMenu.h"
#include "MenuItem.h"
#include "LabelItem.h"
#include "MenuSwitchItem.h"
#include "ToggleItem.h"
#include "ValueItem.h"
#include "../Config.h"
#include "../Engine/TextDrawer.h"
#include "../Engine/ortho.h"
#include "../Engine/Timer.h"
#include "../Engine/Init.h"
#include "../Engine/TextureManager.h"
#include "../Engine/SoundManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/ScreenFader.h"

#include "../Controller/Controller_Keyboard.h"

ApplicationMenu::ApplicationMenu(Application *pApp)
{
	m_pApp = pApp;
	m_pActivateRepetitionTimer = new Timer();
	//------------------------------  generate all Menus
	m_pMainMenu = new Menu("Main Menu", NULL);
	m_pStartgameMenu = new Menu(
		"New Game", m_pMainMenu,
		"use up&down keys to navigate / left&right keys to modiy options");
	m_pOptionsMenu = new Menu("Options", m_pMainMenu);
	m_pGoodieslimitMenu = new Menu(
		"Start/Max Goodies", m_pOptionsMenu,
		"use up&down keys to navigate / left&right keys to modiy options");
	m_pGoodiesMenu = new Menu(
		"Enable/Disable Goodies", m_pOptionsMenu,
		"use up&down keys to navigate / left&right keys to modiy options");
	m_pBadiesMenu = new Menu(
		"Enable/Disable Badies", m_pOptionsMenu,
		"use up&down keys to navigate / left&right keys to modiy options");
	m_pPlayerSetupMenu = new PlayerSetupMenu(m_pMainMenu);
	m_pLevelSelectionMenu = new LevelSelectionMenu(m_pMainMenu);
	m_pSoundSetupMenu = new Menu(
		"Audio Setup", m_pMainMenu,
		"use up&down keys to navigate / left&right keys to modiy options");
	m_pVideoSetupMenu = new Menu(
		"Video Setup", m_pMainMenu,
		"use up&down keys to navigate / left&right keys to modiy options");
	m_pCredits = new Menu("Credits", m_pMainMenu, "Press ESC to exit");

	//------------------------------ add Menuitems to the menus

	/**MainMenu */
	m_pMainMenu->addMenuItem(
		new MenuSwitchItem("New Game", m_pStartgameMenu));
	m_pMainMenu->addMenuItem(new MenuSwitchItem("Options", m_pOptionsMenu));
	m_pMainMenu->addMenuItem(
		new MenuSwitchItem("Map Selection", m_pLevelSelectionMenu));
	m_pMainMenu->addMenuItem(
		new MenuSwitchItem("Player Setup", m_pPlayerSetupMenu));
	m_pMainMenu->addMenuItem(
		new MenuSwitchItem("Audio Setup", m_pSoundSetupMenu));
	m_pMainMenu->addMenuItem(
		new MenuSwitchItem("Video Setup", m_pVideoSetupMenu));
	m_pMainMenu->addMenuItem(new MenuSwitchItem("Credits", m_pCredits));
	m_pMainMenu->addSpace();

	m_pQuitGameMenuItem = new ToggleItem("Quit");
	((ToggleItem *)m_pQuitGameMenuItem)->addOption(" ", 0);
	((ToggleItem *)m_pQuitGameMenuItem)->addOption(" ", 1);
	m_pMainMenu->addMenuItem(m_pQuitGameMenuItem);

	//**startGame Menu*/

	// HACK: 1 == Start Game - value will not be displayed !
	m_pStartGameMenuItem = new ToggleItem("Start Game");
	((ToggleItem *)m_pStartGameMenuItem)->addOption(" ", 0);
	((ToggleItem *)m_pStartGameMenuItem)->addOption(" ", 1);
	m_pStartgameMenu->addMenuItem(m_pStartGameMenuItem);

	m_pStartgameMenu->addSpace();

	m_pGameTypeMenuItem = new ToggleItem("Game type:");
	((ToggleItem *)m_pGameTypeMenuItem)->addOption("Standard", 0);
	((ToggleItem *)m_pGameTypeMenuItem)->addOption("Wiley attacks!", 1);
	m_pGameTypeMenuItem->setValue(m_pApp->m_pConfig->getGameType());
	m_pStartgameMenu->addMenuItem(m_pGameTypeMenuItem);

	m_pRoundTimeMenuItem = new ValueItem("Roundtime (sec.):", 30, 300, 30);
	m_pRoundTimeMenuItem->setValue(m_pApp->m_pConfig->getRoundTime());
	m_pStartgameMenu->addMenuItem(m_pRoundTimeMenuItem);

	m_pPointsToWinMenuItem = new ValueItem("Points to win game:", 1, 5, 1);
	m_pPointsToWinMenuItem->setValue(
		m_pApp->m_pConfig->getPointsForVictory());
	m_pStartgameMenu->addMenuItem(m_pPointsToWinMenuItem);

	m_pRandomMapOrderMenuItem = new ToggleItem("Random Map Order:");
	((ToggleItem *)m_pRandomMapOrderMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pRandomMapOrderMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getRandomMapOrder() ?
		m_pRandomMapOrderMenuItem->setValue(1) :
		m_pRandomMapOrderMenuItem->setValue(0);
	m_pStartgameMenu->addMenuItem(m_pRandomMapOrderMenuItem);

	m_pStartgameMenu->addSpace();
	m_pStartgameMenu->addMenuItem(
		new MenuSwitchItem("<Back>", m_pMainMenu));

	/**Options Menu*/

	m_pOptionsMenu->addMenuItem(
		new MenuSwitchItem("Start/Max Goodies", m_pGoodieslimitMenu));
	m_pOptionsMenu->addMenuItem(
		new MenuSwitchItem("Enable/Disable Goodies", m_pGoodiesMenu));
	m_pOptionsMenu->addMenuItem(
		new MenuSwitchItem("Enable/Disable Badies", m_pBadiesMenu));
	m_pOptionsMenu->addSpace();
	m_pOptionsMenu->addMenuItem(new MenuSwitchItem("<Back>", m_pMainMenu));

	/**GoodieslimitMenu*/
	m_pStartBombsMenuItem = new ValueItem("Inital Bombs:", 1, 10, 1);
	m_pStartBombsMenuItem->setValue(m_pApp->m_pConfig->getStartBombs());
	m_pGoodieslimitMenu->addMenuItem(m_pStartBombsMenuItem);

	m_pStartPowerMenuItem = new ValueItem("Inital Power:", 1, 10, 1);
	m_pStartPowerMenuItem->setValue(m_pApp->m_pConfig->getStartPower());
	m_pGoodieslimitMenu->addMenuItem(m_pStartPowerMenuItem);

	m_pStartSpeedMenuItem = new ValueItem("Inital Speed:", 1, 5, 1);
	m_pStartSpeedMenuItem->setValue(m_pApp->m_pConfig->getStartSpeed());
	m_pGoodieslimitMenu->addMenuItem(m_pStartSpeedMenuItem);

	m_pStartKickMenuItem = new ToggleItem("Start with Kick:");
	((ToggleItem *)m_pStartKickMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pStartKickMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getStartKick() ? m_pStartKickMenuItem->setValue(1) :
					    m_pStartKickMenuItem->setValue(0);
	m_pGoodieslimitMenu->addMenuItem(m_pStartKickMenuItem);

	m_pExtraBombsMenuItem = new ValueItem("Max. extra Bombs:", 0, 10, 1);
	m_pExtraBombsMenuItem->setValue(m_pApp->m_pConfig->getExtraBombs());
	m_pGoodieslimitMenu->addMenuItem(m_pExtraBombsMenuItem);

	m_pExtraPowerMenuItem = new ValueItem("Max. extra Power:", 0, 10, 1);
	m_pExtraPowerMenuItem->setValue(m_pApp->m_pConfig->getExtraPower());
	m_pGoodieslimitMenu->addMenuItem(m_pExtraPowerMenuItem);

	m_pExtraSpeedMenuItem = new ValueItem("Max. extra Speed:", 0, 10, 1);
	m_pExtraSpeedMenuItem->setValue(m_pApp->m_pConfig->getExtraSpeed());
	m_pGoodieslimitMenu->addMenuItem(m_pExtraSpeedMenuItem);

	m_pGoodieslimitMenu->addSpace();
	m_pGoodieslimitMenu->addMenuItem(
		new MenuSwitchItem("<Back>", m_pOptionsMenu));

	/**m_pGoodiesMenu*/
	m_pToggleBombUpMenuItem = new ToggleItem("Enable BombUp Item:");
	((ToggleItem *)m_pToggleBombUpMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleBombUpMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getBomb() ? m_pToggleBombUpMenuItem->setValue(1) :
				       m_pToggleBombUpMenuItem->setValue(0);
	m_pGoodiesMenu->addMenuItem(m_pToggleBombUpMenuItem);

	m_pTogglePowerUpMenuItem = new ToggleItem("Enable PowerUp Item:");
	((ToggleItem *)m_pTogglePowerUpMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pTogglePowerUpMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getPower() ? m_pTogglePowerUpMenuItem->setValue(1) :
					m_pTogglePowerUpMenuItem->setValue(0);
	m_pGoodiesMenu->addMenuItem(m_pTogglePowerUpMenuItem);

	m_pToggleSpeedUpMenuItem = new ToggleItem("Enable SpeedUp Item:");
	((ToggleItem *)m_pToggleSpeedUpMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleSpeedUpMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getSpeed() ? m_pToggleSpeedUpMenuItem->setValue(1) :
					m_pToggleSpeedUpMenuItem->setValue(0);
	m_pGoodiesMenu->addMenuItem(m_pToggleSpeedUpMenuItem);

	m_pToggleKickMenuItem = new ToggleItem("Enable Kick Item:");
	((ToggleItem *)m_pToggleKickMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleKickMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getKick() ? m_pToggleKickMenuItem->setValue(1) :
				       m_pToggleKickMenuItem->setValue(0);
	m_pGoodiesMenu->addMenuItem(m_pToggleKickMenuItem);

	m_pGoodiesMenu->addSpace();
	m_pGoodiesMenu->addMenuItem(
		new MenuSwitchItem("<Back>", m_pOptionsMenu));

	/**m_pBadiesMenu*/
	m_pToggleJointMenuItem = new ToggleItem("Enable Joint Item:");
	((ToggleItem *)m_pToggleJointMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleJointMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getJoint() ? m_pToggleJointMenuItem->setValue(1) :
					m_pToggleJointMenuItem->setValue(0);
	m_pBadiesMenu->addMenuItem(m_pToggleJointMenuItem);

	m_pToggleViagraMenuItem = new ToggleItem("Enable Viagra Item:");
	((ToggleItem *)m_pToggleViagraMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleViagraMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getViagra() ? m_pToggleViagraMenuItem->setValue(1) :
					 m_pToggleViagraMenuItem->setValue(0);
	m_pBadiesMenu->addMenuItem(m_pToggleViagraMenuItem);

	m_pToggleCocaineMenuItem = new ToggleItem("Enable Cocaine Item:");
	((ToggleItem *)m_pToggleCocaineMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleCocaineMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getCocaine() ?
		m_pToggleCocaineMenuItem->setValue(1) :
		m_pToggleCocaineMenuItem->setValue(0);
	m_pBadiesMenu->addMenuItem(m_pToggleCocaineMenuItem);

	m_pToggleCondomMenuItem = new ToggleItem("Enable Condom Item:");
	((ToggleItem *)m_pToggleCondomMenuItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleCondomMenuItem)->addOption("No", 0);
	m_pApp->m_pConfig->getCondom() ? m_pToggleCondomMenuItem->setValue(1) :
					 m_pToggleCondomMenuItem->setValue(0);
	m_pBadiesMenu->addMenuItem(m_pToggleCondomMenuItem);

	m_pBadiesMenu->addSpace();
	m_pBadiesMenu->addMenuItem(
		new MenuSwitchItem("<Back>", m_pOptionsMenu));

	/**m_pSoundSetupMenu*/
	m_pToggleSoundFXItem = new ToggleItem("Play SoundFX:");
	((ToggleItem *)m_pToggleSoundFXItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleSoundFXItem)->addOption("No", 0);
	m_pApp->m_pConfig->getSoundFX() ? m_pToggleSoundFXItem->setValue(1) :
					  m_pToggleSoundFXItem->setValue(0);
	m_pSoundSetupMenu->addMenuItem(m_pToggleSoundFXItem);

	m_pToggleMusicItem = new ToggleItem("Play Music");
	((ToggleItem *)m_pToggleMusicItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleMusicItem)->addOption("No", 0);
	m_pApp->m_pConfig->getMusic() ? m_pToggleMusicItem->setValue(1) :
					m_pToggleMusicItem->setValue(0);
	m_pSoundSetupMenu->addMenuItem(m_pToggleMusicItem);

	m_pSoundFXVolumeItem = new ValueItem("SoundFX Volume:", 1, 5, 1);
	m_pSoundFXVolumeItem->setValue(m_pApp->m_pConfig->getSoundFXVolume());
	m_pSoundSetupMenu->addMenuItem(m_pSoundFXVolumeItem);
	m_pMusicVolumeItem = new ValueItem("Music Volume:", 1, 5, 1);
	m_pMusicVolumeItem->setValue(m_pApp->m_pConfig->getMusicVolume());
	m_pSoundSetupMenu->addMenuItem(m_pMusicVolumeItem);

	m_pSoundSetupMenu->addSpace();
	m_pSoundSetupMenu->addMenuItem(
		new MenuSwitchItem("<Back>", m_pMainMenu));

	/**m_pVideoSetupMenu*/
	m_pToggleResolutionItem = new ToggleItem("Resolution:");

	//only add supported Resolutions to our list
	if (Application::m_pConfig->getResolutionSupport(0))
		((ToggleItem *)m_pToggleResolutionItem)->addOption("800x600", 0);
	if (Application::m_pConfig->getResolutionSupport(1))
		((ToggleItem *)m_pToggleResolutionItem)
			->addOption("1024x768", 1);
	if (Application::m_pConfig->getResolutionSupport(2))
		((ToggleItem *)m_pToggleResolutionItem)
			->addOption("1280x800", 2);

	m_pToggleResolutionItem->setValue(m_pApp->m_pConfig->getResolution());
	m_pVideoSetupMenu->addMenuItem(m_pToggleResolutionItem);

	m_pToggleFullscreenItem = new ToggleItem("Fullscreen:");
	((ToggleItem *)m_pToggleFullscreenItem)->addOption("Yes", 1);
	((ToggleItem *)m_pToggleFullscreenItem)->addOption("No", 0);
	m_pApp->m_pConfig->getFullscreen() ?
		m_pToggleFullscreenItem->setValue(1) :
		m_pToggleFullscreenItem->setValue(0);
	m_pVideoSetupMenu->addMenuItem(m_pToggleFullscreenItem);

	float length = Application::m_pTextDrawer->getLength(
		"(Changes will apply after restart)");
	m_pVideoSetupMenu->addMenuItem(
		new LabelItem("(Changes will apply after restart)"),
		Vector3(0.5 - (length / 2), 0.85, 0));

	m_pVideoSetupMenu->addSpace();
	m_pVideoSetupMenu->addMenuItem(
		new MenuSwitchItem("<Back>", m_pMainMenu));

	/**m_pCredits*/
	m_pCredits->addMenuItem(new LabelItem("Programming:"),
				Vector3(0.3, 0.73, 0));
	m_pCredits->addMenuItem(new LabelItem("Altay Cebe"),
				Vector3(0.5, 0.73, 0));

	m_pCredits->addMenuItem(new LabelItem("Graphics:"),
				Vector3(0.3, 0.66, 0));
	m_pCredits->addMenuItem(new LabelItem("Altay Cebe"),
				Vector3(0.5, 0.66, 0));

	m_pCredits->addMenuItem(new LabelItem("Music:"), Vector3(0.3, 0.59, 0));
	m_pCredits->addMenuItem(new LabelItem("Dennis Becker"),
				Vector3(0.5, 0.59, 0));
	m_pCredits->addMenuItem(new LabelItem("(www.ohrmusik.de)"),
				Vector3(0.5, 0.55, 0));

	m_pCredits->addMenuItem(new LabelItem("Special thanks to:"),
				Vector3(0.3, 0.4, 0));
	m_pCredits->addMenuItem(new LabelItem("Lale Cebe"),
				Vector3(0.5, 0.36, 0));
	m_pCredits->addMenuItem(new LabelItem("Jens Neuhalfen"),
				Vector3(0.5, 0.29, 0));

	Menu::setActiveMenu(m_pMainMenu);
}

ApplicationMenu::~ApplicationMenu()
{
	delete m_pMainMenu;

	delete m_pOptionsMenu;
	delete m_pGoodieslimitMenu;
	delete m_pGoodiesMenu;
	delete m_pBadiesMenu;

	delete m_pStartgameMenu;
	delete m_pPlayerSetupMenu;
	delete m_pSoundSetupMenu;
	delete m_pVideoSetupMenu;
	delete m_pLevelSelectionMenu;
	delete m_pCredits;

	delete m_pActivateRepetitionTimer;
}

void ApplicationMenu::storeSettings()
{
	m_pApp->m_pConfig->setGameType(m_pGameTypeMenuItem->getValue());
	m_pApp->m_pConfig->setRoundTime(m_pRoundTimeMenuItem->getValue());
	m_pApp->m_pConfig->setPointsForVictory(
		m_pPointsToWinMenuItem->getValue());
	m_pApp->m_pConfig->setRandomMapOrder(
		m_pRandomMapOrderMenuItem->getValue());

	m_pApp->m_pConfig->setStartBombs(m_pStartBombsMenuItem->getValue());
	m_pApp->m_pConfig->setStartPower(m_pStartPowerMenuItem->getValue());
	m_pApp->m_pConfig->setStartSpeed(m_pStartSpeedMenuItem->getValue());
	m_pApp->m_pConfig->setStartKick(m_pStartKickMenuItem->getValue());

	m_pApp->m_pConfig->setExtraBombs(m_pExtraBombsMenuItem->getValue());
	m_pApp->m_pConfig->setExtraPower(m_pExtraPowerMenuItem->getValue());
	m_pApp->m_pConfig->setExtraSpeed(m_pExtraSpeedMenuItem->getValue());

	m_pApp->m_pConfig->setBomb(m_pToggleBombUpMenuItem->getValue());
	m_pApp->m_pConfig->setPower(m_pTogglePowerUpMenuItem->getValue());
	m_pApp->m_pConfig->setSpeed(m_pToggleSpeedUpMenuItem->getValue());
	m_pApp->m_pConfig->setKick(m_pToggleKickMenuItem->getValue());
	m_pApp->m_pConfig->setJoint(m_pToggleJointMenuItem->getValue());
	m_pApp->m_pConfig->setViagra(m_pToggleViagraMenuItem->getValue());
	m_pApp->m_pConfig->setCocaine(m_pToggleCocaineMenuItem->getValue());
	m_pApp->m_pConfig->setCondom(m_pToggleCondomMenuItem->getValue());

	m_pApp->m_pConfig->setSoundFX(m_pToggleSoundFXItem->getValue());
	m_pApp->m_pConfig->setMusic(m_pToggleMusicItem->getValue());
	m_pApp->m_pConfig->setSoundFXVolume(m_pSoundFXVolumeItem->getValue());
	m_pApp->m_pConfig->setMusicVolume(m_pMusicVolumeItem->getValue());

	m_pApp->m_pConfig->setResolution(m_pToggleResolutionItem->getValue());
	m_pApp->m_pConfig->setFullscreen(m_pToggleFullscreenItem->getValue());

	//Player Setup Menu has it's own store function....
	((PlayerSetupMenu *)m_pPlayerSetupMenu)->storeSettings();
}

void ApplicationMenu::handleInput()
{
	Controller *m_pController =
		Application::m_pInputManager->getController(1);
	if (m_pController->isBombPressed()) {
		Menu::getActiveMenu()->enter();
	}

	if (m_pController->isUpPressed()) {
		Menu::getActiveMenu()->up();
		m_pActivateRepetitionTimer->setAlarm(500);
	} else if (m_pController->isDownPressed()) {
		Menu::getActiveMenu()->down();
		m_pActivateRepetitionTimer->setAlarm(500);

	} else if (m_pController->isLeftPressed()) {
		Menu::getActiveMenu()->left();
		m_pActivateRepetitionTimer->setAlarm(500);
	} else if (m_pController->isRightPressed()) {
		Menu::getActiveMenu()->right();
		m_pActivateRepetitionTimer->setAlarm(500);
	} else if (m_pController->isBackPressed()) {
		Menu::getActiveMenu()->back();
	} else if (m_pController->isSpacePressed()) {
		Menu::getActiveMenu()->space();
	}

	//activate Input Repetition, when a key is hold down
	//makes the menues much easier to use
	if (m_pController->isDownHold() &&
	    m_pActivateRepetitionTimer->isTimeUp()) {
		m_pActivateRepetitionTimer->setAlarm(120);
		Menu::getActiveMenu()->down();
	}

	if (m_pController->isUpHold() &&
	    m_pActivateRepetitionTimer->isTimeUp()) {
		m_pActivateRepetitionTimer->setAlarm(120);
		Menu::getActiveMenu()->up();
	}

	if (m_pController->isLeftHold() &&
	    m_pActivateRepetitionTimer->isTimeUp()) {
		m_pActivateRepetitionTimer->setAlarm(120);
		Menu::getActiveMenu()->left();
	}

	if (m_pController->isRightHold() &&
	    m_pActivateRepetitionTimer->isTimeUp()) {
		m_pActivateRepetitionTimer->setAlarm(120);
		Menu::getActiveMenu()->right();
	}
}

void ApplicationMenu::update()
{
	/*	if ( !m_pApp->m_pScreenFader->hasStarted())
	{	
		handleInput();
		Menu::getActiveMenu()->update();
	}
	else
	{
		m_pApp->m_pScreenFader->update();
		if (m_pApp->m_pScreenFader->isDone())
			m_pApp->setState(1);
	}

	*/

	handleInput();
	Menu::getActiveMenu()->update();

	// This section is hackish
	// We check the values of specific Menuitem and decide accordingly

	// start game ?
	if (m_pStartGameMenuItem->getValue() == 1) {
		// reset m_pStartGameMenuItem
		m_pStartGameMenuItem->setValue(0);
		// update config
		storeSettings();

		m_pApp->m_pScreenFader->setAction(ScreenFader::FADEOUT);
		// set app state to running
		m_pApp->setState(1);
	}

	//quit game ?
	if (m_pQuitGameMenuItem->getValue() == 1) {
		m_pApp->setState(3);
	}

	m_pApp->m_pConfig->setMusic(m_pToggleMusicItem->getValue());
	m_pApp->m_pSoundManager->setVolumeSoundFX(
		m_pSoundFXVolumeItem->getValue());
	m_pApp->m_pSoundManager->setVolumeMusic(m_pMusicVolumeItem->getValue());

	//only start/stop Music if Music was stopped / was playing
	if ((m_pToggleMusicItem->getValue() == 1) &&
	    (!m_pApp->m_pSoundManager->isMusicPlaying()))
		m_pApp->m_pSoundManager->playMusic(0);

	if ((m_pToggleMusicItem->getValue() == 0) &&
	    (m_pApp->m_pSoundManager->isMusicPlaying()))
		m_pApp->m_pSoundManager->stopMusic();
}

void ApplicationMenu::draw()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//disable lighting - this way we can speciy text color by calling glColor()
	glDisable(GL_LIGHTING);

	enableOrthoMode();

	// set menu background
	Application::m_pTextureManager->bindTexture(MENU_BACKGROUND_TEXTURE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -100);
	glTexCoord2f(1, 0);
	glVertex3f(Application::screenWidth, 0, -100);
	glTexCoord2f(1, 1);
	glVertex3f(Application::screenWidth, Application::screenHeight, -100);
	glTexCoord2f(0, 1);
	glVertex3f(0, Application::screenHeight, -100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 1, 1);

	// draw Current Menu
	Menu::getActiveMenu()->draw();

	disableOrthoMode();
	//	m_pApp->m_pScreenFader->draw();

	glEnable(GL_LIGHTING);
}
