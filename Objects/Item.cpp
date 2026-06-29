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

#include "Item.h"
#include <SDL3/SDL_opengl.h>
#include "../Engine/MeshManager.h"
#include "../Engine/Wobbler.h"

#include "../MeshObjects/ItemMesh.h"

#include "../Application.h"

Item::Item(int xBlock, int zBlock)
	: Object_Moving(xBlock, zBlock, 1.0f)
{
	m_iType = 0;

	m_bWobble = true;
	m_pWobbler->setRads(0, 0, 0);
	m_pWobbler->setRadSpeeds(2, 2, 2);
	m_pWobbler->setMedians(0.9, 0.9, 0.9);
	m_pWobbler->setMaxima(0.1, 0.1, 0.1);
	m_vPos.y = 0.0;
}

void Item::showType()
{
	printf("Picked Up: ");
	switch (m_iType) {
	case BOMBUP:
		printf("BOMBUP\n");
		break;
	case SPEEDUP:
		printf("SPEEDUP\n");
		break;
	case POWERUP:
		printf("POWERUP\n");
		break;
	case ENABLEKICK:
		printf("ENABLEKICK\n");
		break;

	case JOINT:
		printf("JOINT\n");
		break;
	case COCAINE:
		printf("COCAINE\n");
		break;
	case VIAGRA:
		printf("VIAGRA\n");
		break;
	}
}

void Item::update()
{
	if (m_bWobble)
		m_pWobbler->update();
}

void Item::draw()
{
	glPushMatrix();
	// FIX ME: we add 0.5 to m_vPos because the bottom of the item model bottom is at y= -0.5;
	glTranslatef(m_vPos.x, m_vPos.y + 0.5, m_vPos.z);
	glRotatef(
		180, 0, 1,
		0); //rotate around y-axis, Makes items face in the right direction.

	if (m_bWobble)
		glScalef(m_pWobbler->getScaleValueX(),
			 m_pWobbler->getScaleValueY(),
			 m_pWobbler->getScaleValueZ());

	Application::m_pMeshManager->m_pItemMesh->configureTexture0(m_iTexture);
	Application::m_pMeshManager->m_pItemMesh->drawVBO();

	glPopMatrix();
}
