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

#include "loadTexture.h"

#include "TriangleMesh.h"
#include "lib3ds/chunk.h"
#include "lib3ds/mesh.h"
#include "lib3ds/vector.h"
#include "lib3ds/material.h"

TriangleMesh::TriangleMesh()
{
	m_nVertices = 0;
	m_nTexels = 0;
	m_nTriangles = 0;
	m_nMaterials = 0;
	m_iTexture = 0;

	// Array to store the vertices of the mesh
	m_pVertexIndices = NULL;
	m_pVertices = NULL;
	m_pVertexNormals = NULL;
	m_pTexCoords = NULL;

	m_bTexture = false;
}

void TriangleMesh::load3dsFile(Lib3dsFile *pFile)
{
	Lib3dsMesh *mesh = NULL;

	if (pFile == NULL) {
		SDL_Log("TriangleMesh: File not found.");
		exit(-1);
	}

	mesh = pFile->meshes;

	// -----------------	Determine the counts
	m_nVertices = mesh->points;
	m_nTriangles = mesh->faces;
	m_nTexels = mesh->texels;

	// How many materials are there?
	Lib3dsMaterial *m;
	for (m = pFile->materials; m; m = m->next) {
		//printf ("%s\n",m->name);
		m_nMaterials++;
	}
	m_pVertexIndices = new int[m_nTriangles * 3];
	m_pVertices = new glm::vec3[m_nVertices];
	m_pVertexNormals = new glm::vec3[m_nVertices];
	m_pTexCoords = new float[m_nTexels * 2];

	// -----------------	Fill arrays
	// Vertices
	Lib3dsVector pos;

	for (int i = 0; i < m_nVertices; i++) {
		lib3ds_vector_copy(pos, mesh->pointL[i].pos);

		//	In Wings3D, specify that Y/Z should not be swapped on export
		//	(This also preserves the normals)
		m_pVertices[i].x = pos[0];
		m_pVertices[i].y = pos[1];
		m_pVertices[i].z = pos[2];
	}

	// Normals & Vertexindices
	int j = 0;
	int k = 0;
	glm::vec3 faceNormal;

	for (int i = 0; i < m_nTriangles; i++) {
		//get the face Normal
		faceNormal.x = mesh->faceL[i].normal[0];
		faceNormal.y = mesh->faceL[i].normal[1];
		faceNormal.z = mesh->faceL[i].normal[2];

		// get the indices of the vertices, which define this face
		m_pVertexIndices[k++] = mesh->faceL[i].points[0];
		m_pVertexIndices[k++] = mesh->faceL[i].points[1];
		m_pVertexIndices[k++] = mesh->faceL[i].points[2];

		//vertexnormals calculation...
		m_pVertexNormals[mesh->faceL[i].points[0]] =
			m_pVertexNormals[mesh->faceL[i].points[0]] + faceNormal;
		m_pVertexNormals[mesh->faceL[i].points[1]] =
			m_pVertexNormals[mesh->faceL[i].points[1]] + faceNormal;
		m_pVertexNormals[mesh->faceL[i].points[2]] =
			m_pVertexNormals[mesh->faceL[i].points[2]] + faceNormal;
	}

	// Run through all vertexnormals and normalize them
	for (int i = 0; i < m_nVertices; i++) {
		m_pVertexNormals[i] = glm::normalize(m_pVertexNormals[i]);
	}

	// Texcoords

	if (m_nTexels != 0)
		m_bTexture = true;

	j = 0;
	if (m_bTexture) {
		Lib3dsTexel tmp;
		for (int i = 0; i < m_nTexels; i++) {
			lib3ds_vector_copy(tmp, mesh->texelL[i]);
			m_pTexCoords[j++] = tmp[0];
			m_pTexCoords[j++] = tmp[1];
		}

		/*		
		// Does the mesh have a texture?
		int textureIndex = 0;

			// Determine the texture
		for (m=pFile->materials; m; m=m->next)
		{
				Lib3dsTextureMap tmpMap = m->texture1_map;
				if (SDL_strcmp(tmpMap.name,"") != 0)
				{
					SDL_memcpy(m_cTexturename,tmpMap.name,64);
				//	printf("%s\n",m_cTexturename);
					loadTexture(m_TextureArray, textureIndex++, m->texture1_map.name);
				}
				
		}
		*/
	} //	if (m_bTexture)
}

TriangleMesh::~TriangleMesh()
{
	delete[] m_pVertexIndices;
	delete[] m_pVertices;
	delete[] m_pVertexNormals;
	delete[] m_pTexCoords;

	glDeleteBuffersARB(1, &m_nVBOVertices);
	glDeleteBuffersARB(1, &m_nVBOIndices);
	glDeleteBuffersARB(1, &m_nVBONormals);
	glDeleteBuffersARB(1, &m_nVBOTexcoords);
}

void TriangleMesh::createVBO()
{
	glGenBuffersARB(1, &m_nVBOVertices);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOVertices);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_nVertices * sizeof(glm::vec3),
			m_pVertices, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glGenBuffersARB(1, &m_nVBONormals);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBONormals);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_nVertices * sizeof(glm::vec3),
			m_pVertexNormals, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glGenBuffersARB(1, &m_nVBOTexcoords);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_nVertices * 2 * sizeof(GLfloat),
			m_pTexCoords, GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glGenBuffersARB(1, &m_nVBOIndices);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_nVBOIndices);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
			m_nTriangles * 3 * sizeof(int), m_pVertexIndices,
			GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void TriangleMesh::drawVBO()
{
	/*	if (m_bTexture)
		glBindTexture( GL_TEXTURE_2D, m_TextureArray[m_iTexture] );
	*/

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBONormals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_nVBOIndices);
	glDrawElements(GL_TRIANGLES, m_nTriangles * 3, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}
