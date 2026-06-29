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

#include "../Menu/ScoreScreen.h"
#include "../Application.h"
#include "../Engine/TextDrawer.h"
#include "../Gametypes/Game.h"
#include "../Defines.h"
#include "../Controller/Controller.h"
#include "../Engine/ortho.h"
#include "../Engine/MeshManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/InputManager.h"

#include "../Engine/Vector3.h"
#include "../Engine/Wobbler.h"

#include "../MeshObjects/CupMesh.h"
#include "../MeshObjects/PlayerMesh.h"

#include "../Objects/Player.h"

ScoreScreen::ScoreScreen(Game *pGame)
{
	m_pGame = pGame;
	m_bDone = false;
	m_bPaused = false;

	// Init Rows
	m_iRows = m_pGame->getPlayerCount();
	m_pRows = new stRow[m_iRows];

	m_vFirstRowPosition.x = 0.25;
	m_vFirstRowPosition.y = 0.66;
	m_fColumnSpacing = 0.0875;
	m_fRowSpacing = 0.2;
	m_fOffsetLeft = 0.0375;
	m_fCupRotationAngle = 0;

	for (int i = 0; i < m_iRows; i++) {
		m_pRows[i].position.x = m_vFirstRowPosition.x;
		m_pRows[i].position.y =
			m_vFirstRowPosition.y - (i * m_fRowSpacing);

		m_pRows[i].iColumns = m_pGame->getPlayerScore(i);
		m_pRows[i].pPlayer = m_pGame->getPlayer(i);
	}

	// No winner
	if (m_pGame->getWinnerOfRound() == DRAWGAME) {
		SDL_strlcpy(m_cHeading, "Draw Game !", sizeof(m_cHeading));
		m_bDoHandleInput = true;

	} else {
		Player *pPlayer =
			m_pGame->getPlayer(m_pGame->getWinnerOfRound());
		SDL_strlcpy(m_cHeading, pPlayer->getName(), sizeof(m_cHeading));
		SDL_strlcat(m_cHeading, " wins !", sizeof(m_cHeading));

		// The Winner gets a Trophy ! Init Trophys initial position.
		m_vCupPosition.x = 1;
		m_vCupPosition.y =
			m_pRows[m_pGame->getWinnerOfRound()]
				.position
				.y; // 400 - m_pGame->getWinnerOfRound() * 50;
		m_bDoHandleInput = false;
	}

	//init wobbler
	m_pWobbler = new Wobbler();
	m_pWobbler->setRads(5, 5, 5);
	m_pWobbler->setMedians(3, 3, 3);
	m_pWobbler->setMaxima(4, 4, 4);
}

ScoreScreen::~ScoreScreen()
{
	delete[] m_pRows;
	delete m_pWobbler;
}

