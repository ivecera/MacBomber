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

#include "Crate.h"
#include "../Engine/MeshManager.h"
#include "../MeshObjects/CrateMesh.h"

#include "../Application.h"

Crate::Crate(int xBlock, int zBlock)
	: Object(xBlock, zBlock)
{
	m_iType = CRATE_OBJECT;
	//randomly choose between 0,90,180 and 270
	m_iOrientation = (SDL_rand(4)) * 90;
}

void Crate::draw()
{
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(m_iOrientation, 0, 1, 0);
	Application::m_pMeshManager->m_pCrateMesh->drawVBO();
}