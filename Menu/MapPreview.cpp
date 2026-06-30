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

#include "../Engine/MatrixStack.h"
#include <SDL3/SDL_opengl.h>

#include "MapPreview.h"
#include "../Application.h"
#include "../Defines.h"
#include "../Engine/MeshManager.h"

#include "../MeshObjects/SquareMesh.h"
#include "../MeshObjects/BlockMesh.h"
#include "../MeshObjects/CrateMesh.h"

MapPreview::MapPreview()
{
}

void MapPreview::setMap(StMapEntry entry)
{
	m_listCrateFields.clear();
	m_listBlockFields.clear();

	m_listPlainFields_Color0.clear();
	m_listPlainFields_Color1.clear();

	m_listArrowFields_Color0.clear();
	m_listArrowFields_Color1.clear();

	m_listHoleFields_Color0.clear();
	m_listHoleFields_Color1.clear();

	m_listRandomFields.clear();

	m_stMapEntry = entry;
	bool bColor0 = true;

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 19; j++) {
			stArrowField field;
			field.xPos = j;
			field.zPos = i;

			switch (m_stMapEntry.cArray[i][j]) {
			case '+': //Crate
				m_listCrateFields.push_back(field);
				break;
			case '*': //Block
				m_listBlockFields.push_back(field);
				break;
			case '-': //Void
				break;
			case 'o': //Hole
				if (bColor0)
					m_listHoleFields_Color0.push_back(
						field);
				else
					m_listHoleFields_Color1.push_back(
						field);
				break;
			case 'R': //Random
				m_listRandomFields.push_back(field);
				break;
			case '>':
				field.iDirection = RIGHT;
				if (bColor0) {
					m_listArrowFields_Color0.push_back(
						field);
				} else {
					m_listArrowFields_Color1.push_back(
						field);
				}
				break;

			case '<':
				field.iDirection = LEFT;
				if (bColor0) {
					m_listArrowFields_Color0.push_back(
						field);
				} else {
					m_listArrowFields_Color1.push_back(
						field);
				}
				break;
			case 'v':
				field.iDirection = DOWN;
				if (bColor0) {
					m_listArrowFields_Color0.push_back(
						field);
				} else {
					m_listArrowFields_Color1.push_back(
						field);
				}
				break;
			case '^': //UP
				field.iDirection = UP;
				if (bColor0) {
					m_listArrowFields_Color0.push_back(
						field);
				} else {
					m_listArrowFields_Color1.push_back(
						field);
				}

				break;
			case ' ': //Plain
			default: //default to plain field if unknown number or player start pos (1-8)
				if (bColor0)
					m_listPlainFields_Color0.push_back(
						field);
				else
					m_listPlainFields_Color1.push_back(
						field);
				break;
			} //switch
			bColor0 = !bColor0;
		}
}

void MapPreview::drawCrateFields()
{
	list<stArrowField>::iterator it;
	Application::m_pMeshManager->m_pCrateMesh->configureMaterial();
	Application::m_pMeshManager->m_pCrateMesh->configureTexture0(
		CRATE_TEXTURE);
	Application::m_pMeshManager->m_pCrateMesh->configureTexCoord0();

	Application::m_pMeshManager->m_pCrateMesh->enableBuffers();

	for (it = m_listCrateFields.begin(); it != m_listCrateFields.end();
	     it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pCrateMesh->drawVBO();
		modelview.pop();
	}

	Application::m_pMeshManager->m_pCrateMesh->disableBuffers();
	Application::m_pMeshManager->m_pCrateMesh->resetTextureEngines();
}

void MapPreview::drawBlockFields()
{
	list<stArrowField>::iterator it;
	Application::m_pMeshManager->m_pBlockMesh->configureMaterial();
	Application::m_pMeshManager->m_pBlockMesh->configureTexture0(
		BLOCK_TEXTURE);
	Application::m_pMeshManager->m_pBlockMesh->configureTexCoord0();

	Application::m_pMeshManager->m_pBlockMesh->enableBuffers();

	for (it = m_listBlockFields.begin(); it != m_listBlockFields.end();
	     it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pBlockMesh->drawVBO();
		modelview.pop();
	}
	Application::m_pMeshManager->m_pBlockMesh->disableBuffers();
	Application::m_pMeshManager->m_pBlockMesh->resetTextureEngines();
}

void MapPreview::drawPlainFields()
{
	list<stArrowField>::iterator it;

	//draw all fields in color0
	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_PLAIN0_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listPlainFields_Color0.begin();
	     it != m_listPlainFields_Color0.end(); it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}
	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();

	//draw all fields in color1
	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_PLAIN1_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listPlainFields_Color1.begin();
	     it != m_listPlainFields_Color1.end(); it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}
	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();

	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_PLAIN0_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->configureTexture1(
		FIELD_HOLE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord1(0);
	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listHoleFields_Color0.begin();
	     it != m_listHoleFields_Color0.end(); it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}
	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();
}
void MapPreview::drawArrowFields()
{
	list<stArrowField>::iterator it;

	//draw all fields in color0
	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_PLAIN0_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->configureTexture1(
		FIELD_ARROW);

	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listArrowFields_Color0.begin();
	     it != m_listArrowFields_Color0.end(); it++) {
		Application::m_pMeshManager->m_pSquareMesh->configureTexCoord1(
			((*it).iDirection));
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}
	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();

	//draw all fields in color1
	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_PLAIN1_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->configureTexture1(
		FIELD_ARROW);

	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listArrowFields_Color1.begin();
	     it != m_listArrowFields_Color1.end(); it++) {
		Application::m_pMeshManager->m_pSquareMesh->configureTexCoord1(
			((*it).iDirection));
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}
	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();
}

void MapPreview::drawHoleFields()
{
	list<stArrowField>::iterator it;
	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_PLAIN1_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->configureTexture1(
		FIELD_HOLE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord1(0);
	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listHoleFields_Color1.begin();
	     it != m_listHoleFields_Color1.end(); it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}

	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();
}

void MapPreview::drawRandomFields()
{
	list<stArrowField>::iterator it;
	Application::m_pMeshManager->m_pSquareMesh->configureMaterial();
	Application::m_pMeshManager->m_pSquareMesh->configureTexture0(
		FIELD_RANDOM_TEXTURE);
	Application::m_pMeshManager->m_pSquareMesh->configureTexCoord0(0);
	Application::m_pMeshManager->m_pSquareMesh->enableBuffers();

	for (it = m_listRandomFields.begin(); it != m_listRandomFields.end();
	     it++) {
		modelview.push();
		modelview.translate((*it).xPos, 0, (*it).zPos);
		modelview.apply();
		Application::m_pMeshManager->m_pSquareMesh->drawVBO();
		modelview.pop();
	}

	Application::m_pMeshManager->m_pSquareMesh->disableBuffers();
	Application::m_pMeshManager->m_pSquareMesh->resetTextureEngines();
}

void MapPreview::draw()
{
	modelview.push();
	modelview.loadIdentity();
	glm::mat4 v = glm::lookAt(glm::vec3(13, 25, 13), glm::vec3(13, -1, 9.5),
				  glm::vec3(0, 1, 0));
	modelview.multiply(v);
	modelview.translate(8, -2, 2);

	drawCrateFields();
	drawBlockFields();
	drawPlainFields();
	drawArrowFields();
	drawHoleFields();
	drawRandomFields();
	modelview.pop();
}
