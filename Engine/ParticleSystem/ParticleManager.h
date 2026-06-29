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

#include <GLUT/glut.h>
#include "Particle.h"
#include "Particle_Explosion.h"

#include "../Vector3.h"

#include <list>

class ParticleManager {
	friend class Particle_Item;
	friend class Particle_Crate;
	friend class Particle_SmokeTrail;

private:
	//calculates a random displacment vector, which lays on hemisphere with radius 1 around m_vPos
	void calculateDisplacement(Vector3 &vDisplacement, int minAngle,
				   int maxAngle);
	//calculates a new startPosition, wehich lays within a sphere with radius "radius" araound m_vPos
	void randomizeStartPosition(Vector3 &vPosition, float radius = 1);

	//list, which contains all particles except explosion particle
	list<Particle *> m_listParticles;
	/**
	list which keeps all explosion particles.
	this is used to ensure that all debirs, smoke particles are drawn on top of the explosions
	*/
	list<Particle_Explosion *> m_listExplosionParticles;

public:
	static GLuint m_iParticleDL;

	ParticleManager();
	~ParticleManager();

	void addItemParticle(Vector3 vPos, int count, int itemType);
	void addSmokeParticle(Vector3 vPos, int count);
	void addPlayerSmokeParticle(Vector3 vPos, int count);
	void addCrateParticle(Vector3 vPos, int count);
	void addExplosionParticle(Vector3 vPos);
	void addWileyParticle(Vector3 vPos, int count);

	void update();
	void draw();
};

#endif
