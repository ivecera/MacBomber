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

#include "CPlayer.h"
#include "CItem.h"
#include "CItem_BombUp.h"
#include "CItem_PowerUp.h"
#include "CItem_SpeedUp.h"
#include "CItem_EnableKick.h"
#include "CItem_Joint.h"
#include "CItem_Cocaine.h"
#include "CItem_Viagra.h"
#include "CItem_Condom.h"

#include "CItemManager.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CSoundManager.h"
#include "../Engine/CWobbler.h"
#include "../Engine/CTimer.h"

#include "../MeshObjects/CPlayerMesh.h"

#include "../CApplication.h"
#include "../Gametypes/CGame.h"
#include "../CConfig.h"
#include "../Defines.h"



CPlayer::CPlayer( int id, CMap * pField, int xBlock, int zBlock ) : CObject_Moving( xBlock, zBlock, 0.6f )
{
	m_iType = PLAYER_OBJECT;
	
	m_cName = NULL;

    m_pField = pField;
	
	m_bKickBomb		=	CApplication::m_pConfig->getStartKick();
	m_iBombCount	=	CApplication::m_pConfig->getStartBombs();
    m_iBombStrength =	CApplication::m_pConfig->getStartPower();
   
	m_iSpeed		=	CApplication::m_pConfig->getStartSpeed();	
	m_fVelocity = 1.0 + (CApplication::m_pConfig->getVelocityStepping() * m_iSpeed);
	m_iDirection = NONE;
    m_fOrientation = 0;
	m_fOrientationCurrent = 0;
		
	m_iID = id;
	m_pItem = NULL;
	m_pItemManager = new CItemManager(this);

	m_pWobbler->setRadSpeeds(10,10,10);

	m_iPrimaryTexture	= PLAYER1_TEXTURE;
	m_iSecondaryTexture	= PLAYER_HAPPY_TEXTURE;

	m_bCanBomb = true;
	m_iState = ALIVE;

	m_iTicks = 0;
	m_bDoSmoke = false;
}

CPlayer::~CPlayer()
{
	if (m_pItem != NULL )
		delete m_pItem;
	
	delete m_pItemManager;

	
}

void CPlayer::attachController( CController * pController)
{
	m_pController = pController;
}


void CPlayer::placeBomb()
{
	// Only place bomb if player is allowed	to
	if ( ( CMap::m_iBombsOnField[m_iID] < m_iBombCount) && (m_bCanBomb) )
	{
		// Bomb has been succesfully planted
		if ( m_pField->placeBomb( new CBomb(m_xBlock,m_zBlock,m_iID,m_iBombStrength)) == true )
		{
			CMap::m_iBombsOnField[m_iID]++;
			CApplication::m_pSoundManager->playSoundFX(PUTBOMB_SOUND);
		}
	}
}


//Called once when the player got "burned"by a bomb for the first time
void CPlayer::doDie()
{	
	// it's dead, jim...
	m_iState = DEADBYBOMB;

	//let the player face in a random direction
	m_fOrientation = rand()%360;

	// Put some Items into the CItemThrowerList	
	// calulate the amount of items this player picked up 
	int iBombUpItemCount = m_iBombCount - CApplication::m_pConfig->getStartBombs();
	int iPowerUpItemCount = m_iBombStrength - CApplication::m_pConfig->getStartPower();
	int iSpeedUpItemCount = m_iSpeed - CApplication::m_pConfig->getStartSpeed();
	
	
	// ----- add some Goodies 
	
	//BombUpItems. 
	for ( int i = 0; i < int(iBombUpItemCount/2); i++)
		m_pField->addItemToThrower( m_vPos, new CItem_BombUp(m_xBlock, m_zBlock) );
	
	// PowerUpItems
	for ( int i = 0; i < int(iPowerUpItemCount/2); i++)
		m_pField->addItemToThrower( m_vPos, new CItem_PowerUp(m_xBlock, m_zBlock) );
	
	
	// SpeedUpItems
	for ( int i = 0; i < int(iSpeedUpItemCount/2); i++)
		m_pField->addItemToThrower( m_vPos, new CItem_SpeedUp(m_xBlock, m_zBlock) );
	
	// enableKick Item
	if ( (m_bKickBomb) && (!CApplication::m_pConfig->getStartKick()) )
		m_pField->addItemToThrower( m_vPos, new CItem_EnableKick(m_xBlock, m_zBlock) );
	
	// ----- add all Badies, which affected the player until his tragic death... 
	if (m_pItemManager->hasItem(JOINT))
		m_pField->addItemToThrower( m_vPos, new CItem_Joint(m_xBlock, m_zBlock) );

	if (m_pItemManager->hasItem(COCAINE))
		m_pField->addItemToThrower( m_vPos, new CItem_Cocaine(m_xBlock, m_zBlock) );

	if (m_pItemManager->hasItem(VIAGRA))
		m_pField->addItemToThrower( m_vPos, new CItem_Viagra(m_xBlock, m_zBlock) );

	if (m_pItemManager->hasItem(CONDOM))
		m_pField->addItemToThrower( m_vPos, new CItem_Condom(m_xBlock, m_zBlock) );

	
	
	// ----- player got fragged by a bomb *sad panda*
	m_iSecondaryTexture = PLAYER_FRAGGED_TEXTURE;

	m_tTimer.setAlarm(500);
}

