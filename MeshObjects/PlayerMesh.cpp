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

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include "Workaround.h"

#include "../Application.h"
#include "../Engine/TextureManager.h"

#include "PlayerMesh.h"

PlayerMesh::PlayerMesh()
	: Mesh("/Meshes/MacClassic.3ds")
{
	mat_ambient[0] = 0.2;
	mat_ambient[1] = 0.2;
	mat_ambient[2] = 0.2;
	mat_ambient[3] = 1.0;

	mat_diffuse[0] = 0.8;
	mat_diffuse[1] = 0.8;
	mat_diffuse[2] = 0.8;
	mat_diffuse[3] = 1.0;

	mat_specular[0] = 0.3;
	mat_specular[1] = 0.3;
	mat_specular[2] = 0.3;
	mat_specular[3] = 1.0;

	mat_shininess = 10.0;
}

void PlayerMesh::resetTextureEngines()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
}

void PlayerMesh::configureMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}
