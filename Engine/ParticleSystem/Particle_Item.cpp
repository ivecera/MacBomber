/*
 *  Particle_Item.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "../../Application.h"
#include "ParticleManager.h"
#include "Particle_Item.h"
#include "../../Defines.h"

Particle_Item::Particle_Item(glm::vec3 vPos, ParticleManager *pParticleManager,
			     int itemType)
	: Particle(vPos)
{
	//check Item Type and set Color/Texture accordingly
	if ((itemType == SPEEDUP) || (itemType == POWERUP) ||
	    (itemType == BOMBUP) || (itemType == ENABLEKICK)) {
		m_fColor[0] = 0;
		m_fColor[1] = 0;
		m_fColor[2] = 1;
		m_fColor[3] = 0.5;
		m_iTextureIndex = PARTICLE_GOODIE_TEXTURE;
	} else {
		m_fColor[0] = 1;
		m_fColor[1] = 0;
		m_fColor[2] = 0;
		m_fColor[3] = 0.5;
		m_iTextureIndex = PARTICLE_BADIE_TEXTURE;
	}

	m_iTTL = 40;
	m_fScaleFactor = 0.1;
	m_fVelocity = 15 + rand() % 6;
	m_vDisplacement.y = 1;
	m_pParticleManager = pParticleManager;

	m_bSpawnTrailParticle = true;
}

void Particle_Item::update()
{
	m_iTTL--;
	if (m_iTTL < 20)
		m_fColor[3] -= 0.05;
	move();
	m_vDisplacement.y -= (2 * Application::m_fReciprocalFPS);
	updateBillboardMatrix();

	Particle *pParticle = new Particle(m_vPosition);
	pParticle->m_iTTL = 20;
	pParticle->m_fScaleFactor = 1;
	pParticle->m_fVelocity = 0;
	pParticle->m_iTextureIndex = m_iTextureIndex;

	pParticle->m_fColor[0] = m_fColor[0];
	pParticle->m_fColor[1] = m_fColor[1];
	pParticle->m_fColor[2] = m_fColor[2];
	pParticle->m_fColor[3] = m_fColor[3];

	m_pParticleManager->m_listParticles.push_back(pParticle);

	m_bSpawnTrailParticle = !m_bSpawnTrailParticle;
}
