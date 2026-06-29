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

#include "ScreenFader.h"
#include <SDL_opengl.h>
#include "ortho.h"
#include "../Application.h"

ScreenFader::ScreenFader()
{
	m_iAction = NOACTION;
	m_fAlpha = 1;
	m_bDone = true;
	m_bTransitionStarted = false;
}

// tell screenfader what to do
void ScreenFader::setAction(enAction action)
{
	switch (action) {
	case FADEIN:
		m_fAlpha = 0;
		m_bDone = false;
		m_bTransitionStarted = true;
		break;
	case FADEOUT:
		m_fAlpha = 1;
		m_bDone = false;
		m_bTransitionStarted = true;
		break;
	default:
		break;
	}
	m_iAction = action;
}

bool ScreenFader::hasStarted()
{
	return m_bTransitionStarted;
}

//returns true if current transition is done
bool ScreenFader::isDone()
{
	return m_bDone;
}

void ScreenFader::update()
{
	switch (m_iAction) {
	case (FADEOUT):
		m_fAlpha -= (Application::m_fReciprocalFPS);
		if (m_fAlpha < 0) {
			m_fAlpha = 0;
			m_iAction = NOACTION;
			m_bDone = true;
			m_bTransitionStarted = false;
		}
		break;

	case (FADEIN):
		m_fAlpha += (Application::m_fReciprocalFPS);
		if (m_fAlpha > 1) {
			m_fAlpha = 1;
			m_iAction = NOACTION;
			m_bDone = true;
			m_bTransitionStarted = false;
		}
		break;

	default:
		break;
	}
}

void ScreenFader::fadeIn()
{
	m_iAction = FADEIN;
}

void ScreenFader::fadeOut()
{
	m_iAction = FADEOUT;
}

void ScreenFader::draw()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	enableOrthoMode();
	glColor4f(1, 0, 0, 1);

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 10);
	glVertex3f(Application::screenWidth, 0, 10);
	glVertex3f(Application::screenWidth, Application::screenHeight, 10);
	glVertex3f(0, Application::screenHeight, 10);
	glEnd();

	disableOrthoMode();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glColor4f(1, 1, 1, 1);
}
