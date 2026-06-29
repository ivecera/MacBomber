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

#include "Game.h"
#include "../Objects/Player.h"
#include "../Map/Map.h"
#include "../Map/MapManager.h"
#include "../Map/MapPlaylist.h"
#include "../Map/MapDestroyer.h"
#include "../Menu/ScoreScreen.h"
#include "../Application.h"
#include "../Engine/SoundManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/Clock.h"
#include "../Engine/ortho.h"

#include "../Config.h"

#include "../Menu/HUD.h"

Game::Game(Application *pApp)
{
	m_pApp = pApp;

	for (int i = 0; i < 4; i++) {
		m_pPlayer[i] = NULL;
		m_iPlayerScore[i] = 0;
	}
	m_iAlivePlayerCount = 4;
	m_pMap = NULL;

	m_pScoreScreen = NULL;
	m_pHUD = NULL;
	m_iCurrentRound = 0;
	m_iState = RUNNING;
	m_bPaused = false;

	m_pPlaylist = m_pApp->m_pMapManager->getPlaylist();
	compileBackgroundDisplayList();
}

Game::~Game()
{
	delete m_pMap;

	if (m_pScoreScreen != NULL)
		delete m_pScoreScreen;

	delete m_pHUD;

	for (int i = 0; i < m_pApp->m_pConfig->getPlayerCount(); i++)
		delete m_pPlayer[i];

	delete m_pPlaylist;
	glDeleteLists(m_iBackgroundDL, 1);
}

void Game::compileBackgroundDisplayList()
{
	m_iBackgroundDL = glGenLists(1);
	glNewList(m_iBackgroundDL, GL_COMPILE);
	enableOrthoMode();
	glDepthMask(false);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	Application::m_pTextureManager->bindTexture(GAME_BACKGROUND_TEXTURE);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -20);
	glTexCoord2f(1, 0);
	glVertex3f(Application::screenWidth, 0, -20);
	glTexCoord2f(1, 1);
	glVertex3f(Application::screenWidth, Application::screenHeight, -20);
	glTexCoord2f(0, 1);
	glVertex3f(0, Application::screenHeight, -20);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	disableOrthoMode();
	glEndList();
}

int Game::determineWinner()
{
	// index of the surviving player
	int iAlivePlayerIndex = 0;
	int iAlivePlayerCount = m_pApp->m_pConfig->getPlayerCount();

	//determine if there is a Winner
	for (int i = 0; i < m_pApp->m_pConfig->getPlayerCount(); i++) {
		m_pPlayer[i]->update();

		//is current player dead ?
		if (m_pPlayer[i]->isDead())
			iAlivePlayerCount--;
		else
			iAlivePlayerIndex = i;
	}

	//Hey, we have a survivour over here !
	if (iAlivePlayerCount == 1)
		return iAlivePlayerIndex;
	else
		//there are none or >1  players alive
		return DRAWGAME;
}

void Game::updateScoreScreen()
{
	m_pScoreScreen->update();
	// did the user requested to exit the scorescreen ?
	if (m_pScoreScreen->done()) {
		// Did the winner of the last round reach MaxRounds ...
		if (++m_iPlayerScore[m_iWinner] ==
		    m_pApp->m_pConfig->getPointsForVictory()) {
			m_iState = GAMEOVER;
		} else // ..carry on
		{
			m_iState = RUNNING;
			//					m_pApp->m_pMapManager->setNextMap();
			m_pPlaylist->setNextMapIndex();
			startNextRound();
		}
	}
}

