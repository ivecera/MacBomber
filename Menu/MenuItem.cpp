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

#include "../Application.h"
#include "MenuItem.h"
#include "Menu.h"
#include "../Engine/TextureManager.h"
#include "../Engine/ortho.h"

#include "../Defines.h"
#include <SDL3/SDL_opengl.h>

#include "../Engine/TextDrawer.h"

MenuItem::MenuItem(const char *caption)
{
	m_vPosition = Vector3(0, 0, 0);
	//	m_cCaption = caption;
	SDL_strlcpy(m_cCaption, caption, sizeof(m_cCaption));
	m_bActive = false;
	m_bInteractive = true;
	m_iValue = 0; // NEW
}

void MenuItem::drawQuad()
{
	float blah[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, blah);
	glColor3f(1.0f, 0.58f, 0.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glPushMatrix();
	Application::m_pTextureManager->bindTexture(MENU_ARROW_TEXTURE);
	glTranslatef(relToAbs(m_vPosition.x - 0.031, 0),
		     relToAbs(m_vPosition.y + 0.013, 1), 0);
	//		glNormal3f(0,0,1);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(20, 20, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-20, 20, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-20, -20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(20, -20, 0);
	glEnd();
	glColor3f(1.0f, 1.0, 1.0f);

	glPopMatrix();
	glDisable(GL_BLEND);
}

void MenuItem::setActive(bool bActive)
{
	m_bActive = bActive;
}

//specifies the position of this MenuItem
void MenuItem::setPosition(Vector3 vPosition)
{
	m_vPosition = vPosition;
}

int MenuItem::getValue()
{
	return m_iValue;
}
