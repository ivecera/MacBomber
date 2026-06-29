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

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Engine/Vector3.h"
#include <SDL3/SDL_opengl.h>

class Camera;
class TextureManager;

class Explosion {
private:
	//position of Explosion
	Vector3 m_vPos;
	// Explosion Display List
	GLuint m_iExplosionDL;

	int m_iTextureIndex;
	float m_fScaleFactor;
	float m_BillboardMatrix[16];

	//creates an DisplayList and stores it in m_iExplosionDL
	void compileDisplayList();
	void updateBillboardMatrix();

public:
	Explosion(Vector3 vPos);
	~Explosion();
	void update();
	void draw();

	void reset();
};

#endif
