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


#include "CMap.h"
#include "../Engine/CBoundingBox_2D.h"
#include "../Objects/CObject_Moving.h"
#include "../Objects/CPlayer.h"
#include "../Objects/CBomb.h"
#include "../Objects/CBombThrower.h"
#include "../Objects/CItem.h"
#include "../Objects/CItemThrower.h"

#include "../Engine/CMeshManager.h"
#include "../MeshObjects/CBlockMesh.h"
#include "../MeshObjects/CCrateMesh.h"
#include "../MeshObjects/CSquareMesh.h"
#include "../MeshObjects/CBombMesh.h"
#include "../MeshObjects/CItemMesh.h"

#include "../Map/CShaker.h"
#include "../Map/CField.h"
#include "../Map/CField_Plain.h"
#include "../Map/CField_Block.h"
#include "../Map/CField_Void.h"
#include "../Map/CField_Hole.h"
#include "../Map/CField_Arrow.h"
#include "../Objects/CCrate.h"
#include "../CApplication.h"
#include "../Engine/CCamera.h"

#include "../Gametypes/CGame.h"
#include "../Engine/ParticleSystem/CParticleManager.h"
#include "CMapManager.h"
#include "StMapEntry.h"


int CMap::m_iBombsOnField[4] = {0,0,0,0};


CMap::CMap(CGame * pGame, int mapIndex)
{
    m_iWidth    = 19;
    m_iHeight   = 15;
	m_iFieldCount = m_iWidth * m_iHeight;
	m_pGame = pGame;
	
	StMapEntry entry = CApplication::m_pMapManager->getMap(mapIndex);
	
	m_iPlayerCount = entry.playerCount;
	char (*pArray)[19] = entry.cArray;

	m_pBombThrower = NULL; 
	m_bBombThrower = false;
	
	m_pShaker = new CShaker();

	// used to make the map look like a checkerboard
	int color = 1;
	bool bColor0 = true;
	
	// Read char Array line by line
	for ( int i = 0; i < 15; i++ )			// z-Pos
	{
		for ( int j = 0; j < 19; j++ )		// x-Pos
		{
			switch (pArray[i][j])
			{
				case ' ':
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}					
					break;
				case '+':
				{
					CField * pField = new CField_Plain(j,i,true,this);
					m_pMap[j][i] = pField;
					m_listCrateFields.push_back(m_pMap[j][i]);
				}
					break;
				case '*':
					m_pMap[j][i] = new CField_Block(j,i,this);
					m_listBlockFields.push_back(m_pMap[j][i]);
					break;
				case '-':
					m_pMap[j][i] = new CField_Void(j,i,this);
					m_iFieldCount--;
					break;
				case 'o':
					//this map has at least one hole -> create a bombthrower
					if (!m_bBombThrower)
					{
						m_pBombThrower = new CBombThrower(this); 
						m_bBombThrower = true;
					}
					
					m_pMap[j][i] = new CField_Hole(j,i,this);
					if (bColor0)
					{
						m_listHoleFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listHoleFields_Color1.push_back(m_pMap[j][i]);
					}
					break;
				case 'R':
					if ( (rand() %3) == 0)
					{
						CField * pField = new CField_Plain(j,i,true,this);
						m_pMap[j][i] = pField;
						m_listCrateFields.push_back(m_pMap[j][i]);

					}
					else
					{
						m_pMap[j][i] = new CField_Plain(j,i,false,this);
						if (bColor0)
						{
							m_listPlainFields_Color0.push_back(m_pMap[j][i]);
						}
						else
						{
							m_listPlainFields_Color1.push_back(m_pMap[j][i]);
						}
					}	
					break;
					
				case '>':
					m_pMap[j][i] = new CField_Arrow(j,i,RIGHT,this);
					if (bColor0)
					{
						m_listArrowFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listArrowFields_Color1.push_back(m_pMap[j][i]);
					}
					break;
				case '<':
					m_pMap[j][i] = new CField_Arrow(j,i,LEFT,this);
					if (bColor0)
					{
						m_listArrowFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listArrowFields_Color1.push_back(m_pMap[j][i]);
					}
					break;
				case '^':
					m_pMap[j][i] = new CField_Arrow(j,i,UP,this);
					if (bColor0)
					{
						m_listArrowFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listArrowFields_Color1.push_back(m_pMap[j][i]);
					}
					break;
				case 'v':
					m_pMap[j][i] = new CField_Arrow(j,i,DOWN,this);
					if (bColor0)
					{
						m_listArrowFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listArrowFields_Color1.push_back(m_pMap[j][i]);
					}
					break;
				
		
				case '0':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[0].x = j;
					m_StPlayerStartPos[0].z = i;
				}
					break;
				case '1':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[1].x = j;
					m_StPlayerStartPos[1].z = i;					
				}
					break;
				case '2':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[2].x = j;
					m_StPlayerStartPos[2].z = i;
				}
					break;
					
				case '3':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[3].x = j;
					m_StPlayerStartPos[3].z = i;
				}
					break;
				case '4':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[4].x = j;
					m_StPlayerStartPos[4].z = i;
				}
					break;
				case '5':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[5].x = j;
					m_StPlayerStartPos[5].z = i;
				}
					break;
					
				case '6':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[6].x = j;
					m_StPlayerStartPos[6].z = i;
				}
					break;
				case '7':
				{
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					m_StPlayerStartPos[7].x = j;
					m_StPlayerStartPos[7].z = i;
				}
					break;
					
				default:
					m_pMap[j][i] = new CField_Plain(j,i,false,this);
					if (bColor0)
					{
						m_listPlainFields_Color0.push_back(m_pMap[j][i]);
					}
					else
					{
						m_listPlainFields_Color1.push_back(m_pMap[j][i]);
					}
					break;
			}//switch
			
			// after determining the type of field, it's time to determine it's "color"
			// (let the map look like a checkerfield)
			if ( (++color%2) == 0)
				m_pMap[j][i]->setTexture(FIELD_PLAIN0_TEXTURE);
			else
				m_pMap[j][i]->setTexture(FIELD_PLAIN1_TEXTURE);
				
			bColor0 = !bColor0;
			
		}// for j
	}// for i

	
	for (int i = 0; i < 4; i++)
		m_iBombsOnField[i] = 0;
	
	m_pItemThrower = new CItemThrower(this);
}

