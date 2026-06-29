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

#include <iostream.h>

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include "Workaround.h"

#include "../CApplication.h"
#include "../Defines.h"
#include "../Engine/CTextureManager.h"

#include "CMesh.h"
#include "3DMath.h"
#include "lib3ds/chunk.h"
#include "lib3ds/mesh.h"
#include "lib3ds/vector.h"
#include "lib3ds/material.h"


CMesh::CMesh(char * filename)
{
	m_bUseVBO = true;
	m_nVertices	= 0;
	m_nTexels	= 0;
	m_nTriangles = 0;
	
	
	// Array in dem wir die Vertices des Meshs speichern
	m_pVertexIndices	= NULL;	
	m_pVertices			= NULL;
	m_pVertexNormals	= NULL;
	m_pTexCoords		= NULL;
	
	load3dsFile(expand(filename));
	createVBO();
}

const char * CMesh::expand(const char * path)
{
	string tmp = CApplication::m_strResourcePath;
	tmp = tmp + path;
	return tmp.c_str(); 
}


void CMesh::load3dsFile(const char * fileName)
{

	Lib3dsMesh *mesh = NULL;
	Lib3dsMaterial *mat =NULL;
	bool bTexture = false;
	
	Lib3dsFile * pFile;
	pFile = lib3ds_file_load(fileName); 	
	
	if (pFile == NULL)
	{
		cout << "CTriangleMesh: File not found. Exit" << endl;
		exit(-1);
	}
	
	mesh = pFile->meshes;
	mat = pFile->materials;	
	
	// -----------------	Ermittele die Anzahlen
	m_nVertices  = mesh->points;
    m_nTriangles = mesh->faces;
	m_nTexels = mesh->texels; 
	m_nIndices = m_nTriangles * 3;
/*	// Wieviele Materialien gibt es ?
	Lib3dsMaterial *m;
	for (m=pFile->materials; m; m=m->next)
	{
		//printf ("%s\n",m->name);
		m_nMaterials++;
	}*/
	m_pVertexIndices	= new int[m_nIndices];
	m_pVertices			= new CVector3[m_nVertices];
	m_pVertexNormals	= new CVector3[m_nVertices];
	m_pTexCoords		= new float[m_nTexels*2];
	
	
	
	// -----------------	fülle Arrays
	// Vertices
    Lib3dsVector pos;

	for ( int i = 0; i < m_nVertices; i++)
	{
		lib3ds_vector_copy(pos, mesh->pointL[i].pos);
		
		//	Bei Wings3d also angeben, dass Y/z beim Export nicht geswapt werden sollen
		//	(So bleiben auch die Normals erhalten..)		
		m_pVertices[i].x = pos[0];
		m_pVertices[i].y = pos[1];
		m_pVertices[i].z = pos[2];

	}
	
	
	
	// Normals & Vertexindices
	int j=0;
	int k = 0;
	CVector3 faceNormal;
	
	for (int i=0; i< m_nTriangles; i++)
	{

		
		//get the face Normal
		faceNormal.x = mesh->faceL[i].normal[0];
		faceNormal.y = mesh->faceL[i].normal[1];
		faceNormal.z = mesh->faceL[i].normal[2];
		
		// get the indices of the vertices, which define this face
		m_pVertexIndices[k++]  = mesh->faceL[i].points[0];
		m_pVertexIndices[k++]  = mesh->faceL[i].points[1];
		m_pVertexIndices[k++]  = mesh->faceL[i].points[2];
		
		//vertexnormals calculation...
		m_pVertexNormals[mesh->faceL[i].points[0]] = m_pVertexNormals[mesh->faceL[i].points[0]] + faceNormal;
		m_pVertexNormals[mesh->faceL[i].points[1]] = m_pVertexNormals[mesh->faceL[i].points[1]] + faceNormal;
		m_pVertexNormals[mesh->faceL[i].points[2]] = m_pVertexNormals[mesh->faceL[i].points[2]] + faceNormal;
	
    }
	
	// Run through all vertexnormals and normalize them
	for (int i = 0; i < m_nVertices; i++)
	{
		m_pVertexNormals[i] = normalize (m_pVertexNormals[i]);
	}
	
	// Texcoords
	
	if ( m_nTexels != 0)
		bTexture = true;
		
		
	j=0;		
	if (bTexture)
	{
		Lib3dsTexel tmp;
		for (int i = 0; i < m_nTexels; i++)
		{
			lib3ds_vector_copy(tmp, mesh->texelL[i]);
			m_pTexCoords[j++] = tmp[0];
			m_pTexCoords[j++] = tmp[1];
		}
		
				
	}//	if (m_bTexture)

	lib3ds_file_free(pFile);
		
	

}

CMesh::~CMesh()
{
	if (m_bUseVBO)
	{
		delete [] m_pTextureIndices;
		delete [] m_pVertexIndices;	
		
		delete [] m_pVertices;
		delete [] m_pVertexNormals;
		delete [] m_pTexCoords;

		glDeleteBuffersARB(1,&m_nVBOVertices);
		glDeleteBuffersARB(1,&m_nVBOIndices);
		glDeleteBuffersARB(1,&m_nVBONormals);
		glDeleteBuffersARB(1,&m_nVBOTexcoords);
	}
	
}



void CMesh::createVBO()
{
	
	glGenBuffersARB( 1, &m_nVBOVertices );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBOVertices );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_nVertices*sizeof(CVector3), m_pVertices, GL_STATIC_DRAW_ARB );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
	
	glGenBuffersARB( 1, &m_nVBONormals );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBONormals );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_nVertices*sizeof(CVector3), m_pVertexNormals, GL_STATIC_DRAW_ARB );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
	
	glGenBuffersARB( 1, &m_nVBOTexcoords );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_nVertices*2*sizeof(GLfloat), m_pTexCoords, GL_STATIC_DRAW_ARB );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
	
	glGenBuffersARB( 1, &m_nVBOIndices );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_nVBOIndices );
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_nIndices * sizeof(int), m_pVertexIndices, GL_STATIC_DRAW_ARB );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	
}

void CMesh::configureTexCoord0()
{
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords);
		glTexCoordPointer(2,GL_FLOAT, 0, 0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void CMesh::configureTexCoord1()
{
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords);
		glTexCoordPointer(2,GL_FLOAT, 0, 0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


void CMesh::configureTexture0(int index)
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	CApplication::m_pTextureManager->bindTexture(index);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void CMesh::configureTexture1(int index)
{
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	CApplication::m_pTextureManager->bindTexture(index);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void CMesh::enableBuffers()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBOVertices );
		glVertexPointer( 3, GL_FLOAT, 0, NULL );

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBONormals);
		glNormalPointer(GL_FLOAT,0,NULL);
				
		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB,m_nVBOIndices);
}

void CMesh::disableBuffers()
{
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_NORMAL_ARRAY); 

}

void CMesh::drawVBO()
{
//	configureMaterial();
//	configureTextureEngines();
//	enableBuffers();
	
		glDrawRangeElements(GL_TRIANGLES,0,m_nIndices,m_nIndices,GL_UNSIGNED_INT,NULL);		
	
//	disableBuffers();
	
//	resetTextureEngines();
	
	
}


