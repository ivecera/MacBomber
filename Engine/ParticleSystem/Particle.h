/*
 *  Particle.h
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PARTICLE_H
#define PARTICLE_H
#include <glm/glm.hpp>

class Particle {
protected:
	void updateBillboardMatrix();
	//moves the particle
	void move();

public:
	float m_fVelocity; // the speed of the particle
	glm::vec3 m_vDisplacement; // the Direction it travels
	glm::vec3 m_vPosition; // the position of the particle
	int m_iTTL; // the amount of ticks it has to live ( Time To Live)

	float m_fColor[4]; //the particles Color (R,G,B,A )
	int m_iTextureIndex; // particles can have different textures
	float m_fScaleFactor; // the scalefactor for the particles Texture
	float m_fScaleFactorModifier;
	float m_fRotation; // rotation of the particle
	glm::mat4 m_BillboardMatrix;

	Particle(glm::vec3 vPos);

	bool isDead();
	bool m_bHasTrail;

	virtual ~Particle();
	virtual void update();
	virtual void draw();
};
#endif