void CPlayer::handleInput()
{
	
	// Richtung in Abh. vom Controller setzen
	if (m_pController->isDownHold() )
	{
		setDirection(DOWN);
	}else if (m_pController->isUpHold() )
	{
		setDirection(UP);	
		
	}else if (m_pController->isLeftHold() )
	{
		setDirection(LEFT);		
	}else if (m_pController->isRightHold() )
	{
		setDirection(RIGHT);
	}
	else
	{
		setDirection(NONE);
	}
	
	if (m_pController->isBombPressed() )
		placeBomb();
	
	if (m_pController->isBackPressed() )
		CApplication::m_pGame->abort();
	

	
}


void CPlayer::move()
{
	
	
	// Only check for the field in front of the players *center* for an item
	// if player ist not moving we check for an item on the current field (could have gotten there by air)	

	CItem * pItem = m_pField->getItem(int (m_xBlock + m_vDisplacement.x),int (m_zBlock + m_vDisplacement.z));
	if( pItem != NULL)
	{
		float blah;
		bool bItemCollision = false;

		if (m_iDirection == NONE)
			bItemCollision = true;
		else
		{	
			CBoundingBox_2D * pBBox = pItem->getBoundingBox();
			bItemCollision = pBBox->doesCollide(m_pBBox,(m_vDisplacement*m_fVelocity),blah);
		}

		if (bItemCollision)
		{
			m_pItemManager->addItem(pItem);
			m_pField->dispatchItem(int (m_xBlock + m_vDisplacement.x),int (m_zBlock + m_vDisplacement.z));			
		}	
	}

	CVector3 slideDirection;
	float time = 0;
	if (!m_pField->doesPlayerCollide(this,slideDirection,time))
	{
		CVector3 vMovement = m_vDisplacement * ( m_fVelocity *CApplication::m_fReciprocalFPS);
		m_vPos = m_vPos + vMovement;
	}	
	else
	{
		//needed to prevent player from sliding back and forth when an cocaine item ist active
		float slideVelocity = m_fVelocity;
		if (m_pItemManager->hasItem(COCAINE))
			slideVelocity = m_fVelocity/2;
			
		// slide into the right direction if needed
		CVector3 vMovement = slideDirection * ( slideVelocity *CApplication::m_fReciprocalFPS);
		m_vPos = m_vPos + vMovement;

		//check if we need to reposition the player closer at the obstacle (usefull at high speeds)
		if ((m_fVelocity * CApplication::m_fReciprocalFPS * time) >= 0.1)
		{
			// - 0.0001 to avoid walking through walls
			m_vPos = m_vPos + (m_vDisplacement* ((time*m_fVelocity * CApplication::m_fReciprocalFPS)-0.001));
		}
		
	}
	
	
	
	// aktualisiere die Gird Koordinaten
	m_xBlock = int ( m_vPos.x );
	m_zBlock = int ( m_vPos.z );
	m_pBBox->update(m_vPos);

	setDirection(NONE);
	
}
void CPlayer::setStartPosition(int x, int z)
{
	m_xBlock = x;
	m_zBlock = z;
	m_vPos.x = m_xBlock + 0.5f;
    m_vPos.z = m_zBlock + 0.5f;
	m_pBBox->update(m_vPos);

}

void CPlayer::setName(char * name)
{
	m_cName = name;
}


void CPlayer::setPrimaryTexture(int skin)
{
	m_iPrimaryTexture = skin;
	switch(m_iPrimaryTexture)
	{
		case PLAYER1_TEXTURE:
			m_cName = "RedMac";
			break;
		case PLAYER2_TEXTURE:
			m_cName = "BrownMac";
			break;
		case PLAYER3_TEXTURE:
			m_cName = "BlueMac";
			break;
		case PLAYER4_TEXTURE:
			m_cName = "WhiteMac";
			break;
		default:
			m_cName = "Unknown";			
			
	}
}

