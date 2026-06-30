#include "../MatrixStack.h"
#include <SDL3/SDL_opengl.h>

#include "Particle_Explosion.h"
#include "../../Application.h"
#include "../DrawQuad.h"
#include "../TextureManager.h"

#include "../../Defines.h"

Particle_Explosion::Particle_Explosion(glm::vec3 vPos)
	: Particle(vPos)
{
	m_iTTL = 16;
	//m_fScaleFactor =  0.2 + ((SDL_rand(2)) *0.1);
	m_fVelocity = 0;
	m_vPosition.y = 0.5;

	/*	float rnd = ((float)(SDL_rand(5)))/10 ;
	m_fColor[0] = 0.6 + rnd;
	m_fColor[1] = 0.6;
	m_fColor[2] = 0.6;
	m_fColor[3] = 1;
*/
	float rnd = ((float)(SDL_rand(3))) / 10;
	m_fColor[0] = 0.8 + rnd;
	m_fColor[1] = 0.9;
	m_fColor[2] = 0.9;
	m_fColor[3] = 1;

	//set initial scalefactor
	rnd = float(SDL_rand(10));
	//	m_fScaleFactor = 1.3 + rnd/10;
	m_fScaleFactor = 0.8 + rnd / 10;
	//randomly choose one of three explosion textures
	switch (SDL_rand(3)) {
	case 0:
		m_iTextureIndex = EXPLOSION_TEXTURE1;
		break;
	case 1:
		m_iTextureIndex = EXPLOSION_TEXTURE2;
		break;
	case 2:
		m_iTextureIndex = EXPLOSION_TEXTURE3;
		break;
	}
}

void Particle_Explosion::update()
{
	if (m_iTTL > 13) {
		m_fScaleFactor += (0.5 / 3);
	}

	if (m_iTTL < 5) {
		m_fColor[0] -= 0.2;
		m_fColor[1] -= 0.2;
		m_fColor[2] -= 0.2;
		m_fColor[3] -= 0.2;
	}
	m_iTTL--;

	m_fScaleFactor += (0.5 * Application::m_fReciprocalFPS);
	updateBillboardMatrix();
}

void Particle_Explosion::draw()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

	glDisable(GL_DEPTH_TEST);
	//	glDepthMask(GL_FALSE);

	glColor4f(m_fColor[0], m_fColor[1], m_fColor[2], m_fColor[3]);

	modelview.push();
	modelview.multiply(m_BillboardMatrix);
	glNormal3f(0, 0, 1);
	modelview.scale(m_fScaleFactor, m_fScaleFactor, m_fScaleFactor);

	Application::m_pTextureManager->bindTexture(m_iTextureIndex);
	modelview.rotate(m_fRotation, 0, 0, 1);
	modelview.apply();
	drawUnitQuad();
	modelview.pop();

	glColor4f(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	//	glDepthMask(GL_TRUE);

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}
