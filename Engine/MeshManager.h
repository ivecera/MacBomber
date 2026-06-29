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

#ifndef MESHMANAGER_H
#define MESHMANAGER_H

class TriangleMesh;

class BlockMesh;
class BombMesh;
class CrateMesh;
class ItemMesh;
class PlayerMesh;
class CupMesh;
class SquareMesh;

class MeshManager {
private:
	struct stMaterial {
		float ambientDiffuse[4];
		float specular[4];
	};

	// Array Contains all TriangleMeshes
	TriangleMesh *m_pTriangleMesh;
	// These Arrays contain Material Information for each Mesh
	stMaterial m_stMaterials[7];

	const char *expand(char *path);

public:
	// These are pointers to our Meshobjects (public for now)
	// to draw an object we call m_p<*>Mesh->drawVBO();
	BlockMesh *m_pBlockMesh;
	BombMesh *m_pBombMesh;
	CrateMesh *m_pCrateMesh;
	ItemMesh *m_pItemMesh;
	PlayerMesh *m_pPlayerMesh;
	CupMesh *m_pCupMesh;
	SquareMesh *m_pSquareMesh;

	MeshManager();
	~MeshManager();
	// load all Meshes
	//void loadMeshes();

	//draws the specified Mesh
	//void drawMesh(int index);
};
#endif