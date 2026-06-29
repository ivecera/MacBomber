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

#include <GLUT/glut.h>
#include <OpenGL/glext.h>

#include "Defines.h"
#include "PlayerSetupItem.h"
#include "ToggleItem.h"
#include "../Application.h"
#include "../Engine/MeshManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/TextDrawer.h"
#include "../Engine/ortho.h"

#include "../MeshObjects/PlayerMesh.h"

PlayerSetupItem::PlayerSetupItem(int value)
	: ToggleItem(" ")
{
	addOption("Red Mac", PLAYER1_TEXTURE);
	addOption("Brown Mac", PLAYER2_TEXTURE);
	addOption("Blue Mac", PLAYER3_TEXTURE);
	addOption("White Mac", PLAYER4_TEXTURE);

	setValue(value);
}

void PlayerSetupItem::draw()
{
	glPushMatrix();
	glTranslatef(relToAbs(m_vPosition.x, 0), relToAbs(m_vPosition.y, 1),
		     -30);
	glPushMatrix();
	glScalef(80, 80, 80);
	Application::m_pMeshManager->m_pPlayerMesh->configureMaterial();
	Application::m_pMeshManager->m_pPlayerMesh->configureTexCoord0();
	Application::m_pMeshManager->m_pPlayerMesh->configureTexCoord1();
	Application::m_pMeshManager->m_pPlayerMesh->configureTexture0(
		(*m_itIterator).value);
	Application::m_pMeshManager->m_pPlayerMesh->configureTexture1(
		PLAYER_HAPPY_TEXTURE);
	Application::m_pMeshManager->m_pPlayerMesh->enableBuffers();
	Application::m_pMeshManager->m_pPlayerMesh->drawVBO();
	Application::m_pMeshManager->m_pPlayerMesh->resetTextureEngines();
	Application::m_pMeshManager->m_pPlayerMesh->disableBuffers();

	glPopMatrix();

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	Application::m_pTextDrawer->drawText(0.03, 0, (*m_itIterator).name);

	glPopMatrix();

	if (m_bActive)
		drawQuad();
}
