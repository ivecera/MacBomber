/*
 *  Particle_Item.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARTICLE_SMOKETRAIL_H
#define PARTICLE_SMOKETRAIL_H

#include "Particle.h"
#include "../Vector3.h"

class Particle_SmokeTrail : public Particle {
private:
public:
	Particle_SmokeTrail(Vector3 m_vPos);
	void update();
};
#endif
