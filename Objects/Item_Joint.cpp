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

#include "Item_Joint.h"
#include "Player.h"
#include "../Defines.h"

Item_Joint::Item_Joint(int xBlock, int zBlock)
	: Item(xBlock, zBlock)
{
	m_iType = JOINT;
	m_iTexture = BADIE_JOINT_TEXTURE;

	m_bActive = false;
	m_pPlayer = NULL;
}

Item_Joint::~Item_Joint()
{
	// If this item is affecting a player, m_pPlayer->m_bWobble is set to true.
	// We need to set it to false if item gets deleted
	if (m_pPlayer != NULL)
		m_pPlayer->m_bWobble = false;
}

bool Item_Joint::affectPlayer(Player *player)
{
	// start des Timers beim ersten Aufruf
	if (!m_bActive) {
		m_pPlayer = player;
		m_bActive = true;
		m_tDuration.setAlarm(5000);
	}

	// Wirkungsdauer Ende ?
	if (m_tDuration.isTimeUp()) {
		player->m_bWobble = false;
		return true;
	} else {
		switch (player->m_iDirection) {
		case LEFT:
			player->setDirection(RIGHT);
			break;
		case RIGHT:
			player->setDirection(LEFT);
			break;
		case UP:
			player->setDirection(DOWN);
			break;
		case DOWN:
			player->setDirection(UP);
			break;
		default:
			break;
		}
		// it's an badie item, so make the player wobble
		player->m_bWobble = true;

		return false;
	}
}