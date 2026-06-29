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

#include "Player.h"
#include "Item.h"
#include "Item_BombUp.h"
#include "Item_PowerUp.h"
#include "Item_SpeedUp.h"
#include "Item_EnableKick.h"
#include "Item_Joint.h"
#include "Item_Cocaine.h"
#include "Item_Viagra.h"
#include "Item_Condom.h"

#include "ItemManager.h"
#include "../Engine/MeshManager.h"
#include "../Engine/SoundManager.h"
#include "../Engine/Wobbler.h"
#include "../Engine/Timer.h"

#include "../MeshObjects/PlayerMesh.h"

#include "../Application.h"
#include "../Gametypes/Game.h"
#include "../Config.h"
#include "../Defines.h"

Player::Player(int id, Map *pField, int xBlock, int zBlock)
	: Object_Moving(xBlock, zBlock, 0.6f)
{
	m_iType = PLAYER_OBJECT;

	m_cName = NULL;

	m_pField = pField;

	m_bKickBomb = Application::m_pConfig->getStartKick();
	m_iBombCount = Application::m_pConfig->getStartBombs();
	m_iBombStrength = Application::m_pConfig->getStartPower();

	m_iSpeed = Application::m_pConfig->getStartSpeed();
	m_fVelocity = 1.0 + (Application::m_pConfig->getVelocityStepping() *
			     m_iSpeed);
	m_iDirection = NONE;
	m_fOrientation = 0;
	m_fOrientationCurrent = 0;

	m_iID = id;
	m_pItem = NULL;
	m_pItemManager = new ItemManager(this);

	m_pWobbler->setRadSpeeds(10, 10, 10);

	m_iPrimaryTexture = PLAYER1_TEXTURE;
	m_iSecondaryTexture = PLAYER_HAPPY_TEXTURE;

	m_bCanBomb = true;
	m_iState = ALIVE;

	m_iTicks = 0;
	m_bDoSmoke = false;
}

Player::~Player()
{
	if (m_pItem != NULL)
		delete m_pItem;

	delete m_pItemManager;
}

void Player::attachController(Controller *pController)
{
	m_pController = pController;
}

void Player::placeBomb()
{
	// Only place bomb if player is allowed	to
	if ((Map::m_iBombsOnField[m_iID] < m_iBombCount) && (m_bCanBomb)) {
		// Bomb has been succesfully planted
		if (m_pField->placeBomb(new Bomb(m_xBlock, m_zBlock, m_iID,
						 m_iBombStrength)) == true) {
			Map::m_iBombsOnField[m_iID]++;
			Application::m_pSoundManager->playSoundFX(
				PUTBOMB_SOUND);
		}
	}
}

//Called once when the player got "burned"by a bomb for the first time
void Player::doDie()
{
	// it's dead, jim...
	m_iState = DEADBYBOMB;

	//let the player face in a random direction
	m_fOrientation = rand() % 360;

	// Put some Items into the ItemThrowerList
	// calulate the amount of items this player picked up
	int iBombUpItemCount =
		m_iBombCount - Application::m_pConfig->getStartBombs();
	int iPowerUpItemCount =
		m_iBombStrength - Application::m_pConfig->getStartPower();
	int iSpeedUpItemCount =
		m_iSpeed - Application::m_pConfig->getStartSpeed();

	// ----- add some Goodies

	//BombUpItems.
	for (int i = 0; i < int(iBombUpItemCount / 2); i++)
		m_pField->addItemToThrower(m_vPos,
					   new Item_BombUp(m_xBlock, m_zBlock));

	// PowerUpItems
	for (int i = 0; i < int(iPowerUpItemCount / 2); i++)
		m_pField->addItemToThrower(m_vPos, new Item_PowerUp(m_xBlock,
								    m_zBlock));

	// SpeedUpItems
	for (int i = 0; i < int(iSpeedUpItemCount / 2); i++)
		m_pField->addItemToThrower(m_vPos, new Item_SpeedUp(m_xBlock,
								    m_zBlock));

	// enableKick Item
	if ((m_bKickBomb) && (!Application::m_pConfig->getStartKick()))
		m_pField->addItemToThrower(
			m_vPos, new Item_EnableKick(m_xBlock, m_zBlock));

	// ----- add all Badies, which affected the player until his tragic death...
	if (m_pItemManager->hasItem(JOINT))
		m_pField->addItemToThrower(m_vPos,
					   new Item_Joint(m_xBlock, m_zBlock));

	if (m_pItemManager->hasItem(COCAINE))
		m_pField->addItemToThrower(m_vPos, new Item_Cocaine(m_xBlock,
								    m_zBlock));

	if (m_pItemManager->hasItem(VIAGRA))
		m_pField->addItemToThrower(m_vPos,
					   new Item_Viagra(m_xBlock, m_zBlock));

	if (m_pItemManager->hasItem(CONDOM))
		m_pField->addItemToThrower(m_vPos,
					   new Item_Condom(m_xBlock, m_zBlock));

	// ----- player got fragged by a bomb *sad panda*
	m_iSecondaryTexture = PLAYER_FRAGGED_TEXTURE;

	m_tTimer.setAlarm(500);
}

