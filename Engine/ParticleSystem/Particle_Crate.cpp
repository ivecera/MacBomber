/*
 *  Particle_Crate.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "../../Application.h"
#include "ParticleManager.h"
#include "Particle_Crate.h"
#include "Particle_SmokeTrail.h"
#include "../../Defines.h"
#include "../Billboard.h"
#include "../TextureManager.h"

Particle_Crate::Particle_Crate(glm::vec3 vPos,
			       ParticleManager *pParticleManager)
	: Particle(vPos)
{
	m_iTTL = 40;
	m_fScaleFactor = 0.8;
	m_fVelocity = 5 + SDL_rand(6);
	m_vDisplacement.y = 1;
	m_pParticleManager = pParticleManager;
	m_iTextureIndex = PARTICLE_CRATE_TEXTURE;

	m_fAngleX = SDL_rand(360);
	m_fAngleY = SDL_rand(360);
	m_fAngleZ = SDL_rand(360);

	float rnd = ((float)(SDL_rand(3))) / 10;
	m_fColor[0] = 0.8 + rnd;
	m_fColor[1] = 0.8 + rnd;
	m_fColor[2] = 0.8 + rnd;
	m_fColor[3] = 1;

	m_bSpawnTrailParticle = false;
}

void Particle_Crate::update()
{
	m_iTTL--;
	if (m_iTTL < 10)
		m_fColor[3] -= 0.05;
	move();
	m_vDisplacement.y -= (2 * Application::m_fReciprocalFPS);

	//	updateBillboardMatrix();

	m_fAngleX += 180 * Application::m_fReciprocalFPS;
	m_fAngleY += 180 * Application::m_fReciprocalFPS;
	m_fAngleZ += 180 * Application::m_fReciprocalFPS;

	if (m_bSpawnTrailParticle) {
		Particle *pParticle = new Particle_SmokeTrail(m_vPosition);
		m_pParticleManager->m_listParticles.push_back(pParticle);
	}

	m_bSpawnTrailParticle = !m_bSpawnTrailParticle;
}

void Particle_Crate::draw()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);

	glColor4f(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);

	glPushMatrix();

	glTranslatef(m_vPosition.x, m_vPosition.y, m_vPosition.z);

	glRotatef(m_fAngleX, 1, 0, 0);
	glRotatef(m_fAngleY, 0, 1, 0);
	glRotatef(m_fAngleZ, 0, 0, 1);

	glScalef(m_fScaleFactor, m_fScaleFactor, m_fScaleFactor);

	Application::m_pTextureManager->bindTexture(m_iTextureIndex);
	glCallList(ParticleManager::m_iParticleDL);

	glPopMatrix();

	glColor4f(1, 1, 1, 1);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}
