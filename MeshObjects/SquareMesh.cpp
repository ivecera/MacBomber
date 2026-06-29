
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

#include "SquareMesh.h"
#include "../Application.h"
#include "../Engine/TextureManager.h"
#include "../Defines.h"
#include "../Engine/3DMath.h"

#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_opengl.h>

SquareMesh::SquareMesh()
{
	m_iMaxTextureCount = 3;
	m_iCurrentTexCoords = 0;
	m_bUseTexture = new bool[m_iMaxTextureCount];
	for (int i = 0; i < m_iMaxTextureCount; i++) {
		m_bUseTexture[i] = false;
	}
	m_pTextureIndices = new int[m_iMaxTextureCount];

	m_bUseTexture[0] = true;

	mat_ambient[0] = 0.7;
	mat_ambient[1] = 0.7;
	mat_ambient[2] = 0.7;
	mat_ambient[3] = 1.0;

	mat_diffuse[0] = 0.2;
	mat_diffuse[1] = 0.2;
	mat_diffuse[2] = 0.2;
	mat_diffuse[3] = 1.0;

	mat_specular[0] = 0.1;
	mat_specular[1] = 0.1;
	mat_specular[2] = 0.1;
	mat_specular[3] = 1.0;

	mat_shininess = 10.0;

	init();
}

SquareMesh::~SquareMesh()
{
	delete[] m_bUseTexture;
	delete[] m_pTextureIndices;
	glDeleteBuffersARB(4, m_nVBOTexcoords);
	glDeleteBuffersARB(1, &m_nVBOVertices);
	glDeleteBuffersARB(1, &m_nVBOIndices);
	glDeleteBuffersARB(1, &m_nVBONormals);
}

void SquareMesh::init()
{
	glGenBuffersARB(4, m_nVBOTexcoords);
	for (int i = 0; i < 4; i++) {
		//all coords are subtracted by -0.5 to center them around origin for rotation
		// so: 0 -> -0.5; 1 -> -0.5 etc.
		m_fTexCoords[i][0] = -0.5;
		m_fTexCoords[i][1] = -0.5;
		m_fTexCoords[i][2] = 0.5;
		m_fTexCoords[i][3] = -0.5;
		m_fTexCoords[i][4] = 0.5;
		m_fTexCoords[i][5] = 0.5;
		m_fTexCoords[i][6] = -0.5;
		m_fTexCoords[i][7] = 0.5;

		rotateAroundYAxis(m_fTexCoords[i][0], m_fTexCoords[i][1],
				  -90 * i);
		rotateAroundYAxis(m_fTexCoords[i][2], m_fTexCoords[i][3],
				  -90 * i);
		rotateAroundYAxis(m_fTexCoords[i][4], m_fTexCoords[i][5],
				  -90 * i);
		rotateAroundYAxis(m_fTexCoords[i][6], m_fTexCoords[i][7],
				  -90 * i);

		//correct centering
		m_fTexCoords[i][0] += 0.5;
		m_fTexCoords[i][1] += 0.5;
		m_fTexCoords[i][2] += 0.5;
		m_fTexCoords[i][3] += 0.5;
		m_fTexCoords[i][4] += 0.5;
		m_fTexCoords[i][5] += 0.5;
		m_fTexCoords[i][6] += 0.5;
		m_fTexCoords[i][7] += 0.5;

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords[i]);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, 4 * 2 * sizeof(GLfloat),
				m_fTexCoords[i], GL_STATIC_DRAW_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	}

	GLfloat fTexCoords[12] = { -0.5, 0.0, 0.5,  0.5,  0.0, 0.5,
				   0.5,	 0,   -0.5, -0.5, 0,   -0.5 };

	glGenBuffersARB(1, &m_nVBOVertices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOVertices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, 4 * 3 * sizeof(GLfloat),
			fTexCoords, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	GLuint iIndices[4] = { 0, 1, 2, 3 };
	glGenBuffersARB(1, &m_nVBOIndices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOIndices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, 4 * sizeof(GLuint), iIndices,
			GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	GLfloat fNormals[12] = { 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
				 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 };

	glGenBuffersARB(1, &m_nVBONormals);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBONormals);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, 4 * 3 * sizeof(GLfloat), fNormals,
			GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void SquareMesh::setTexCoord(int type)
{
	m_iCurrentTexCoords = type;
}

void SquareMesh::setTexture(int index, int nr)
{
	if (index < m_iMaxTextureCount) {
		if (nr == NONE) {
			m_bUseTexture[index] = false;
		} else {
			m_bUseTexture[index] = true;
			m_pTextureIndices[index] = nr;
		}
	}
}

void SquareMesh::configureTexture0(int index)
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	Application::m_pTextureManager->bindTexture(index);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void SquareMesh::configureTexture1(int index)
{
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	Application::m_pTextureManager->bindTexture(index);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void SquareMesh::configureTexCoord0(int index)
{
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void SquareMesh::configureTexCoord1(int index)
{
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords[index]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void SquareMesh::enableBuffers()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBONormals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_nVBOIndices);
}

void SquareMesh::disableBuffers()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void SquareMesh::resetTextureEngines()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);

	m_bUseTexture[0] = false;
	m_bUseTexture[1] = false;
	m_bUseTexture[2] = false;
}

void SquareMesh::configureMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void SquareMesh::drawVBO()
{
	glDrawRangeElements(GL_QUADS, 0, 4, 4, GL_UNSIGNED_INT, NULL);
}