CMap::~CMap()
{
	cleanUp();
}

 
void  CMap::calculateDisplacement(CVector3 & vDisplacement)
{
	float angle;

	float x,y,z;

	//randomly choose an angle between minAngle - maxAngle;
	angle = rand()%(360);
	//convert deg -> rad
	angle = (angle*3.14159265/180);
	
	//caluclate intial values of the displacement vector
	x = cos (angle);
	y = sin (angle);
	z = 0;
	
	//rotate the point (x,z) araund the y axis by a random angle
	rotateAroundYAxis(x,z,rand()%360);
	
	vDisplacement.x = x;
	vDisplacement.y = y;
	vDisplacement.z = z;

}


void CMap::cleanUp()
{
	for ( int i = 0; i < 15; i++ )
		for ( int j = 0; j < 19; j++ )
		{			
			if ( m_pMap[j][i] != NULL)
				delete m_pMap[j][i];
		}
	
	if (m_bBombThrower)
		delete m_pBombThrower;
	
	delete m_pItemThrower;
	
	//delete all falling fields
	list<CField*>::iterator it;
	for (it = m_listFallingFields.begin(); it != m_listFallingFields.end();it++)
	{
		delete (*it);
	}
	
}

bool CMap::hasBomb( int x, int z )
{
    return m_pMap[x][z]->hasBomb();
}

bool CMap::hasItem( int x, int z )
{
	return m_pMap[x][z]->hasItem();
}

bool CMap::hasCrate( int x, int z )
{
    return m_pMap[x][z]->hasCrate();
}

