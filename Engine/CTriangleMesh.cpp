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

#include "loadTexture.h"
#include "Workaround.h"

#include "CTriangleMesh.h"
#include "3DMath.h"
#include "lib3ds/chunk.h"
#include "lib3ds/mesh.h"
#include "lib3ds/vector.h"
#include "lib3ds/material.h"

CTriangleMesh::CTriangleMesh()
{
	m_nVertices	= 0;
	m_nTexels	= 0;
	m_nTriangles = 0;
    m_nMaterials = 0;
	m_iTexture = 0;


    // Array in dem wir die Vertices des Meshs speichern
	m_pVertexIndices	= NULL;	
	m_pVertices			= NULL;
	m_pVertexNormals	= NULL;
	m_pTexCoords		= NULL;
    
	m_bTexture = false;
}


void CTriangleMesh::load3dsFile(Lib3dsFile * pFile)
{
	Lib3dsMesh *mesh = NULL;
	Lib3dsMaterial *mat =NULL;
	
	if (pFile == NULL)
	{
		cout << "CTRiangleMesh: File not found." << endl;
		exit(-1);
	}
	
	mesh = pFile->meshes;
	mat = pFile->materials;	
	
	// -----------------	Ermittele die Anzahlen
	m_nVertices  = mesh->points;
    m_nTriangles = mesh->faces;
	m_nTexels = mesh->texels; 
	
	// Wieviele Materialien gibt es ?
	Lib3dsMaterial *m;
	for (m=pFile->materials; m; m=m->next)
	{
		//printf ("%s\n",m->name);
		m_nMaterials++;
	}
	m_pVertexIndices	= new int[m_nTriangles*3];
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
		m_bTexture = true;
		
		
	j=0;		
	if (m_bTexture)
	{
		Lib3dsTexel tmp;
		for (int i = 0; i < m_nTexels; i++)
		{
			lib3ds_vector_copy(tmp, mesh->texelL[i]);
			m_pTexCoords[j++] = tmp[0];
			m_pTexCoords[j++] = tmp[1];
		}
		
/*		
		// Hat das Mesh eine Textur ?
		int textureIndex = 0;
				
			// Bestimme die Textur
		for (m=pFile->materials; m; m=m->next)
		{
				Lib3dsTextureMap tmpMap = m->texture1_map;
				if (strcmp(tmpMap.name,"") != 0)
				{
					memcpy(m_cTexturename,tmpMap.name,64);
				//	printf("%s\n",m_cTexturename);
					loadTexture(m_TextureArray, textureIndex++, m->texture1_map.name);
				}
				
		}
		*/					
	}//	if (m_bTexture)

		
	

}

CTriangleMesh::~CTriangleMesh()
{


	delete [] m_pVertexIndices;	
	delete [] m_pVertices;
	delete [] m_pVertexNormals;
	delete [] m_pTexCoords;

	glDeleteBuffersARB(1,&m_nVBOVertices);
	glDeleteBuffersARB(1,&m_nVBOIndices);
	glDeleteBuffersARB(1,&m_nVBONormals);
	glDeleteBuffersARB(1,&m_nVBOTexcoords);

	
}



void CTriangleMesh::createVBO()
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
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_nTriangles*3*sizeof(int), m_pVertexIndices, GL_STATIC_DRAW_ARB );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	
}

void CTriangleMesh::drawVBO()
{
/*	if (m_bTexture)
		glBindTexture( GL_TEXTURE_2D, m_TextureArray[m_iTexture] );
	*/
	
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBOVertices );
		glVertexPointer( 3, GL_FLOAT, 0, NULL );

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_nVBONormals);
		glNormalPointer(GL_FLOAT,0,NULL);
						
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_nVBOTexcoords);
		glTexCoordPointer(2,GL_FLOAT,0,NULL);
				
		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB,m_nVBOIndices);
		glDrawElements(GL_TRIANGLES,m_nTriangles*3,GL_UNSIGNED_INT,NULL);		
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	

	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
	

	glBindTexture( GL_TEXTURE_2D, NULL );
}


