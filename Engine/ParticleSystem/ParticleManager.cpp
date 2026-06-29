/*
 *  ParticleManager.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <SDL3/SDL_opengl.h>

#include "ParticleManager.h"
#include "Particle_Item.h"
#include "Particle_Smoke.h"
#include "Particle_Crate.h"
#include "Particle_Explosion.h"

#include "../3DMath.h"
#include "../TextureManager.h"
#include "../../Application.h"
#include "../../Defines.h"

GLuint ParticleManager::m_iParticleDL = 0;

ParticleManager::ParticleManager()
{
	m_iParticleDL = glGenLists(1);
	glNewList(m_iParticleDL, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
	glEndList();
}

ParticleManager::~ParticleManager()
{
	{
		list<Particle *>::iterator it;
		for (it = m_listParticles.begin(); it != m_listParticles.end();
		     it++) {
			delete (*it);
		}
		m_listParticles.clear();
	}

	list<Particle_Explosion *>::iterator it;
	for (it = m_listExplosionParticles.begin();
	     it != m_listExplosionParticles.end(); it++) {
		delete (*it);
	}
	m_listExplosionParticles.clear();
	glDeleteLists(m_iParticleDL, 1);
}

void ParticleManager::addItemParticle(glm::vec3 vPos, int count, int itemType)
{
	for (int i = 0; i < count; i++) {
		Particle *particle = new Particle_Item(vPos, this, itemType);
		calculateDisplacement(particle->m_vDisplacement, 60, 120);

		m_listParticles.push_back(particle);
	}
}

void ParticleManager::addCrateParticle(glm::vec3 vPos, int count)
{
	for (int i = 0; i < count; i++) {
		Particle *particle = new Particle_Crate(vPos, this);
		calculateDisplacement(particle->m_vDisplacement, 20, 160);
		m_listParticles.push_back(particle);
	}
}

void ParticleManager::addSmokeParticle(glm::vec3 vPos, int count)
{
	for (int i = 0; i < count; i++) {
		Particle *particle = new Particle_Smoke(vPos);
		randomizeStartPosition(particle->m_vPosition, 0.5);
		particle->m_vPosition.y = 0;
		m_listParticles.push_back(particle);
	}
}

void ParticleManager::addPlayerSmokeParticle(glm::vec3 vPos, int count)
{
	for (int i = 0; i < count; i++) {
		Particle *particle = new Particle_Smoke(vPos);
		randomizeStartPosition(particle->m_vPosition, 0.5);
		particle->m_iTTL = 100;
		particle->m_fScaleFactor = 0.75;
		particle->m_fScaleFactorModifier = 1;

		float fColorMod = 0.5 + ((SDL_rand(7)) * 0.1);
		particle->m_fColor[0] = fColorMod;
		particle->m_fColor[1] = fColorMod;
		particle->m_fColor[2] = fColorMod;
		particle->m_fColor[3] = 0.8;

		particle->m_fVelocity = 1 + ((SDL_rand(11)) * 0.1);
		particle->m_vDisplacement.y = 1;
		particle->m_iTextureIndex = PARTICLE_SMOKE0_TEXTURE;

		m_listParticles.push_back(particle);
	}
}

void ParticleManager::addExplosionParticle(glm::vec3 vPos)
{
	Particle_Explosion *particle = new Particle_Explosion(vPos);
	//randomizeStartPosition(particle->m_vPosition, 0.2);
	m_listExplosionParticles.push_back(particle);
}

void ParticleManager::addWileyParticle(glm::vec3 vPos, int count)
{
	for (int i = 0; i < count; i++) {
		Particle *particle = new Particle(vPos);
		randomizeStartPosition(particle->m_vPosition, 0.25);
		particle->m_iTTL = 50;
		particle->m_fScaleFactor = 0.75;
		particle->m_fScaleFactorModifier = -0.5;
		particle->m_fRotation = SDL_rand(360);

		//determine randomly a yellow color
		float fColorMod = 0.1 + ((SDL_rand(5)) * 0.1);
		particle->m_fColor[0] = 1;
		particle->m_fColor[1] = 1;
		particle->m_fColor[2] = fColorMod;
		particle->m_fColor[3] = 0.8;

		particle->m_fVelocity = 1;
		particle->m_vDisplacement.y = -1;
		particle->m_iTextureIndex = PARTICLE_WILEY_TEXTURE;

		m_listParticles.push_back(particle);
	}
}

void ParticleManager::calculateDisplacement(glm::vec3 &vDisplacement,
					    int minAngle, int maxAngle)
{
	float angle;
	float x, y, z;

	//randomly choose an angle between minAngle - maxAngle;
	angle = SDL_rand(maxAngle - minAngle);
	angle += minAngle;
	//convert deg -> rad
	angle = (angle * SDL_PI_F / 180);

	//caluclate intial values of the displacement vector
	x = SDL_cosf(angle);
	y = SDL_sinf(angle);
	z = 0;

	//rotate the point (x,z) araund the y axis by a random angle
	rotateAroundYAxis(x, z, SDL_rand(360));

	vDisplacement.x = x;
	vDisplacement.y = y;
	vDisplacement.z = z;
}

void ParticleManager::randomizeStartPosition(glm::vec3 &vPosition, float radius)
{
	float angle;
	float x, y, z;

	//randomly choose an angle between minAngle - maxAngle;
	angle = SDL_rand(360);
	//convert deg -> rad
	angle = (angle * SDL_PI_F / 180);

	//caluclate intial values of the displacement vector
	x = SDL_cosf(angle);
	y = SDL_sinf(angle);
	z = 0;

	//rotate the point (x,z) araund the y axis by a random angle
	rotateAroundYAxis(x, z, SDL_rand(360));

	vPosition.x += x * radius;
	vPosition.y += y * radius;
	vPosition.z += z * radius;
}

void ParticleManager::update()
{
	{
		list<Particle *>::iterator it;
		for (it = m_listParticles.begin();
		     it != m_listParticles.end();) {
			if ((*it)->isDead()) {
				delete (*it);
				m_listParticles.erase(it++);

			} else {
				(*it)->update();
				++it;
			}
		}
	}

	list<Particle_Explosion *>::iterator it;
	for (it = m_listExplosionParticles.begin();
	     it != m_listExplosionParticles.end();) {
		if ((*it)->isDead()) {
			delete (*it);
			m_listExplosionParticles.erase(it++);

		} else {
			(*it)->update();
			++it;
		}
	}
}

void ParticleManager::draw()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	list<Particle_Explosion *>::reverse_iterator it;
	for (it = m_listExplosionParticles.rbegin();
	     it != m_listExplosionParticles.rend(); it++) {
		(*it)->draw();
	}

	{
		list<Particle *>::reverse_iterator it;
		for (it = m_listParticles.rbegin();
		     it != m_listParticles.rend(); it++) {
			(*it)->draw();
		}
	}
}