void ScoreScreen::drawCup()
{
	glEnable(GL_LIGHTING);
	glTranslatef(relToAbs(m_vCupPosition.x, 0), 0, 0.0);
	glPushMatrix();
	// rotates the cup
	//glRotatef(m_fCupRotationAngle,0,1,0);
	glScalef(10 + m_pWobbler->getScaleValueX(),
		 10 + m_pWobbler->getScaleValueY(),
		 10 + m_pWobbler->getScaleValueZ());
	Application::m_pMeshManager->m_pCupMesh->configureMaterial();
	Application::m_pMeshManager->m_pCupMesh->configureTexCoord0();
	Application::m_pMeshManager->m_pCupMesh->configureTexture0(CUP_TEXTURE);
	Application::m_pMeshManager->m_pCupMesh->enableBuffers();
	Application::m_pMeshManager->m_pCupMesh->drawVBO();
	Application::m_pMeshManager->m_pCupMesh->resetTextureEngines();
	Application::m_pMeshManager->m_pCupMesh->disableBuffers();
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

void ScoreScreen::handleInput()
{
	Controller *m_pController =
		Application::m_pInputManager->getController(1);
	if ((!m_bDoHandleInput) || m_bPaused)
		return;

	for (int i = 0; i < 2; i++) {
		// has a player triggered the bomb button ?
		if (m_pController->isBombPressed())
			m_bDone = true;
	}
}

void ScoreScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glDisable(GL_LIGHTING);
	//	glDisable (GL_FOG);
	enableOrthoMode();
	Application::m_pTextDrawer->setSize(BIG);
	Application::m_pTextDrawer->drawTextCentered(0.5, 0.91, m_cHeading);
	Application::m_pTextDrawer->setSize(STD);

	//Give a message when player can continue
	if (m_bDoHandleInput)
		Application::m_pTextDrawer->drawTextCentered(
			0.5, 0.83, "Press return to continue!");

	if (m_bPaused)
		Application::m_pTextDrawer->drawText(0.00625, 0.94,
						     "Game paused!");

	// loop through all rows
	for (int i = 0; i < m_iRows; i++) {
		glPushMatrix();
		//1. Translate to current rows y Pos ( this is our new Origin )
		glTranslatef(relToAbs(m_pRows[i].position.x, 0),
			     relToAbs(m_pRows[i].position.y, 1), 0);

		Application::m_pTextDrawer->drawTextCentered(
			0, -0.042, m_pRows[i].pPlayer->getName());

		//2. Draw player
		glPushMatrix();
		glScalef(80, 80, 80);
		//					Application::m_pTextureManager->bindTexture(m_pRows[i].pPlayer->getSkin());
		//					Application::m_pMeshManager->drawMesh(PLAYER_OBJECT);
		Application::m_pMeshManager->m_pPlayerMesh->configureMaterial();
		Application::m_pMeshManager->m_pPlayerMesh->configureTexCoord0();
		Application::m_pMeshManager->m_pPlayerMesh->configureTexCoord1();

		Application::m_pMeshManager->m_pPlayerMesh->configureTexture0(
			m_pRows[i].pPlayer->getPrimaryTexture());
		Application::m_pMeshManager->m_pPlayerMesh->configureTexture1(
			m_pRows[i].pPlayer->getSecondaryTexture());
		Application::m_pMeshManager->m_pPlayerMesh->enableBuffers();
		Application::m_pMeshManager->m_pPlayerMesh->drawVBO();
		Application::m_pMeshManager->m_pPlayerMesh
			->resetTextureEngines();
		Application::m_pMeshManager->m_pPlayerMesh->disableBuffers();

		glPopMatrix();
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		//loop through all slots
		// add a small offset to the players column
		glTranslatef(relToAbs(m_fOffsetLeft, 0), 0, 0);
		// 3. draw Cups
		for (int j = 0;
		     j < Application::m_pConfig->getPointsForVictory(); j++) {
			glTranslatef(relToAbs(m_fColumnSpacing, 0), 0, 0);
			if (j < m_pRows[i].iColumns) {
				glPushMatrix();
				glScalef(10, 10, 10);
				Application::m_pMeshManager->m_pCupMesh
					->configureMaterial();
				Application::m_pMeshManager->m_pCupMesh
					->configureTexCoord0();
				Application::m_pMeshManager->m_pCupMesh
					->configureTexture0(CUP_TEXTURE);
				Application::m_pMeshManager->m_pCupMesh
					->enableBuffers();
				Application::m_pMeshManager->m_pCupMesh
					->drawVBO();
				Application::m_pMeshManager->m_pCupMesh
					->resetTextureEngines();
				Application::m_pMeshManager->m_pCupMesh
					->disableBuffers();
				glPopMatrix();
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glEnable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
					  GL_MODULATE);
			}
			//4. draw small white blocks beneath the cup positions
			glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(0, -20, 0);
			glBegin(GL_QUADS);
			glVertex3f(-10, -5, 0);
			glVertex3f(10, -5, 0);
			glVertex3f(10, 5, 0);
			glVertex3f(-10, 5, 0);
			glEnd();
			glPopMatrix();
		}

		glPopMatrix();
	}
	// draw Cup
	glPushMatrix();
	// Translate to winners rows
	glTranslatef(relToAbs(m_pRows[m_pGame->getWinnerOfRound()].position.x +
				      m_fOffsetLeft,
			      0),
		     relToAbs(m_pRows[m_pGame->getWinnerOfRound()].position.y,
			      1),
		     0);
	if (m_pGame->getWinnerOfRound() != DRAWGAME)
		//	drawCup( m_pGame->getWinnerOfRound(),m_pGame->getPlayerScore(m_pGame->getWinnerOfRound())+1 );
		drawCup();
	glPopMatrix();

	disableOrthoMode();
	glEnable(GL_LIGHTING);

	glClear(GL_DEPTH_BUFFER_BIT);
}

void ScoreScreen::startPause()
{
	m_bPaused = true;
}

void ScoreScreen::stopPause()
{
	m_bPaused = false;
}

void ScoreScreen::update()
{
	handleInput();

	//rotates the cup
	/*	m_fCupRotationAngle += 90 * Application::m_fReciprocalFPS;
	if (m_fCupRotationAngle >= 360)
		m_fCupRotationAngle = 0;*/
	if (!m_bPaused) {
		m_pWobbler->update();
		if (m_vCupPosition.x >
		    ((m_pGame->getPlayerScore(m_pGame->getWinnerOfRound()) + 1) *
		     m_fColumnSpacing)) {
			m_vCupPosition.x -=
				(0.4 * Application::m_fReciprocalFPS);
		} else
			//allow player to continue by pressing the bomb key, if animation is done
			m_bDoHandleInput = true;
	}
	//	draw();
}
