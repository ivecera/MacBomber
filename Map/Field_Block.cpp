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

#include "Field_Block.h"
#include "../Engine/TriangleMesh.h"
#include "../Engine/MeshManager.h"
#include "../MeshObjects/BlockMesh.h"
#include "../Application.h"
#include "../Defines.h"

Field_Block::Field_Block(int xGrid, int yGrid, Map *pMap)
	: Field(xGrid, yGrid, pMap)
{
	m_iType = BLOCK;
	m_bFree = false;
	m_vPos.y = 0.0f;

	//randomly choose between 0,90,180 and 270
	m_iOrientation = (rand() % 4) * 90;
}

bool Field_Block::placeBomb(Bomb *bomb)
{
	delete bomb;
	return false;
}

void Field_Block::draw()
{
	glPushMatrix();
	glTranslatef(m_vPos.x, m_vPos.y, m_vPos.z);

	if (m_iState == FALLING) {
		glRotatef(m_fAngle, 0, 1, 0);
		glRotatef(5, 1, 0, 0);
	}

	glRotatef(m_iOrientation, 0, 1, 0);
	Application::m_pMeshManager->m_pBlockMesh->drawVBO();
	glPopMatrix();
}

void Field_Block::update()
{
	if (m_iState == FALLING) {
		m_vPos.y -= (Application::m_fReciprocalFPS * 4);
		m_fAngle += (Application::m_fReciprocalFPS * 90);
	}
}
