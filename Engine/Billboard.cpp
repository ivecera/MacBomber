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

#include "Billboard.h"
#include "Camera.h"
#include "../Application.h"

void calculateBillboardMatrix_Xaxis(const glm::vec3 &vPos, glm::mat4 &matrix)
{
	glm::vec3 vLook = Application::m_pCamera->m_vPosition - vPos;
	vLook.x = 0;
	vLook = glm::normalize(vLook);
	glm::vec3 vUp(1, 0, 0);
	glm::vec3 vRight = glm::cross(vUp, vLook);

	matrix = glm::mat4(glm::vec4(vRight, 0), glm::vec4(vUp, 0),
			   glm::vec4(vLook, 0), glm::vec4(vPos, 1));
}
