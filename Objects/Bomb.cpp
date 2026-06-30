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

#include "../Engine/MatrixStack.h"
#include "Bomb.h"
#include "../Engine/MeshManager.h"
#include "../Engine/TriangleMesh.h"
#include "../MeshObjects/BombMesh.h"

#include "../Defines.h"
#include "../Application.h"
#include "../Engine/SoundManager.h"
#include "../Engine/Wobbler.h"
int Bomb::m_iBombNr = 0;

Bomb::Bomb(int xBlock, int zBlock, int owner, int strength)
	: Object_Moving(xBlock, zBlock, 0.9f)
{
	m_iType = BOMB_OBJECT;

	m_iOwnerID = owner;
	m_bOwnerLeft = false;

	m_iStrength = strength;
	m_bExploded = false;

	m_StartExplosionTimer = Timer(2500);

	m_fVelocity = 3;
	m_iBombID = m_iBombNr++;

	m_bWobble = true;
	m_pWobbler->setRads(0.785, 2.35, 0.785);
	m_pWobbler->setMedians(0.8, 0.9, 0.8);

	m_vPos.y = 0.0f;
}

void Bomb::explode()
{
	// If the bomb is moving, stop the movement
	m_iDirection = NONE;
	m_bExploded = true;

	Application::m_pSoundManager->playSoundFX(EXPlOSION_SOUND);
}

bool Bomb::isExploded()
{
	return m_bExploded;
}

int Bomb::getStrength()
{
	return m_iStrength;
}

bool Bomb::doesMove()
{
	if (m_iDirection == NONE)
		return false;
	else
		return true;
}

void Bomb::stopMovement()
{
	m_iDirection = NONE;
	m_vPos.x = m_xBlock + 0.5f;
	m_vPos.z = m_zBlock + 0.5f;
}

void Bomb::update()
{
	if (m_bWobble)
		m_pWobbler->update();
}

void Bomb::draw()
{
	modelview.push();
	modelview.translate(m_vPos.x, m_vPos.y, m_vPos.z);

	if (m_bWobble)
		modelview.scale(m_pWobbler->getScaleValueX(),
				m_pWobbler->getScaleValueY(),
				m_pWobbler->getScaleValueZ());

	modelview.apply();
	Application::m_pMeshManager->m_pBombMesh->drawVBO();

	modelview.pop();
}
