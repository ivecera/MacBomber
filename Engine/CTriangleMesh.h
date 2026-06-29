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

#ifndef CTriangleMesh_H
#define CTriangleMesh_H

#include <GLUT/glut.h>
#include "lib3ds/file.h"

class CVector3; 

struct stMaterial 
{
	char name[50];
	float rgb[4];
	GLfloat amb[4];
	GLfloat diff[4];
	GLfloat spec[4];
	GLfloat shi;
	float trans;
	
	// Gehört zu diesem Material eine Texturemap
	bool bTexture;
	// Welche Texture soll verwendet werden ?
	int  iTextureIndex;
};


class CTriangleMesh
{
    
    
protected:
    
	int m_iTexture;
    // Array das die verwendeten Texturen enthält
	//GLuint m_TextureArray[10];
	
public:
	
    // Anzahl der Vertices/Materialien/Dreiecke(Faces) 
    int m_nVertices;
	int m_nTexels;
	int m_nTriangles;
    int m_nMaterials;
	
	int * m_pVertexIndices;	
//	float * m_pVertices;
//	float * m_pNormals;
	float * m_pTexCoords;
	
	CVector3 * m_pVertices;
	CVector3 * m_pVertexNormals;
	
	
	GLuint m_nVBOVertices;
	GLuint m_nVBOIndices;
	GLuint m_nVBONormals;
	GLuint m_nVBOTexcoords;
	
	bool m_bTexture;
    char m_cName[64];
	char m_cTexturename[64];
	
	CTriangleMesh();	
	void load3dsFile(Lib3dsFile * pFile);
    ~CTriangleMesh();
	
	void createVBO();
    void drawVBO();
	
	
};



#endif;