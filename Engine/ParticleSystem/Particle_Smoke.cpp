
#include "Particle_Smoke.h"
#include "../../Application.h"
#include "../../Defines.h"

Particle_Smoke::Particle_Smoke(glm::vec3 vPos)
	: Particle(vPos)
{
	m_iTTL = 40;
	//	m_fScaleFactor = 0.25;
	m_fScaleFactor = 0.2 + ((rand() % 2) * 0.1);
	m_fVelocity = 5 + rand() % 6;
	m_vDisplacement.y = 1;
	m_iTextureIndex = PARTICLE_SMOKE1_TEXTURE;

	float fColorMod = 0.7 + ((rand() % 4) * 0.1);
	m_fColor[0] = fColorMod;
	m_fColor[1] = fColorMod;
	m_fColor[2] = fColorMod;
	m_fColor[3] = 1;

	m_fRotation = rand() % 360;
}

void Particle_Smoke::update()
{
	m_iTTL--;
	if (m_iTTL < 20)
		m_fColor[3] -= 0.05;
	move();

	m_fScaleFactor +=
		(m_fScaleFactorModifier * Application::m_fReciprocalFPS);

	updateBillboardMatrix();
}