void Player::handleInput()
{
	// Set direction based on controller input
	if (m_pController->isDownHold()) {
		setDirection(DOWN);
	} else if (m_pController->isUpHold()) {
		setDirection(UP);

	} else if (m_pController->isLeftHold()) {
		setDirection(LEFT);
	} else if (m_pController->isRightHold()) {
		setDirection(RIGHT);
	} else {
		setDirection(NONE);
	}

	if (m_pController->isBombPressed())
		placeBomb();

	if (m_pController->isBackPressed())
		Application::m_pGame->abort();
}

void Player::move()
{
	// Only check for the field in front of the players *center* for an item
	// if player ist not moving we check for an item on the current field (could have gotten there by air)

	Item *pItem = m_pField->getItem(int(m_xBlock + m_vDisplacement.x),
					int(m_zBlock + m_vDisplacement.z));
	if (pItem != NULL) {
		float blah;
		bool bItemCollision = false;

		if (m_iDirection == NONE)
			bItemCollision = true;
		else {
			BoundingBox_2D *pBBox = pItem->getBoundingBox();
			bItemCollision = pBBox->doesCollide(
				m_pBBox, (m_vDisplacement * m_fVelocity), blah);
		}

		if (bItemCollision) {
			m_pItemManager->addItem(pItem);
			m_pField->dispatchItem(
				int(m_xBlock + m_vDisplacement.x),
				int(m_zBlock + m_vDisplacement.z));
		}
	}

	glm::vec3 slideDirection;
	float time = 0;
	if (!m_pField->doesPlayerCollide(this, slideDirection, time)) {
		glm::vec3 vMovement =
			m_vDisplacement *
			(m_fVelocity * Application::m_fReciprocalFPS);
		m_vPos = m_vPos + vMovement;
	} else {
		//needed to prevent player from sliding back and forth when an cocaine item ist active
		float slideVelocity = m_fVelocity;
		if (m_pItemManager->hasItem(COCAINE))
			slideVelocity = m_fVelocity / 2;

		// slide into the right direction if needed
		glm::vec3 vMovement =
			slideDirection *
			(slideVelocity * Application::m_fReciprocalFPS);
		m_vPos = m_vPos + vMovement;

		//check if we need to reposition the player closer at the obstacle (usefull at high speeds)
		if ((m_fVelocity * Application::m_fReciprocalFPS * time) >=
		    0.1) {
			// - 0.0001 to avoid walking through walls
			m_vPos = m_vPos + (m_vDisplacement *
					   ((time * m_fVelocity *
					     Application::m_fReciprocalFPS) -
					    0.001f));
		}
	}

	// Update the grid coordinates
	m_xBlock = int(m_vPos.x);
	m_zBlock = int(m_vPos.z);
	m_pBBox->update(m_vPos);

	setDirection(NONE);
}
void Player::setStartPosition(int x, int z)
{
	m_xBlock = x;
	m_zBlock = z;
	m_vPos.x = m_xBlock + 0.5f;
	m_vPos.z = m_zBlock + 0.5f;
	m_pBBox->update(m_vPos);
}

void Player::setName(const char *name)
{
	m_cName = name;
}

