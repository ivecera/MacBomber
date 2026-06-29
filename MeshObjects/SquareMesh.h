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

#ifndef SquareMesh_H
#define SquareMesh_H

#include "Mesh.h"
#include "Vector3.h"

class SquareMesh {
private:
	//stores texcoords for arrow layers
	Vector3 m_pTexCoords[4][4];

	GLfloat mat_amb_diff[4];
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_shininess;

	GLuint m_nVBOVertices;
	GLuint m_nVBOIndices;
	GLuint m_nVBONormals;
	GLuint m_nVBOTexcoords[4];

	int m_iMaxTextureCount;
	float m_fTexCoords[4][8];
	// the current set of texcoords which should be used for texture layer 2
	int m_iCurrentTexCoords;
	int *m_pTextureIndices;

	// tells us wether a specific texture unit should be used
	bool *m_bUseTexture;

	//calculates four sets of Texcoords (in 90¡ steps)
	void init();

public:
	void resetTextureEngines();

	void configureMaterial();

	SquareMesh();
	~SquareMesh();

	//specifies which texcoords to be used
	void setTexCoord(int type);

	// by passing NONE as nr, texture unit index will be disabled
	void setTexture(int index, int nr);

	void configureTexture0(int index);
	void configureTexture1(int index);

	void configureTexCoord0(int index);
	void configureTexCoord1(int index);

	void enableBuffers();
	void disableBuffers();

	// for now we don't use an VBO for fields.
	// Thus we have to override Mesh::draw()
	void drawVBO();
};

#endif