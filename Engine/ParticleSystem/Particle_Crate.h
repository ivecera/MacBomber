/*
 *  Particle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARTICLE_CRATE_H
#define PARTICLE_CRATE_H

#include "Particle.h"
#include <glm/glm.hpp>

class ParticleManager;

class Particle_Crate : public Particle {
private:
	float m_fAngleX; //rotation of Particle around X Axis
	float m_fAngleY; //rotation of Particle around Y Axis
	float m_fAngleZ; //rotation of Particle around Z Axis

	bool m_bSpawnTrailParticle;
	ParticleManager *m_pParticleManager;

public:
	Particle_Crate(glm::vec3 m_vPos, ParticleManager *pParticleManager);
	void update();
	void draw();
};
#endif
