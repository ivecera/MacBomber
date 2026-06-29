/*
 *  Game_Standard.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 15.09.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game_Standard.h"
#include "../Application.h"
#include "../Engine/SoundManager.h"
#include "../Menu/ScoreScreen.h"

#include "../Engine/MeshManager.h"
#include "../MeshObjects/PlayerMesh.h"

#include "../Map/Map.h"
#include "../Objects/Player.h"
#include "../Menu/HUD.h"

Game_Standard::Game_Standard(Application *pApp)
	: Game(pApp)
{
	startNextRound();
}

Game_Standard::~Game_Standard()
{
}

void Game_Standard::updateRunning()
{
	//if no or only 1 Players are alive then ...
	if (m_iAlivePlayerCount <= 1) {
		if (!m_bDeathBell) { //...let the round end ahead of time, by reseting the timer
			m_tRoundTimer.setAlarm(3000);
			m_bDeathBell = true;
			m_pHUD->doDrawTime(false);
		}
	}

	//check if time is up !
	if (m_tRoundTimer.isTimeUp()) {
		// check which player won
		m_iWinner = determineWinner();

		// time is Up ! generate a scorescreen & switch State to ScoreScreen
		m_pScoreScreen = new ScoreScreen(this);
		m_iState = SCORESCREEN;
		Application::m_pSoundManager->playMusic(SCORESCREEN_MUSIC,
							false);
	}
	//	return true;
}

void Game_Standard::startNextRound()
{
	_startNextRound();
}

void Game_Standard::drawRunning()
{
	Application::m_pMeshManager->m_pPlayerMesh->configureMaterial();
	Application::m_pMeshManager->m_pPlayerMesh->configureTexCoord0();
	Application::m_pMeshManager->m_pPlayerMesh->configureTexCoord1();

	Application::m_pMeshManager->m_pPlayerMesh->enableBuffers();

	//draw all Players
	for (int i = 0; i < m_pApp->m_pConfig->getPlayerCount(); i++)
		m_pPlayer[i]->draw();

	Application::m_pMeshManager->m_pPlayerMesh->disableBuffers();
	Application::m_pMeshManager->m_pPlayerMesh->resetTextureEngines();

	//draw Map (including all explosions, particle FX, etc.)...
	m_pMap->draw();
	//....and above all the HUD
	m_pHUD->draw();
}
