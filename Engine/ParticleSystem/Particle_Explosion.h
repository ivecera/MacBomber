/*
 *  Particle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARTICLE_EXPLOSION_H
#define PARTICLE_EXPLOSION_H

#include "Particle.h"
#include "../Vector3.h"

class Particle_Explosion : public Particle {
private:
public:
	Particle_Explosion(Vector3 m_vPos);

	void update();
	void draw();
};
#endif
