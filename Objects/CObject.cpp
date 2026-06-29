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

#include "CObject.h"
#include "../Engine/CWobbler.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTextureManager.h"



CObject::CObject( int xBlock, int zBlock, float size )
{
    m_fSize = size;
    
    m_xBlock = xBlock;
    m_zBlock = zBlock;
    
    m_vPos.x = xBlock + 0.5f;
    m_vPos.z = zBlock + 0.5f;
    m_vPos.y = 0.5f;
        
    m_pBBox = new CBoundingBox_2D(m_vPos, m_fSize);
	m_pBBox->update(m_vPos);
	
	m_bWobble  = false;
	m_pWobbler = new CWobbler();
	
}
CObject::~CObject()
{
	delete m_pBBox;
	delete m_pWobbler;
}


int CObject::getXBlock()
{
    return m_xBlock;
}

int CObject::getZBlock()
{
    return m_zBlock;
}

float CObject::getSize()
{
    return m_fSize;
}

void CObject::setPosition(CVector3 vPos)
{
	m_vPos = vPos;
	m_xBlock =  int(vPos.x);
	m_zBlock =  int(vPos.z);
	m_pBBox->update(m_vPos);

}

CVector3 CObject::getPosition()
{
    return m_vPos;
}

CBoundingBox_2D * CObject::getBoundingBox()
{
	return m_pBBox;
}

bool CObject::doesCollideWith(CObject * pObject)
{
	return m_pBBox->doesCollideWith(pObject->getBoundingBox());
}

void CObject::setWobble(bool bWobble)
{
	m_bWobble = bWobble;
}
