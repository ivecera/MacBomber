/*
 *  Particle.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 02.01.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <SDL3/SDL_opengl.h>

#include "../../Application.h"
#include "../../Defines.h"
#include "../Billboard.h"
#include "../TextureManager.h"
#include "ParticleManager.h"
#include "Particle.h"

Particle::Particle(glm::vec3 vPos)
{
	m_vPosition = vPos;
	m_fScaleFactorModifier = 0;
	m_fRotation = 0;
	updateBillboardMatrix();
}

bool Particle::isDead()
{
	if (m_iTTL < 0)
		return true;
	else
		return false;
}

void Particle::updateBillboardMatrix()
{
	calculateBillboardMatrix_Xaxis(m_vPosition, m_BillboardMatrix);
}

void Particle::move()
{
	m_vPosition =
		m_vPosition + ((m_vDisplacement *
				(m_fVelocity * Application::m_fReciprocalFPS)));
}

void Particle::draw()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glDisable( GL_DEPTH_TEST );
	glDepthMask(GL_FALSE);

	glColor4f(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);

	glPushMatrix();
	glMultMatrixf(m_BillboardMatrix);
	glNormal3f(0, 0, 1);
	glScalef(m_fScaleFactor, m_fScaleFactor, m_fScaleFactor);

	Application::m_pTextureManager->bindTexture(m_iTextureIndex);
	glRotatef(m_fRotation, 0, 0, 1);
	/*		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.0f);   
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.0f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.0f);   
     		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.0f);   
		glEnd();*/
	glCallList(ParticleManager::m_iParticleDL);
	glPopMatrix();

	glColor4f(1, 1, 1, 1);
	//	glEnable( GL_DEPTH_TEST );
	glDepthMask(GL_TRUE);

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

Particle::~Particle()
{
}

void Particle::update()
{
	m_iTTL--;
	if (m_iTTL < 10) {
		m_fColor[3] -= 0.1;
	}

	m_fScaleFactor +=
		(m_fScaleFactorModifier * Application::m_fReciprocalFPS);

	move();
	updateBillboardMatrix();
}
