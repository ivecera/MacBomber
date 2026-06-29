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
#include "HUD.h"

#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#include "../Application.h"
#include "../Gametypes/Game.h"
#include "../Defines.h"
#include "../Engine/TextDrawer.h"
#include "../Engine/TextureManager.h"
#include "../Engine/ortho.h"
#include "../Engine/Timer.h"
#include "../Engine/intToString.h"
#include "../Engine/Camera.h"
#include "../Map/MapManager.h"
#include "../Map/StMapEntry.h"
#include "Timebar.h"

#include <iostream>
#include <sstream>
HUD::HUD(int index)
{
	StMapEntry tmpEntry = Application::m_pMapManager->getMap(index);
	m_strLevelName = string(tmpEntry.name);
	m_fLevelName_Xpos = 1 - Application::m_pTextDrawer->getLength(
					m_strLevelName.c_str());
	m_fMargin = 0.00625;
	m_fScalefactor_Warning = 0;
	m_fAlpha_Warning = 1;

	m_bDrawTime = true;
	m_bDrawWarning = false;
	m_bPause = false;
	m_pTimebar = new Timebar(Application::m_pGame->getTotalTime());
}
HUD::~HUD()
{
	delete m_pTimebar;
}

void HUD::drawTime()
{
	if (m_bDrawTime) {
		Application::m_pTextureManager->bindTexture(CLOCK_TEXTURE);
		glEnable(GL_BLEND);
		glPushMatrix();
		glTranslatef(relToAbs(m_fMargin, 0), relToAbs(0.94, 1), 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(40, 40, 0);
		glTexCoord2f(0, 1);
		glVertex3f(0, 40, 0);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3f(40, 0, 0);
		glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);

		string strTime = convertValueToString(m_iTime);
		Application::m_pTextDrawer->drawText(m_fMargin + 0.05, 0.96,
						     strTime.c_str());
		//	m_pTimebar->draw();
	}
}

void HUD::drawWarning()
{
	if (m_bDrawWarning) {
		glColor4f(1, 0, 0, m_fAlpha_Warning);
		glEnable(GL_BLEND);
		Application::m_pTextDrawer->setSize(BIG);
		Application::m_pTextDrawer->drawTextCentered(
			0.5, 0.5, "Hurry up!", m_fScalefactor_Warning);
		Application::m_pTextDrawer->setSize(STD);
		glDisable(GL_BLEND);
		glColor3f(1, 1, 1);
	}
}

void HUD::drawLevelName()
{
	Application::m_pTextDrawer->drawTextCentered(0.5, 0.96,
						     m_strLevelName.c_str());
}

void HUD::drawView()
{
	Application::m_pTextureManager->bindTexture(EYE_TEXTURE);
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(relToAbs(1 - m_fMargin - 0.08, 0), relToAbs(0.94, 1), 0);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(40, 40, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 40, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(40, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);

	string strView = convertValueToString(m_iView);
	Application::m_pTextDrawer->drawText(1 - m_fMargin - 0.02, 0.96,
					     strView.c_str());
}

void HUD::startPause()
{
	m_bPause = true;
}

void HUD::stopPause()
{
	m_bPause = false;
}

void HUD::update()
{
	m_iTime = (Application::m_pConfig->getRoundTime() * 1000 -
		   Application::m_pGame->getElapsedTime()) /
		  1000;
	m_iView = Application::m_pCamera->getPreset() +
		  1; // +1: don't let view indeces star at 0

	if (m_iTime <= 33) {
		m_bDrawWarning = true;

		if (m_iTime >= 31) {
			if (m_fScalefactor_Warning >= 1)
				m_fScalefactor_Warning = 1;
			else
				m_fScalefactor_Warning +=
					2 * Application::m_fReciprocalFPS;

		} else if (m_iTime >= 29) {
			m_fScalefactor_Warning +=
				3 * Application::m_fReciprocalFPS;
			m_fAlpha_Warning -= 1 * Application::m_fReciprocalFPS;
		} else
			m_bDrawWarning = false;
	}

	m_pTimebar->update(m_iTime);
}

void HUD::draw()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//disable lighting - this way we can speciy text color by calling glColor()
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	enableOrthoMode();
	if (m_bPause == false) {
		drawTime();
	} else {
		Application::m_pTextDrawer->drawText(m_fMargin, 0.96,
						     "Game paused!");
	}
	drawWarning();
	drawLevelName();
	drawView();

	disableOrthoMode();
	glEnable(GL_LIGHTING);
}
