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

#include "Item_Cocaine.h"
#include "Player.h"
#include "../Application.h"
#include "../Config.h"

Item_Cocaine::Item_Cocaine(int xBlock, int zBlock)
	: Item(xBlock, zBlock)
{
	m_iType = COCAINE;
	m_iTexture = BADIE_COCAINE_TEXTURE;

	m_bActive = false;
	m_pPlayer = NULL;
}

Item_Cocaine::~Item_Cocaine()
{
	// reset the velocity Modifier (only if this Cocaine Badie is in use)
	if (m_pPlayer != NULL) {
		m_pPlayer->m_bWobble = false;
		//recalculate speed:
		m_pPlayer->m_fVelocity =
			1 + (Application::m_pConfig->getVelocityStepping() *
			     m_pPlayer->m_iSpeed);
	}
}

bool Item_Cocaine::affectPlayer(Player *player)
{
	// start des Timers beim ersten Aufruf
	if (!m_bActive) {
		m_pPlayer = player;
		m_bActive = true;
		player->m_fVelocity = 20;
		player->m_bWobble = true;
		m_tDuration.setAlarm(5000);
	}

	// Wirkungsdauer Ende ?
	if (m_tDuration.isTimeUp()) {
		player->m_bWobble = false;
		//recalculate speed:
		player->m_fVelocity =
			1 + (Application::m_pConfig->getVelocityStepping() *
			     player->m_iSpeed);
		return true;
	} else {
		// it's an badie item, so make the player wobble

		player->m_fVelocity = 20;
		return false;
	}
}
