/*
 *  Item_Condom.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 28.07.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Item_Condom.h"
#include "Player.h"

Item_Condom::Item_Condom(int xBlock, int zBlock)
	: Item(xBlock, zBlock)
{
	m_iType = CONDOM;
	m_iTexture = BADIE_CONDOM_TEXTURE;

	m_bActive = false;
	m_pPlayer = NULL;
}

Item_Condom::~Item_Condom()
{
	// If this item is affecting a player, m_pPlayer->m_bWobble is set to true.
	// We need to set it to false if item gets deleted
	if (m_pPlayer != NULL) {
		m_pPlayer->m_bWobble = false;
		m_pPlayer->m_bCanBomb = true;
	}
}

bool Item_Condom::affectPlayer(Player *player)
{
	// start des Timers beim ersten Aufruf
	if (!m_bActive) {
		m_pPlayer = player;
		m_bActive = true;
		m_tDuration.setAlarm(5000);
	}

	// Wirkungsdauer Ende ?
	if (m_tDuration.isTimeUp()) {
		player->m_bCanBomb = true;
		player->m_bWobble = false;

		return true;
	} else {
		// it's an badie item, so make the player wobble
		player->m_bWobble = true;
		player->m_bCanBomb = false;

		return false;
	}
}
