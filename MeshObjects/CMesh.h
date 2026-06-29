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

#ifndef CMesh_H
#define CMesh_H


#include <GLUT/glut.h>
#include "lib3ds/file.h"

class CVector3; 

class CMesh
{
    
    
protected:
    
	// pointer to an array with texture indices
	int * m_pTextureIndices;	
	
    // amount of Vertices/texcoords/Triangles
    int m_nVertices;
	int m_nTexels;
	int m_nTriangles;
	int m_nIndices;
	
	//pointer to an array of vertexindices and texcoords
	int * m_pVertexIndices;	
	float * m_pTexCoords;
	
	CVector3 * m_pVertices;
	CVector3 * m_pVertexNormals;
	
	bool m_bUseVBO;
	
	GLfloat mat_amb_diff[4];
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_shininess;

	GLuint m_nVBOVertices;
	GLuint m_nVBOIndices;
	GLuint m_nVBONormals;
	GLuint m_nVBOTexcoords;
 

 
	const char * expand(const char * path);
	void load3dsFile(const char *fileName);

public:	

	//disable all used texture units (prevents objects from being textured with wrong textures)
	virtual void resetTextureEngines() = 0;
	
	// gets called to setup the objects Material properties
	virtual void configureMaterial(){};
	
	//loads our vertices/normals/texcoords to vram 
	void createVBO();
	
	//constructor if this mesh object uses an 3ds file
	CMesh(char * fileName);
    virtual ~CMesh();
	
	
	void configureTexCoord0();
	void configureTexCoord1();
	
	
	void configureTexture0(int index);
	void configureTexture1(int index);
	
	void enableBuffers();
	void disableBuffers();
    void drawVBO();
	
	
};



#endif;