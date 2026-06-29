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

#include "Object.h"
#include "../Engine/Wobbler.h"
#include "../Engine/MeshManager.h"
#include "../Engine/TextureManager.h"

Object::Object(int xBlock, int zBlock, float size)
{
	m_fSize = size;

	m_xBlock = xBlock;
	m_zBlock = zBlock;

	m_vPos.x = xBlock + 0.5f;
	m_vPos.z = zBlock + 0.5f;
	m_vPos.y = 0.5f;

	m_pBBox = new BoundingBox_2D(m_vPos, m_fSize);
	m_pBBox->update(m_vPos);

	m_bWobble = false;
	m_pWobbler = new Wobbler();
}
Object::~Object()
{
	delete m_pBBox;
	delete m_pWobbler;
}

int Object::getXBlock()
{
	return m_xBlock;
}

int Object::getZBlock()
{
	return m_zBlock;
}

float Object::getSize()
{
	return m_fSize;
}

void Object::setPosition(Vector3 vPos)
{
	m_vPos = vPos;
	m_xBlock = int(vPos.x);
	m_zBlock = int(vPos.z);
	m_pBBox->update(m_vPos);
}

Vector3 Object::getPosition()
{
	return m_vPos;
}

BoundingBox_2D *Object::getBoundingBox()
{
	return m_pBBox;
}

bool Object::doesCollideWith(Object *pObject)
{
	return m_pBBox->doesCollideWith(pObject->getBoundingBox());
}

void Object::setWobble(bool bWobble)
{
	m_bWobble = bWobble;
}