bool CMap::hasPlayer( int x, int z )
{

	CPlayer * pPlayer;
	// loop throug all players and see if one is standing on specified field
	for (int i = 0; i < m_pGame->getPlayerCount(); i++)
	{
		pPlayer = m_pGame->getPlayer(i);
		if( (pPlayer->getXBlock() == x) && 
		    (pPlayer->getZBlock() == z) )
		{
			//only return true if player ist not dead
			if  (!(m_pGame->getPlayer(i))->isDead())
				return true;
		}
	}
	
	// if we reached here then there is no Player standing on field (x,z)
	return false;
}

/*
bool CMap::isBlock( int x, int z )
{
    return (m_pMap[x][z]->getType() == BLOCK);
}

bool CMap::isVoid( int x, int z )
{
    return (m_pMap[x][z]->getType() == VOID);	
}
*/

int CMap::getType(int x, int z)
{
	return (m_pMap[x][z]->getType());
}

bool CMap::isFree( int x, int z )
{
	return m_pMap[x][z]->isFree();
}



bool CMap::placeBomb(CBomb * bomb)
{
    return m_pMap[bomb->getXBlock()][bomb->getZBlock()]->placeBomb ( bomb );
}

void CMap::dispatchBomb( int x, int z )
{
    m_pMap[x][z]->dispatchBomb ();	
}

void CMap::placeItem( CItem * item)
{
	//don't let item wobble if it's placed on an void field
	if (m_pMap[item->getXBlock()][item->getZBlock()]->getType() == VOID)
		item->setWobble(false);
	else
		item->setWobble(true);

		
	 m_pMap[item->getXBlock()][item->getZBlock()]->placeItem ( item );
	 
}

void CMap::dispatchItem( int x, int z )
{
	m_pMap[x][z]->dispatchItem();	
}



void CMap::destroyBlock( int x, int z )
{
		m_pMap[x][z]->destroy();
}

CBomb * CMap::getBomb( int x, int z )
{
	return m_pMap[x][z]->getBomb();
}

CItem * CMap::getItem ( int x, int z)
{
	return m_pMap[x][z]->getItem();
}


int CMap::getPlayerStartPositionX(int nr)
{
	if ( nr < m_iPlayerCount)
		return m_StPlayerStartPos[nr].x; 
	else
		return 0;
}

int CMap::getPlayerStartPositionZ(int nr)
{
	if ( nr < m_iPlayerCount)
		return m_StPlayerStartPos[nr].z; 
	else
		return 0;
	
}

