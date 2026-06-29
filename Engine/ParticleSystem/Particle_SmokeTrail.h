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
#include <glm/glm.hpp>

class Particle_SmokeTrail : public Particle {
private:
public:
	Particle_SmokeTrail(glm::vec3 m_vPos);
	void update();
};
#endif
