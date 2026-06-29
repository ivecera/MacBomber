/*
 *  Particle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARTICLE_ITEM_H
#define PARTICLE_ITEM_H

#include "Particle.h"
#include "../Vector3.h"

class ParticleManager;

class Particle_Item : public Particle {
private:
	bool m_bSpawnTrailParticle;

	ParticleManager *m_pParticleManager;

public:
	Particle_Item(Vector3 m_vPos, ParticleManager *pParticleManager,
		      int itemType);
	void update();
};
#endif