bool CMap::doesPlayerCollide( CPlayer *pPlayer, CVector3 &slideDirection, float &time  )
{
	CBoundingBox_2D * pFieldBBox;
	CBoundingBox_2D * pPlayerBBox = pPlayer->getBoundingBox();
	int block1[2];
	int block2[2];
	float dirX = 0;
	float dirZ = 0;
	int xBlockNext = pPlayer->getXBlock() + int(pPlayer->getDisplacement().x);
	int zBlockNext = pPlayer->getZBlock() + int(pPlayer->getDisplacement().z);
	
	CVector3 vVelocityVector = (pPlayer->getDisplacement()) * pPlayer->getVelocity();
	
	switch(pPlayer->getDirection())
	{
		case UP:
			block1[0] = (int)pPlayerBBox->m_vVertex_Worldspace[0].x;
			block1[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[0].z - 1);
			
			block2[0] = (int)pPlayerBBox->m_vVertex_Worldspace[1].x;
			block2[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[1].z - 1);
			dirX = 1;
			dirZ = 0;
			break;
		
		case DOWN:
			block1[0] = (int)pPlayerBBox->m_vVertex_Worldspace[2].x;
			block1[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[2].z + 1);
			
			block2[0] = (int)pPlayerBBox->m_vVertex_Worldspace[3].x;
			block2[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[3].z + 1);
			dirX = -1;
			dirZ = 0;
			break;
		
		case LEFT:
			block1[0] = (int)(pPlayerBBox->m_vVertex_Worldspace[0].x-1);
			block1[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[0].z);
			
			block2[0] = (int)(pPlayerBBox->m_vVertex_Worldspace[3].x-1);
			block2[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[3].z);	
			dirX = 0;
			dirZ = 1;
			break;

		case RIGHT:
			block1[0] = (int)(pPlayerBBox->m_vVertex_Worldspace[1].x+1);
			block1[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[1].z);
			
			block2[0] = (int)(pPlayerBBox->m_vVertex_Worldspace[2].x+1);
			block2[1] = (int)(pPlayerBBox->m_vVertex_Worldspace[2].z);	
			dirX = 0;
			dirZ = 1;
			break;
		default:
			return false;
			break;
	}
	
	if ( (xBlockNext >= 18) || (xBlockNext <= 0) ||
		 (zBlockNext <= 0) || (zBlockNext  >= 14)  )
		 return false;
		 		
	//get square Bounding Box
	pFieldBBox = m_pMap[block1[0]][block1[1]]->getBoundingBox();

	//check if square is free. if not:  do square & player BBox collide ?
	if (!m_pMap[block1[0]][block1[1]]->isFree() &&
		pFieldBBox->doesCollide(pPlayerBBox,vVelocityVector,time))
	{
		//check if we need to drag the players position
		if (m_pMap[xBlockNext][zBlockNext]->isFree())
		{
			slideDirection.x = dirX;
			slideDirection.z = dirZ;
		}
		
		if( (block1[0] == xBlockNext) && ( block1[1] == zBlockNext) )
		{
			if ( m_pMap[xBlockNext][zBlockNext]->hasBomb() && pPlayer->getKick())
				m_pMap[xBlockNext][zBlockNext]->kickBomb(pPlayer->getDirection());
		}

		return true;
	}

	pFieldBBox = m_pMap[block2[0]][block2[1]]->getBoundingBox();
	if (!m_pMap[block2[0]][block2[1]]->isFree() &&
		pFieldBBox->doesCollide(pPlayerBBox,vVelocityVector,time))
	{
		if ( m_pMap	[xBlockNext][zBlockNext]->isFree())
		{
			slideDirection.x = -1 * dirX;
			slideDirection.z = -1 * dirZ;		
		}
		
		if( (block2[0] == xBlockNext) && ( block2[1] == zBlockNext) )
		{
			if ( m_pMap[xBlockNext][zBlockNext]->hasBomb() && pPlayer->getKick())
				m_pMap[xBlockNext][zBlockNext]->kickBomb(pPlayer->getDirection());
		}

		return true;
	}
	
	return false;

}

bool CMap::doesBurn( CPlayer * player)
{
	return m_pMap[player->getXBlock()][player->getZBlock()]->isExploding();
}

bool CMap::doesBurn(int x, int z)
{
	return m_pMap[x][z]->isExploding();
}

void CMap::doShake()
{
	m_ShakeTimer.setAlarm(300);
}

void CMap::update()
{
	m_listBombFields.clear();
	m_listItemFields.clear();
	
	m_listCrateFields.clear();	
	m_listBlockFields.clear();

	m_listPlainFields_Color0.clear();
	m_listPlainFields_Color1.clear();

	m_listArrowFields_Color0.clear();
	m_listArrowFields_Color1.clear();
	
	m_listHoleFields_Color0.clear();
	m_listHoleFields_Color1.clear();

	m_listExplodingFields.clear();

	if (m_bBombThrower)
		m_pBombThrower->update(); 
	
	m_pItemThrower->update();
	m_ParticleManager.update();

	for ( int i = 0; i < 19; i++ )
		for ( int j = 0; j < 15; j++ )
		{
			m_pMap[i][j]->update();

		}
		

	bool bColor0 = true;
	for ( int i = 0; i < 19; i++ )
	{
		for ( int j = 0; j < 15; j++ )
		{
		
			m_pMap[i][j]->setColor(bColor0);	
			sortField(m_pMap[i][j]);
			bColor0 = !bColor0;
	
		}// for j
	}//for 

	//update all falling fields
	list<CField*>::iterator it;
	
	for (it = m_listFallingFields.begin(); it != m_listFallingFields.end();)
	{

		// did this field reach the bottom ?
		if ( ((*it)->getPosition()).y < -10 )
		{	

			//if so delete the CField object
			delete (*it);
			//erase this list entry
			m_listFallingFields.erase(it++);
		}
		else
		{
			(*it)->update();
			sortField(*it);
			++it;
		}

	}
	

}

