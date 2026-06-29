/*
 *  Wiley.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 13.10.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "Wiley.h"
#include "../Engine/MeshManager.h"
#include "../Engine/TriangleMesh.h"
#include "../Defines.h"
#include "../Application.h"
#include "../MeshObjects/BombMesh.h"

Wiley::Wiley()
	: Object_Moving(-10, 0, 1)
{
	m_bDoesDrop = false;
	m_iDirection = NONE;
	m_fVelocity = 10.0f;
}

void Wiley::draw()
{
	glPushMatrix();
	glTranslatef(m_vPos.x, m_vPos.y, m_vPos.z);
	Application::m_pMeshManager->m_pBombMesh->configureTexCoord0();
	Application::m_pMeshManager->m_pBombMesh->configureTexture0(
		DESTROYER_TEXTURE);
	Application::m_pMeshManager->m_pBombMesh->enableBuffers();
	Application::m_pMeshManager->m_pBombMesh->drawVBO();
	Application::m_pMeshManager->m_pBombMesh->disableBuffers();
	Application::m_pMeshManager->m_pBombMesh->resetTextureEngines();

	glPopMatrix();
}