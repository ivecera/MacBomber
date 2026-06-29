/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <SDL3/SDL_opengl.h>

#include "Explosion.h"
#include "Engine/Vector3.h"
#include "Engine/TextureManager.h"
#include "Engine/Billboard.h"
#include "Engine/Camera.h"
#include "Application.h"
#include "Defines.h"

Explosion::Explosion(Vector3 vPos)
{
	m_vPos = vPos;
	compileDisplayList();
	updateBillboardMatrix();
	reset();
}

Explosion::~Explosion()
{
	glDeleteLists(m_iExplosionDL, 1);
}

void Explosion::compileDisplayList()
{
	m_iExplosionDL = glGenLists(1);
	glNewList(m_iExplosionDL, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
	glEndList();
}

void Explosion::updateBillboardMatrix()
{
	calculateBillboardMatrix_Xaxis(m_vPos, m_BillboardMatrix);
}

void Explosion::update()
{
	m_fScaleFactor += 0.5 * Application::m_fReciprocalFPS;
}

void Explosion::draw()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glDisable(GL_DEPTH_TEST);
	//	glDepthMask(GL_FALSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glEnable(GL_BLEND);
	Application::m_pTextureManager->bindTexture(m_iTextureIndex);
	glPushMatrix();
	glMultMatrixf(m_BillboardMatrix);
	glScalef(m_fScaleFactor, m_fScaleFactor, 0);

	glNormal3f(0, 0, 1);

	/*	glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.0f);   
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.0f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.0f);   
     		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.0f);   
		glEnd();		*/
	glCallList(m_iExplosionDL);

	//		glTranslatef(-0.2,0,-0.1);

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

	//	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}

void Explosion::reset()
{
	//set initial scalefactor
	float rnd = float(rand() % 10);
	m_fScaleFactor = 1.3 + rnd / 10;
	//randomly choose one of three explosion textures
	switch (rand() % 3) {
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