void CMap::doDrop(int x, int z)
{

	// add the field to the list of falling fields...
	m_listFallingFields.push_back(m_pMap[x][z]);
	m_pMap[x][z]->setState(CField::FALLING);
	
	//...and replace it by a void field
	m_pMap[x][z] = new CField_Void(x, z, this); 
}

void CMap::addBombToThrower(CVector3 vStart,CBomb * pBomb)
{
	m_pBombThrower->add(vStart, pBomb);

}

void CMap::addItemToThrower(CVector3 vStart, CItem * pItem)
{
	m_pItemThrower->add(vStart, pItem);
}


void CMap::sortField(CField * pField)
{
	if  (pField->hasBomb())
		m_listBombFields.push_back(pField);
			
	if (pField->hasItem())
		m_listItemFields.push_back(pField);

	if (pField->isExploding())
		m_listExplodingFields.push_back(pField);

	switch(pField->getType())
	{
		case FIELD:
			if (pField->hasCrate())
				m_listCrateFields.push_back(pField);			
			else
			{
				if (pField->getColor())
					m_listPlainFields_Color0.push_back(pField);
				else
					m_listPlainFields_Color1.push_back(pField);
			}
			break;
		case BLOCK:
				m_listBlockFields.push_back(pField);
			break;
/*				case CRATE:
				m_listCrateFields.push_back(m_pMap[j][i]);			
			break;*/
		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			if (pField->getColor())
				m_listArrowFields_Color0.push_back(pField);
			else
				m_listArrowFields_Color1.push_back(pField);			
			break;
		case HOLE:
			if (pField->getColor())
				m_listHoleFields_Color0.push_back(pField);
			else
				m_listHoleFields_Color1.push_back(pField);			
			break;
		case VOID:
			break;
	}//switch

}



void CMap::drawExplosions()
{
/*

	list<CField*>::iterator it;
	for (it = m_listExplodingFields.begin(); it != m_listExplodingFields.end();it++)
	{
		(*it)->drawExplosion();
	}
*/
}