void Player::setPrimaryTexture(int skin)
{
	m_iPrimaryTexture = skin;
	switch (m_iPrimaryTexture) {
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

int Player::getBombStrength()
{
	return m_iBombStrength;
}

bool Player::isDead()
{
	if ((m_iState == DEADBYBOMB) || (m_iState == REALLYDEAD) ||
	    (m_iState == FALLING))
		return true;
	else
		return false;
}

void Player::update()
{
	switch (m_iState) {
	case REALLYDEAD:
		break;

	case DEADBYBOMB:
		m_iTicks++;
		if ((m_iTicks % 10) == 0)
			m_pField->m_ParticleManager.addPlayerSmokeParticle(
				m_vPos, 1);

		// if player is bombed again, let him finally vanish
		// timer is used to ensure that doesBurn() doesn't return true because of the same bomb, which killed the player
		if ((m_pField->doesBurn(this)) && (m_tTimer.isTimeUp())) {
			m_iState = REALLYDEAD;
		}

		// the tile on which the player stood smoking could have been destroyed
		if (m_pField->getType(m_xBlock, m_zBlock) == VOID) {
			m_iState = FALLING;
		}

		break;

	case ALIVE:

		// check if the player has stepped on a void Field
		if (m_pField->getType(m_xBlock, m_zBlock) == VOID) {
			//if so, let him drop !
			m_iState = FALLING;

			// step out of this fuction
			return;
		}

		//ok, player is alive and kicking
		handleInput();

		// determine if the player died :-(
		if (m_pField->doesBurn(this))
			doDie();

		m_pItemManager->update();
		move();

		if (m_bWobble)
			m_pWobbler->update();

		checkPlayerPlayerCollisions();
		break;

	case FALLING:
		if (m_vPos.y > -10) {
			m_vPos.y -= (4 * Application::m_fReciprocalFPS);
		}

		else {
			m_iState = REALLYDEAD;
		}
		break;
		break;

	default:
		break;

	} //switch
}

void Player::checkPlayerPlayerCollisions()
{
	Player *pPlayer = NULL;
	int distance = 0;

	float tmp;
	bool bCollision = false;
	for (int i = 0; i < Application::m_pGame->getPlayerCount(); i++) {
		//only check collisions with other players
		if (i == m_iID)
			continue;

		pPlayer = Application::m_pGame->getPlayer(i);

		//only check with nearby Player and players that are alive

		//... therefore we calculate the manhatan distance
		distance = (SDL_abs(m_xBlock - pPlayer->getXBlock())) +
			   (SDL_abs(m_zBlock - pPlayer->getZBlock()));

		// if pPlayer is too far away or dead abort
		if ((distance > 1) || (pPlayer->isDead()))
			continue;

		BoundingBox_2D *pBBox = pPlayer->getBoundingBox();

		//check for collision. 	consider pPlayer always as fixed
		if (m_iDirection == NONE)
			bCollision = m_pBBox->doesCollideWith(pBBox);
		else {
			glm::vec3 vVelocityVector =
				(m_vDisplacement)*m_fVelocity;
			bCollision = pBBox->doesCollide(m_pBBox,
							vVelocityVector, tmp);
		}

		//"infect" the other player, if there was an collision
		if (bCollision)
			m_pItemManager->infect(pPlayer->getItemManager());
	}
}

void Player::drawPlayer()
{
	glPushMatrix();

	glTranslatef(m_vPos.x, m_vPos.y - 0.5f, m_vPos.z);
	glRotatef(m_fOrientation, 0, 1, 0);

	if (m_bWobble)
		glScalef(m_pWobbler->getScaleValueX(),
			 m_pWobbler->getScaleValueY(),
			 m_pWobbler->getScaleValueZ());

	Application::m_pMeshManager->m_pPlayerMesh->configureTexture0(
		m_iPrimaryTexture);
	Application::m_pMeshManager->m_pPlayerMesh->configureTexture1(
		m_iSecondaryTexture);

	Application::m_pMeshManager->m_pPlayerMesh->drawVBO();

	glPopMatrix();
}

void Player::draw()
{
	switch (m_iState) {
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
