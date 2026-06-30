/*
 *  ParticleManager.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "Particle.h"
#include "Particle_Explosion.h"

#include <glm/glm.hpp>

#include <list>

class ParticleManager {
	friend class Particle_Item;
	friend class Particle_Crate;
	friend class Particle_SmokeTrail;

private:
	//calculates a random displacment vector, which lays on hemisphere with radius 1 around m_vPos
	void calculateDisplacement(glm::vec3 &vDisplacement, int minAngle,
				   int maxAngle);
	//calculates a new startPosition, wehich lays within a sphere with radius "radius" araound m_vPos
	void randomizeStartPosition(glm::vec3 &vPosition, float radius = 1);

	//list, which contains all particles except explosion particle
	std::list<Particle *> m_listParticles;
	/**
	list which keeps all explosion particles.
	this is used to ensure that all debirs, smoke particles are drawn on top of the explosions
	*/
	std::list<Particle_Explosion *> m_listExplosionParticles;

public:
	~ParticleManager();

	void addItemParticle(glm::vec3 vPos, int count, int itemType);
	void addSmokeParticle(glm::vec3 vPos, int count);
	void addPlayerSmokeParticle(glm::vec3 vPos, int count);
	void addCrateParticle(glm::vec3 vPos, int count);
	void addExplosionParticle(glm::vec3 vPos);
	void addWileyParticle(glm::vec3 vPos, int count);

	void update();
	void draw();
};

#endif