int CPlayer::getBombStrength()
{
    return m_iBombStrength;
}

bool CPlayer::isDead()
{
	if ( (m_iState == DEADBYBOMB) || (m_iState == REALLYDEAD) ||
		(m_iState == FALLING) )
		return true;
	else 
		return false;
}

void CPlayer::update()
{
	
	switch (m_iState)
	{
		case REALLYDEAD:
			break;
			
		case DEADBYBOMB:
			m_iTicks++;
			if ((m_iTicks%10) == 0)
				m_pField->m_ParticleManager.addPlayerSmokeParticle(m_vPos,1);

			// if player is bombed again, let him finally vanish
			// timer is used to ensure that doesBurn() doesn't return true because of the same bomb, which killed the player
			if  ( ( m_pField->doesBurn(this))  && (m_tTimer.isTimeUp()) )
			{
				m_iState = REALLYDEAD;
			}
				
			// the tile on which the player stood smoking could have been destroyed
			if ( m_pField->getType(m_xBlock,m_zBlock) == VOID)
			{
				m_iState = FALLING;

			}
					
				
			break;
			
		case ALIVE:
				
			// check if the player has stepped on a void Field
			if ( m_pField->getType(m_xBlock,m_zBlock) == VOID)
			{
				//if so, let him drop !
				m_iState = FALLING;

				// step out of this fuction
				return;
			}
			
			//ok, player is alive and kicking
			handleInput();
				
			// determine if the player died :-(
			if ( m_pField->doesBurn(this)) 
				doDie();

			
			m_pItemManager->update();
			move();
			
			if (m_bWobble)
				m_pWobbler->update();
				
			checkPlayerPlayerCollisions();
			break;
		
		case FALLING:
			if  (m_vPos.y > -10)
			{
				m_vPos.y -= (4 * CApplication::m_fReciprocalFPS);
			}
			
			else
			{
				m_iState = REALLYDEAD;
			}
			break;
			break;
			
		default:
			break;

	}//switch
}

void CPlayer::checkPlayerPlayerCollisions()
{
	CPlayer *pPlayer = NULL;
	int distance = 0;
	
	float tmp;
	bool bCollision = false;
	for (int i=0; i < CApplication::m_pGame->getPlayerCount(); i++)
	{
		//only check collisions with other players
		if (i == m_iID)
			continue;
		
		pPlayer = CApplication::m_pGame->getPlayer(i);

		//only check with nearby Player and players that are alive
		
		//... therefore we calculate the manhatan distance 
		distance =	(abs (m_xBlock - pPlayer->getXBlock())) + 
					(abs (m_zBlock - pPlayer->getZBlock()));
		
		// if pPlayer is too far away or dead abort
		if ( (distance > 1) || (pPlayer->isDead()))
			continue;
		
		CBoundingBox_2D * pBBox = pPlayer->getBoundingBox();

		//check for collision. 	consider pPlayer always as fixed
		if (m_iDirection == NONE)
			bCollision = m_pBBox->doesCollideWith(pBBox);
		else
		{
			CVector3 vVelocityVector = (m_vDisplacement) * m_fVelocity;
			bCollision = pBBox->doesCollide(m_pBBox,vVelocityVector,tmp);
		}
		
		//"infect" the other player, if there was an collision 
		if (bCollision)
			m_pItemManager->infect(pPlayer->getItemManager());
		
		
	}
	
}


void CPlayer::drawPlayer()
{

	glPushMatrix();
	
	glTranslatef(m_vPos.x, m_vPos.y - 0.5f,m_vPos.z);
	glRotatef(m_fOrientation, 0, 1, 0);

	
	if (m_bWobble)
		glScalef(m_pWobbler->getScaleValueX(),m_pWobbler->getScaleValueY(),m_pWobbler->getScaleValueZ());

	CApplication::m_pMeshManager->m_pPlayerMesh->configureTexture0(m_iPrimaryTexture);
	CApplication::m_pMeshManager->m_pPlayerMesh->configureTexture1(m_iSecondaryTexture);

	CApplication::m_pMeshManager->m_pPlayerMesh->drawVBO();

	glPopMatrix();

	
}


void CPlayer::draw()
{

	switch(m_iState)
	{
		case ALIVE:
		case DEADBYBOMB:
		case FALLING:
			drawPlayer();
			break;
		case REALLYDEAD:
		default:
			break;
				
	}
	
	
}
