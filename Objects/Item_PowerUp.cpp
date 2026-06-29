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

#include "Item_PowerUp.h"
#include "Player.h"

#include "../Application.h"
#include "../Config.h"

Item_PowerUp::Item_PowerUp(int xBlock, int zBlock)
	: Item(xBlock, zBlock)
{
	m_iType = POWERUP;
	m_iTexture = GOODIE_POWERUP_TEXTURE;
}

bool Item_PowerUp::affectPlayer(Player *player)
{
	// only affect player if it doesn't exceed Limit
	if (player->m_iBombStrength <
	    (Application::m_pConfig->getStartPower() +
	     Application::m_pConfig->getExtraPower())) {
		player->m_iBombStrength++;
	}
	return true;
}