void Game::_startNextRound()
{
	//delete old Map and players if present
	if (m_pMap != NULL) {
		delete m_pMap;
		m_pMap = NULL;
	}

	//delete ScoreScreen
	if (m_pScoreScreen != NULL) {
		delete m_pScoreScreen;
		m_pScoreScreen = NULL;
	}

	//delete HUD
	if (m_pHUD != NULL) {
		delete m_pHUD;
		m_pHUD = NULL;
	}

	//delete *all* player Slots
	for (int i = 0; i < 4; i++) {
		if (m_pPlayer[i] != NULL) {
			delete m_pPlayer[i];
			m_pPlayer[i] = NULL;
		}
	}

	m_pMap = new Map(this, m_pPlaylist->getCurrentMapIndex());

	// 2. create Players

	int j = 0;
	int iKeySet = 0;
	//loop through all slots
	for (int i = 0; i < 4; i++) {
		// check if player i is enabled
		if (m_pApp->m_pConfig->isPlayerEnabled(i)) {
			// if so, create a new player & configue him according to Config
			m_pPlayer[j] = new Player(
				j, m_pMap, m_pMap->getPlayerStartPositionX(i),
				m_pMap->getPlayerStartPositionZ(i));
			m_pPlayer[j]->setPrimaryTexture(
				m_pApp->m_pConfig->getPlayerSkin(i));
			iKeySet = m_pApp->m_pConfig->getPlayerKeySet(i);

			m_pPlayer[j]->attachController(
				Application::m_pInputManager->getController(
					iKeySet));
			j++;
		}
	}

	// 3. reset round Clock
	Application::m_pClock->reset();
	m_tRoundTimer.setAlarm(m_pApp->m_pConfig->getRoundTime() * 1000);
	m_bDeathBell = false;

	// 4. Create a HUD
	m_pHUD = new HUD(m_pPlaylist->getCurrentMapIndex());

	// 5. start Music
	Application::m_pSoundManager->playMusic(GAME_MUSIC);

	m_iCurrentRound++;
}

int Game::getPlayerCount()
{
	return m_pApp->m_pConfig->getPlayerCount();
}

Player *Game::getPlayer(int playerNr)
{
	if (playerNr < m_pApp->m_pConfig->getPlayerCount())
		return m_pPlayer[playerNr];
	else
		return NULL;
}

Uint32 Game::getElapsedTime()
{
	return (m_tRoundTimer.getElapsedTime());
}

Uint32 Game::getTotalTime()
{
	return m_pApp->m_pConfig->getRoundTime();
}

void Game::update()
{
	int iAlivePlayerCount = 0;
	switch (m_iState) {
	case GAMEOVER:
		m_pApp->setState(0);
		break;

	case SCORESCREEN:
		updateScoreScreen();
		break;

	case RUNNING:
		if (!m_bPaused) {
			iAlivePlayerCount = m_pApp->m_pConfig->getPlayerCount();
			for (int i = 0; i < m_pApp->m_pConfig->getPlayerCount();
			     i++) {
				m_pPlayer[i]->update();

				//is current player dead ?
				if (m_pPlayer[i]->isDead())
					iAlivePlayerCount--;
			}
			m_iAlivePlayerCount = iAlivePlayerCount;
			m_pMap->update();
			m_pHUD->update();

			updateRunning();
		} else
			m_pHUD->update();

		break;
		break;
	} //switch
	//should never reach here
}

void Game::startPause()
{
	//only pause if we are not in scorescreen
	/*	if (m_iState == RUNNING)
	{
		m_iState = PAUSED;
		Application::m_pClock->startPause();
	}*/
	if (!m_bPaused) {
		m_bPaused = true;
		m_pHUD->startPause();
		if (m_iState == SCORESCREEN)
			m_pScoreScreen->startPause();
	}
}

void Game::stopPause()
{
	/*	if (m_iState == PAUSED)
	{
		m_iState = RUNNING;
		Application::m_pClock->stopPause();
	}*/
	if (m_bPaused) {
		m_bPaused = false;
		//Application::m_pClock->stopPause();
		m_pHUD->stopPause();
		if (m_iState == SCORESCREEN)
			m_pScoreScreen->stopPause();
	}
}

bool Game::isPaused()
{
	return m_bPaused;
}

void Game::abort()
{
	m_iState = GAMEOVER;
}

void Game::draw()
{
	switch (m_iState) {
	case GAMEOVER:
		break;
	case SCORESCREEN:
		m_pScoreScreen->draw();
		break;
	case RUNNING:
		glCallList(m_iBackgroundDL);
		drawRunning();
		break;
	};
}