void  CMap::drawCrateFields()
{
	list<CField*>::iterator it;
	CApplication::m_pMeshManager->m_pCrateMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pCrateMesh->configureTexture0(CRATE_TEXTURE);
	CApplication::m_pMeshManager->m_pCrateMesh->configureTexCoord0();
	
	CApplication::m_pMeshManager->m_pCrateMesh->enableBuffers();
	
	for (it = m_listCrateFields.begin(); it != m_listCrateFields.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pCrateMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pCrateMesh->resetTextureEngines();
}

void  CMap::drawBlockFields()
{
	//draw all Blocks
	list<CField*>::iterator it;
	CApplication::m_pMeshManager->m_pBlockMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pBlockMesh->configureTexture0(BLOCK_TEXTURE);
	CApplication::m_pMeshManager->m_pBlockMesh->configureTexCoord0();
	
	CApplication::m_pMeshManager->m_pBlockMesh->enableBuffers();
	
	for (it = m_listBlockFields.begin(); it != m_listBlockFields.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pBlockMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pBlockMesh->resetTextureEngines();

}

void  CMap::drawPlainFields()
{
	list<CField*>::iterator it;
	//draw all fields in color0
	CApplication::m_pMeshManager->m_pSquareMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture0(FIELD_PLAIN0_TEXTURE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	CApplication::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listPlainFields_Color0.begin(); it != m_listPlainFields_Color0.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pSquareMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pSquareMesh->resetTextureEngines();

	CApplication::m_pMeshManager->m_pSquareMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture0(FIELD_PLAIN1_TEXTURE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	CApplication::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listPlainFields_Color1.begin(); it != m_listPlainFields_Color1.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pSquareMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pSquareMesh->resetTextureEngines();
}

void  CMap::drawArrowFields()
{
	list<CField*>::iterator it;
	CApplication::m_pMeshManager->m_pSquareMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture0(FIELD_PLAIN0_TEXTURE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture1(FIELD_ARROW);
	CApplication::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listArrowFields_Color0.begin(); it != m_listArrowFields_Color0.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pSquareMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pSquareMesh->resetTextureEngines();
	
	CApplication::m_pMeshManager->m_pSquareMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture0(FIELD_PLAIN1_TEXTURE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture1(FIELD_ARROW);
	CApplication::m_pMeshManager->m_pSquareMesh->enableBuffers();


	for (it = m_listArrowFields_Color1.begin(); it != m_listArrowFields_Color1.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pSquareMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pSquareMesh->resetTextureEngines();


}

void  CMap::drawHoleFields()
{

	list<CField*>::iterator it;
	CApplication::m_pMeshManager->m_pSquareMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture0(FIELD_PLAIN0_TEXTURE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture1(FIELD_HOLE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord1(0);
	CApplication::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listHoleFields_Color0.begin(); it != m_listHoleFields_Color0.end();it++)
	{
		(*it)->draw();
	}
	CApplication::m_pMeshManager->m_pSquareMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pSquareMesh->resetTextureEngines();

	CApplication::m_pMeshManager->m_pSquareMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture0(FIELD_PLAIN1_TEXTURE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexture1(FIELD_HOLE);
	CApplication::m_pMeshManager->m_pSquareMesh->configureTexCoord1(0);
	CApplication::m_pMeshManager->m_pSquareMesh->enableBuffers();
	for (it = m_listHoleFields_Color1.begin(); it != m_listHoleFields_Color1.end();it++)
	{
		(*it)->draw();
	}

	CApplication::m_pMeshManager->m_pSquareMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pSquareMesh->resetTextureEngines();

}

void CMap::drawBombs()
{
	list<CField*>::iterator it;

	//draw all bombs
	CApplication::m_pMeshManager->m_pBombMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pBombMesh->configureTexture0(BOMB_TEXTURE);
	CApplication::m_pMeshManager->m_pBombMesh->configureTexCoord0();
	CApplication::m_pMeshManager->m_pBombMesh->enableBuffers();
	for (it = m_listBombFields.begin(); it != m_listBombFields.end();it++)
	{
		(*it)->drawBombs();

	}

	if (m_bBombThrower)
		m_pBombThrower->draw(); 

	CApplication::m_pMeshManager->m_pBombMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pBombMesh->resetTextureEngines();



}

void CMap::drawItems()
{

	list<CField*>::iterator it;

	//draw all items
	CApplication::m_pMeshManager->m_pItemMesh->configureMaterial();
	CApplication::m_pMeshManager->m_pItemMesh->configureTexCoord0();
	CApplication::m_pMeshManager->m_pItemMesh->enableBuffers();
	for (it = m_listItemFields.begin(); it != m_listItemFields.end();it++)
	{
		if ((*it)->hasItem())
		{
			CItem * pItem = (*it)->getItem();
			pItem->draw();
		}	

	}
	m_pItemThrower->draw();

	CApplication::m_pMeshManager->m_pItemMesh->disableBuffers();
	CApplication::m_pMeshManager->m_pItemMesh->resetTextureEngines();


}

void CMap::draw()
{
	if (m_ShakeTimer.isTimeUp())
	{
		m_vDisplacement.x = 0;
		m_vDisplacement.y = 0;
		m_vDisplacement.z = 0;
	}
	else
	{
		//shake it, baby !
		calculateDisplacement(m_vDisplacement);
		m_vDisplacement = m_vDisplacement * 0.1;
	}
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glPushMatrix();
		if (!m_pGame->isPaused())
			glTranslatef(m_vDisplacement.x,m_vDisplacement.y,m_vDisplacement.z);

		drawCrateFields();	
		drawBlockFields();
		drawPlainFields();
		drawArrowFields();	
		drawHoleFields();

		drawBombs();
		drawItems();

		drawExplosions();
		m_ParticleManager.draw();
	glPopMatrix();

}



